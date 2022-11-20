#pragma once

#include <entt/fwd.hpp>

class AnimationSystem
{
public:
  AnimationSystem(entt::registry& registry);

  void Update(float deltaTime);

private:
  entt::registry& m_registry;
};