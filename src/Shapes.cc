#include <Shapes.h>

CircleShape::CircleShape(float radius, cpVect offset)
  : _radius(radius)
  , _offset(offset)
{
}

BoxShape::BoxShape(float width, float height)
  : _width(width)
  , _height(height)
{
}

SegmentShape::SegmentShape(cpVect startPos, cpVect endPos)
{
  _startPos = startPos;
  _endPos = endPos;
}

cpShape*
Shape::GetShape() const
{
  return _shape;
}

cpShape*
CircleShape::CreateShape(cpBody* body)
{
  return _shape = cpCircleShapeNew(body, _radius, _offset);
}

cpFloat
CircleShape::GetMoment(cpFloat mass) const
{
  return cpMomentForCircle(
    mass, cpFloat(_radius) * 2.f, cpFloat(_radius) * 2.f, _offset);
}

cpShape*
BoxShape::CreateShape(cpBody* body)
{
  return _shape = cpBoxShapeNew(body, _width, _height, 0);
}

cpFloat
BoxShape::GetMoment(cpFloat mass) const
{
  return cpMomentForBox(mass, _width, _height);
}

cpShape*
SegmentShape::CreateShape(cpBody* body)
{
  return _shape = cpSegmentShapeNew(body, _startPos, _endPos, 0.0f);
}

cpFloat
SegmentShape::GetMoment(cpFloat mass) const
{
  return cpMomentForSegment(mass, _startPos, _endPos, 0.0f);
}