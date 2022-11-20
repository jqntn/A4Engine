#pragma once

#include <Renderer.h>
#include <Sprite.h>
#include <Transform.h>

#include <entt/entt.hpp>

class Systems
{
public:
  static void RenderSystem(entt::registry& registry, Renderer& renderer);
  static void VelocitySystem(entt::registry& registry, float elapsedTime);
};