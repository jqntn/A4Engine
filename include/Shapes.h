#pragma once

#include <chipmunk/chipmunk.h>

class Shape
{
public:
  Shape() = default;
  Shape(const Shape&) = default;
  Shape(Shape&&) = default;
  Shape& operator=(const Shape&) = default;
  Shape& operator=(Shape&&) = default;
  virtual ~Shape() = default;

  cpShape* GetShape() const;

  virtual cpFloat GetMoment(cpFloat mass) const = 0;
  virtual cpShape* CreateShape(cpBody* body) = 0;

protected:
  cpShape* _shape{};
};

class CircleShape : public Shape
{
public:
  CircleShape(float radius, cpVect offset);
  CircleShape(const CircleShape&) = default;
  CircleShape(CircleShape&&) = default;
  CircleShape& operator=(const CircleShape&) = default;
  CircleShape& operator=(CircleShape&&) = default;
  virtual ~CircleShape() = default;

  cpFloat GetMoment(cpFloat mass) const override;
  cpShape* CreateShape(cpBody* body) override;

private:
  float _radius = 1;
  cpVect _offset{};
};

class BoxShape : public Shape
{
public:
  BoxShape(float width, float height);
  BoxShape(const BoxShape&) = default;
  BoxShape(BoxShape&&) = default;
  BoxShape& operator=(const BoxShape&) = default;
  BoxShape& operator=(BoxShape&&) = default;
  virtual ~BoxShape() = default;

  cpFloat GetMoment(cpFloat mass) const override;
  cpShape* CreateShape(cpBody* body) override;

private:
  float _width = 100;
  float _height = 100;
};

class SegmentShape : public Shape
{
public:
  SegmentShape(cpVect vector1, cpVect vector2);
  SegmentShape(const SegmentShape&) = default;
  SegmentShape(SegmentShape&&) = default;
  SegmentShape& operator=(const SegmentShape&) = default;
  SegmentShape& operator=(SegmentShape&&) = default;
  virtual ~SegmentShape() = default;

  cpFloat GetMoment(cpFloat mass) const override;
  cpShape* CreateShape(cpBody* body) override;

private:
  cpVect _startPos;
  cpVect _endPos;
};