#pragma once

#include <chipmunk/chipmunk.h>

#include <vector>

class Vector2;
class Shape;

struct VelocityComponent
{
  float x{};
  float y{};
};

struct CameraComponent
{};

class RigidBodyComponent
{
public:
  RigidBodyComponent(float mass);
  RigidBodyComponent(const RigidBodyComponent&) = default;
  RigidBodyComponent(RigidBodyComponent&&) = default;
  RigidBodyComponent& operator=(const RigidBodyComponent&) = default;
  RigidBodyComponent& operator=(RigidBodyComponent&&) = default;
  virtual ~RigidBodyComponent();

  cpBody* GetBody() const;

  cpVect GetPos() const;
  cpFloat GetAngle() const;

  void SetPos(Vector2 value);

  void AddShape(Shape* shape, cpSpace* space);
  void RemoveShape(Shape* shape);
  void SetMoment();

private:
  cpBody* _body;
  std::vector<Shape*> _shapes;
};