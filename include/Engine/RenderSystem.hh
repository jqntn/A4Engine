#pragma once

#include <entt/fwd.hpp>

class SDLppRenderer;

class RenderSystem
{
public:
  RenderSystem(SDLppRenderer& renderer, entt::registry& registry);

  void Update(float deltaTime);

private:
  SDLppRenderer& m_renderer;
  entt::registry& m_registry;
};