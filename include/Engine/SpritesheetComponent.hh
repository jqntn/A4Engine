#pragma once

#include <Engine/Spritesheet.hh>
#include <Engine/Vector2.hh>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class AnimationSystem;
class Sprite;

class SpritesheetComponent
{
  friend AnimationSystem;

public:
  SpritesheetComponent(std::shared_ptr<const Spritesheet> spritesheet,
                       std::shared_ptr<Sprite> targetSprite);

  void PlayAnimation(const std::string& animName);
  void PlayAnimation(std::size_t animIndex);

private:
  void Update(float elapsedTime);

  std::size_t m_currentAnimation;
  std::shared_ptr<Sprite> m_targetSprite;
  std::shared_ptr<const Spritesheet> m_spritesheet;
  float m_timeAccumulator;
  unsigned int m_currentFrameIndex;
};