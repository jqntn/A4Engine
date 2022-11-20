#include <Engine/Sprite.hh>
#include <Engine/SpritesheetComponent.hh>
#include <SDL.h>
#include <fmt/color.h>
#include <fmt/core.h>

SpritesheetComponent::SpritesheetComponent(
  std::shared_ptr<const Spritesheet> spritesheet,
  std::shared_ptr<Sprite> targetSprite)
  : m_currentAnimation(0)
  , m_targetSprite(std::move(targetSprite))
  , m_spritesheet(std::move(spritesheet))
  , m_timeAccumulator(0.f)
  , m_currentFrameIndex(0)
{
}

void
SpritesheetComponent::PlayAnimation(const std::string& animName)
{
  auto indexOpt = m_spritesheet->GetAnimationByName(animName);
  if (!indexOpt.has_value()) {
    fmt::print(
      stderr, fg(fmt::color::red), "animation \"{}\" not found\n", animName);
    return;
  }

  PlayAnimation(indexOpt.value());
}

void
SpritesheetComponent::PlayAnimation(std::size_t animIndex)
{
  if (m_currentAnimation == animIndex)
    return;

  m_currentAnimation = animIndex;
  m_currentFrameIndex = 0;
  m_timeAccumulator = 0.f;
}

void
SpritesheetComponent::Update(float elapsedTime)
{
  if (m_currentAnimation >= m_spritesheet->GetAnimationCount())
    return;

  const Spritesheet::Animation& anim =
    m_spritesheet->GetAnimation(m_currentAnimation);

  m_timeAccumulator += elapsedTime;
  while (m_timeAccumulator >= anim.frameDuration) {
    m_timeAccumulator -= anim.frameDuration;
    if (++m_currentFrameIndex >= anim.frameCount)
      m_currentFrameIndex = 0;

    SDL_Rect rect;
    rect.x = anim.start.x + anim.size.x * m_currentFrameIndex;
    rect.y = anim.start.y;
    rect.w = anim.size.x;
    rect.h = anim.size.y;

    m_targetSprite->SetRect(rect);
  }
}