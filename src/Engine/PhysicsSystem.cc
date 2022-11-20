#include <Engine/PhysicsSystem.hh>
#include <Engine/RigidBodyComponent.hh>
#include <Engine/Transform.hh>
#include <entt/entt.hpp>

PhysicsSystem::PhysicsSystem(entt::registry& registry)
  : m_registry(registry)
  , m_accumulator(0.f)
  , m_timestep(1.f / 50.f)
{
  if (s_instance != nullptr)
    throw std::runtime_error("only one PhysicsSystem can be created");

  s_instance = this;
}

PhysicsSystem::~PhysicsSystem()
{
  m_registry.clear<RigidBodyComponent>();

  s_instance = nullptr;
}

ChipmunkSpace&
PhysicsSystem::GetSpace()
{
  return *this;
}

void
PhysicsSystem::Update(float deltaTime)
{
  m_accumulator += deltaTime;
  while (m_accumulator >= m_timestep) {
    Step(m_timestep);
    m_accumulator -= m_timestep;
  }

  auto view = m_registry.view<Transform, RigidBodyComponent>();
  for (entt::entity entity : view) {
    Transform& entityTransform = view.get<Transform>(entity);
    RigidBodyComponent& entityBody = view.get<RigidBodyComponent>(entity);

    entityTransform.SetPosition(entityBody.GetPosition());
    entityTransform.SetRotation(entityBody.GetRotation());
  }
}

PhysicsSystem*
PhysicsSystem::Instance()
{
  return s_instance;
}

PhysicsSystem* PhysicsSystem::s_instance = nullptr;