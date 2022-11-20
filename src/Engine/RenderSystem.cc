#include <Engine/CameraComponent.hh>
#include <Engine/GraphicsComponent.hh>
#include <Engine/RenderSystem.hh>
#include <Engine/Renderable.hh>
#include <Engine/Transform.hh>
#include <entt/entt.hpp>
#include <fmt/color.h>
#include <fmt/core.h>

RenderSystem::RenderSystem(SDLppRenderer& renderer, entt::registry& registry)
  : m_renderer(renderer)
  , m_registry(registry)
{
}

void
RenderSystem::Update(float)
{
  Matrix3f cameraMatrix = Matrix3f::Identity();

  auto cameraView = m_registry.view<Transform, CameraComponent>();
  bool cameraFound = false;
  for (entt::entity entity : cameraView) {
    if (cameraFound)
      fmt::print(
        stderr, fg(fmt::color::red), "warning: multiple camera found\n");

    Transform& entityTransform = cameraView.get<Transform>(entity);
    cameraMatrix = entityTransform.GetTransformMatrix();
    cameraMatrix = cameraMatrix.Inverse();
    cameraFound = true;
  }

  if (!cameraFound)
    fmt::print(stderr, fg(fmt::color::red), "warning: no camera found\n");

  auto view = m_registry.view<Transform, GraphicsComponent>();
  for (entt::entity entity : view) {
    Transform& entityTransform = view.get<Transform>(entity);
    GraphicsComponent& entityGraphics = view.get<GraphicsComponent>(entity);

    Matrix3f entityMatrix = entityTransform.GetTransformMatrix();
    entityGraphics.renderable->Draw(m_renderer, cameraMatrix * entityMatrix);
  }
}