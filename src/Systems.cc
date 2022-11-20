#include <Systems.h>

#include <Components.h>
#include <Matrix3.h>

void
Systems::RenderSystem(entt::registry& registry, Renderer& renderer)
{
  auto cameras = registry.view<Transform, CameraComponent>();
  auto sprites = registry.view<Transform, Sprite>();

  Transform curCamTransform;

  for (auto& entity : cameras) {
    auto& transform = cameras.get<Transform>(entity);
    curCamTransform = std::move(transform);
  }

  for (auto& entity : sprites) {
    auto& transform = sprites.get<Transform>(entity);
    auto& sprite = sprites.get<Sprite>(entity);

    auto transfMat = Matrix3::TRS(
      transform.GetPosition(), transform.GetRotation(), transform.GetScale());

    auto camMat = Matrix3::SRT(curCamTransform.GetScale(),
                               curCamTransform.GetRotation(),
                               curCamTransform.GetPosition())
                    .Inverse();

    auto newTransfMat = camMat * transfMat;

    sprite.Draw(renderer, newTransfMat);
  }
}

void
Systems::VelocitySystem(entt::registry& registry, float elapsedTime)
{
  auto view = registry.view<Transform, VelocityComponent>();

  for (auto& entity : view) {
    auto& transform = view.get<Transform>(entity);

    auto& pos = transform.GetPosition();
    auto& vel = view.get<VelocityComponent>(entity);

    auto newPos =
      Vector2{ pos.x + vel.x * elapsedTime, pos.y + vel.y * elapsedTime };

    transform.SetPosition(newPos);
  }
}