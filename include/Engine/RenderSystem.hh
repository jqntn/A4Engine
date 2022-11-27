#pragma once

#include <entt/fwd.hpp>

class Renderer;

class RenderSystem
{
public:
  RenderSystem(Renderer& renderer, entt::registry& registry);

  void Update(float deltaTime);

private:
  Renderer& m_renderer;
  entt::registry& m_registry;
};