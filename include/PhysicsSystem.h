#pragma once

#include <Components.h>

#include <entt/entt.hpp>

#include <vector>

class PhysicsSystem
{
public:
  PhysicsSystem(entt::registry& registry);
  PhysicsSystem(const PhysicsSystem&) = delete;
  PhysicsSystem(PhysicsSystem&&) = delete;
  PhysicsSystem& operator=(const PhysicsSystem&) = delete;
  PhysicsSystem& operator=(PhysicsSystem&&) = delete;
  virtual ~PhysicsSystem();

  cpSpace* GetSpace() const;

  cpFloat GetGravity();
  cpFloat GetDamping();

  void SetGravity(float value);
  void SetDamping(float value);

  void AddBody(const RigidBodyComponent& body);
  void RemoveBody(const RigidBodyComponent& body);

  void Step(float deltaTime);

  void Update(float deltaTime);

private:
  entt::registry& _registry;

  cpSpace* _space;

  std::vector<RigidBodyComponent> _bodies{};

  float _timeStep = 1.f / 50;
  float _physicsAccumulator{};
};