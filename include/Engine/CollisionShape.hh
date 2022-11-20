#pragma once

#include <Engine/Matrix3.hh>
#include <Engine/Vector2.hh>
#include <vector>

class ChipmunkBody;
class ChipmunkShape;
class Model;

struct CollisionShape
{
  virtual ~CollisionShape();

  virtual ChipmunkShape Build(ChipmunkBody& body,
                              const Vector2f& offset = Vector2f(0.f,
                                                                0.f)) const = 0;
  virtual float ComputeMoment(float mass,
                              const Vector2f& offset = Vector2f(0.f,
                                                                0.f)) const = 0;

  float friction = 0.9f;
};

struct BoxShape : CollisionShape
{
  BoxShape(float width, float height, float radius = 0.f);
  BoxShape(float x, float y, float width, float height, float radius = 0.f);

  ChipmunkShape Build(ChipmunkBody& body,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;
  float ComputeMoment(float mass,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;

  float x, y, width, height;
  float radius;
};

struct CircleShape : CollisionShape
{
  CircleShape(float radius);

  ChipmunkShape Build(ChipmunkBody& body,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;
  float ComputeMoment(float mass,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;

  float radius;
};

struct ConvexShape : CollisionShape
{
  ConvexShape(std::vector<Vector2f> pos, float radius = 0.f);
  ConvexShape(const Model& model,
              Matrix3f transformation = Matrix3f::Identity(),
              float radius = 0.f);

  ChipmunkShape Build(ChipmunkBody& body,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;
  float ComputeMoment(float mass,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;

  std::vector<Vector2f> positions;
  float radius;
};

struct SegmentShape : CollisionShape
{
  SegmentShape(const Vector2f& from, const Vector2f& to, float radius = 0.f);

  ChipmunkShape Build(ChipmunkBody& body,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;
  float ComputeMoment(float mass,
                      const Vector2f& offset = Vector2f(0.f,
                                                        0.f)) const override;

  Vector2f from;
  Vector2f to;
  float radius;
};