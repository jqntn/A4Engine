#pragma once

#include <Engine/Renderable.hh>
#include <Engine/Vector2.hh>
#include <SDL.h>
#include <memory>

class Renderer;
class Texture;
class Transform;

class Sprite : public Renderable
{
public:
  Sprite(std::shared_ptr<const Texture> texture);
  Sprite(std::shared_ptr<const Texture> texture, const SDL_Rect& rect);
  Sprite(const Sprite&) = default;
  Sprite(Sprite&&) = default;
  ~Sprite() = default;

  void Draw(Renderer& renderer, const Matrix3f& matrix) override;

  int GetHeight() const;
  const Vector2f& GetOrigin() const;
  int GetWidth() const;

  void Resize(int width, int height);

  void SetOrigin(const Vector2f& origin);
  void SetRect(SDL_Rect rect);

  Sprite& operator=(const Sprite&) = default;
  Sprite& operator=(Sprite&&) = default;

private:
  std::shared_ptr<const Texture> m_texture;
  SDL_Rect m_rect;
  Vector2f m_origin;
  int m_width;
  int m_height;
};