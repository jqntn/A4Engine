#pragma once

#include <Vector2.h>

#include <numbers>
#include <vector>

#define Deg2Rad float(std::numbers::pi / 180)
#define Rad2Deg float(180 / std::numbers::pi)

class Transform
{
public:
  Transform() = default;
  ~Transform() = default;

  Transform(const Transform&);
  Transform(Transform&&) noexcept;
  Transform& operator=(const Transform&);
  Transform& operator=(Transform&&) noexcept;

  const Transform* GetParent() const;

  const Vector2& GetPosition() const;
  const Vector2& GetScale() const;
  const float& GetRotation() const;

  void SetParent(Transform* parent);

  void SetPosition(const Vector2& position);
  void SetScale(const Vector2& scale);
  void SetRotation(float rotation);

  Vector2 GetGlobalPosition() const;
  Vector2 GetGlobalScale() const;
  float GetGlobalRotation() const;

  Vector2 TransformPoint(Vector2 position) const;
  Vector2 InverseTransformPoint(Vector2 position) const;

private:
  Transform* _parent = nullptr;
  Vector2 _position{}, _scale{ 1, 1 };
  float _rotation{};

  std::vector<Transform*> _children;

  void AttachChild(Transform* child);
  void DetachChild(Transform* child);
};