#include <PhysicsSystem.h>

#include <Transform.h>
#include <chipmunk/chipmunk.h>

PhysicsSystem::PhysicsSystem(entt::registry& registry)
  : _registry(registry)
{
  _space = cpSpaceNew();

  SetGravity(981);
  SetDamping(.5f);
}

PhysicsSystem::~PhysicsSystem()
{
  for (const auto& i : _bodies)
    RemoveBody(i);

  cpSpaceFree(_space);
}

cpSpace*
PhysicsSystem::GetSpace() const
{
  return _space;
}

cpFloat
PhysicsSystem::GetGravity()
{
  return cpSpaceGetGravity(_space).y;
}

cpFloat
PhysicsSystem::GetDamping()
{
  return cpSpaceGetDamping(_space);
}

void
PhysicsSystem::SetGravity(float value)
{
  cpSpaceSetGravity(_space, cpv(0, value));
}

void
PhysicsSystem::SetDamping(float value)
{
  cpSpaceSetDamping(_space, value);
}

void
PhysicsSystem::AddBody(const RigidBodyComponent& body)
{
  cpSpaceAddBody(_space, body.GetBody());
  _bodies.push_back(body);
}

void
PhysicsSystem::RemoveBody(const RigidBodyComponent& body)
{
  cpSpaceRemoveBody(_space, body.GetBody());
  body.~RigidBodyComponent();
}

void
PhysicsSystem::Step(float deltaTime)
{
  _physicsAccumulator += deltaTime;
  while (_physicsAccumulator >= _timeStep) {
    cpSpaceStep(_space, _timeStep);
    _physicsAccumulator -= _timeStep;
  }
}

void
PhysicsSystem::Update(float deltaTime)
{
  Step(deltaTime);

  auto view = _registry.view<RigidBodyComponent, Transform>();

  for (auto& entity : view) {
    auto& entityRigidBody = view.get<RigidBodyComponent>(entity);
    auto& entityTransform = view.get<Transform>(entity);

    auto pos = entityRigidBody.GetPos();
    auto rot = entityRigidBody.GetAngle() * Rad2Deg;

    entityTransform.SetPosition(Vector2(pos.x, pos.y));
    entityTransform.SetRotation(rot);
  }
}