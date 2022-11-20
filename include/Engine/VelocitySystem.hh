#pragma once

#include <entt/fwd.hpp>

class VelocitySystem
{
public:
  VelocitySystem(entt::registry& registry);

  void Update(float deltaTime);

private:
  entt::registry& m_registry;
};