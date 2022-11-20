#include <Transform.h>

#include <algorithm>
#include <cassert>
#include <cmath>

Transform::Transform(const Transform& transform)
  : _position(transform._position)
  , _rotation(transform._rotation)
  , _scale(transform._scale)
{
  SetParent(transform._parent);
}

Transform::Transform(Transform&& transform) noexcept
  : _position(transform._position)
  , _rotation(transform._rotation)
  , _scale(transform._scale)
  , _children(std::move(transform._children))
{
  SetParent(transform._parent);

  for (auto child : _children)
    child->_parent = this;
}

Transform&
Transform::operator=(const Transform& transform)
{
  SetParent(transform._parent);

  _position = transform._position;
  _rotation = transform._rotation;
  _scale = transform._scale;

  return *this;
}

Transform&
Transform::operator=(Transform&& transform) noexcept
{
  for (auto child : _children)
    child->_parent = nullptr;

  SetParent(transform._parent);

  _position = transform._position;
  _rotation = transform._rotation;
  _scale = transform._scale;

  _children = std::move(transform._children);

  for (auto child : _children)
    child->_parent = this;

  return *this;
}

const Transform*
Transform::GetParent() const
{
  return _parent;
}

const Vector2&
Transform::GetPosition() const
{
  return _position;
}

const Vector2&
Transform::GetScale() const
{
  return _scale;
}

const float&
Transform::GetRotation() const
{
  return _rotation;
}

void
Transform::SetParent(Transform* parent)
{
  if (_parent == parent)
    return;

  if (_parent)
    _parent->DetachChild(this);

  _parent = parent;
  if (_parent)
    _parent->AttachChild(this);
}

void
Transform::SetPosition(const Vector2& position)
{
  _position = position;
}

void
Transform::SetScale(const Vector2& scale)
{
  _scale = scale;
}

void
Transform::SetRotation(float rotation)
{
  _rotation = rotation;
}

Vector2
Transform::GetGlobalPosition() const
{
  if (!_parent)
    return _position;

  return _parent->TransformPoint(_position);
}

Vector2
Transform::GetGlobalScale() const
{
  if (!_parent)
    return _scale;

  return _parent->GetGlobalScale() * _scale;
}

float
Transform::GetGlobalRotation() const
{
  if (!_parent)
    return _rotation;

  return _parent->GetGlobalRotation() + _rotation;
}

Vector2
Transform::TransformPoint(Vector2 point) const
{
  point *= GetGlobalScale();

  auto rotRad = GetGlobalRotation() * Deg2Rad;

  auto tmpX = std::cos(rotRad) * point.x - std::sin(rotRad) * point.y;
  auto tmpY = std::sin(rotRad) * point.x + std::cos(rotRad) * point.y;

  point.x = tmpX;
  point.y = tmpY;

  if (_parent)
    point += _parent->TransformPoint(_position);
  else
    point += _position;

  return point;
}

Vector2
Transform::InverseTransformPoint(Vector2 point) const
{
  if (_parent)
    point -= _parent->TransformPoint(_position);
  else
    point -= _position;

  auto rotRad = -GetGlobalRotation() * Deg2Rad;

  auto tmpX = std::cos(rotRad) * point.x - std::sin(rotRad) * point.y;
  auto tmpY = std::sin(rotRad) * point.x + std::cos(rotRad) * point.y;

  point.x = tmpX;
  point.y = tmpY;

  point /= GetGlobalScale();

  return point;
}

void
Transform::AttachChild(Transform* child)
{
  _children.push_back(child);
}

void
Transform::DetachChild(Transform* child)
{
  auto it = std::find(_children.begin(), _children.end(), child);
  assert(it != _children.end());

  _children.erase(it);
}