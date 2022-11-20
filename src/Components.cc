#include <Components.h>

#include <Shapes.h>
#include <Vector2.h>

RigidBodyComponent::RigidBodyComponent(float mass)
{
  _body = cpBodyNew(mass, 0);
}

RigidBodyComponent::~RigidBodyComponent()
{
  cpBodyFree(_body);
}

cpBody*
RigidBodyComponent::GetBody() const
{
  return _body;
}

cpVect
RigidBodyComponent::GetPos() const
{
  return cpBodyGetPosition(_body);
}

cpFloat
RigidBodyComponent::GetAngle() const
{
  return cpBodyGetAngle(_body);
}

void
RigidBodyComponent::SetPos(Vector2 value)
{
  cpBodySetPosition(_body, cpVect(value.x, value.y));
}

void
RigidBodyComponent::AddShape(Shape* shape, cpSpace* space)
{
  shape->CreateShape(_body);
  _shapes.push_back(shape);
  cpSpaceAddShape(space, shape->GetShape());
  cpSpaceAddBody(space, _body);
  SetMoment();
}

void
RigidBodyComponent::RemoveShape(Shape* shape)
{
  _shapes.erase(std::find(_shapes.begin(), _shapes.end(), shape));
}

void
RigidBodyComponent::SetMoment()
{
  float tmp = 0;
  for (const auto& shape : _shapes) {
    tmp += (float)shape->GetMoment(cpBodyGetMass(_body));
  }

  cpBodySetMoment(_body, tmp);
}