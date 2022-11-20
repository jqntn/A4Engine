#include <Engine/RigidBodyComponent.hh>
#include <Engine/Transform.hh>
#include <Engine/VelocityComponent.hh>
#include <Engine/VelocitySystem.hh>
#include <entt/entt.hpp>

VelocitySystem::VelocitySystem(entt::registry& registry)
  : m_registry(registry)
{
}

void
VelocitySystem::Update(float deltaTime)
{
  auto view = m_registry.view<Transform, VelocityComponent>(
    entt::exclude<VelocityComponent>);
  for (entt::entity entity : view) {
    Transform& entityTransform = view.get<Transform>(entity);
    VelocityComponent& entityVelocity = view.get<VelocityComponent>(entity);

    entityTransform.Translate(entityVelocity.linearVel * deltaTime);
    entityTransform.Rotate(entityVelocity.angularVel * deltaTime);
  }
}