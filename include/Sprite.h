#pragma once

#include <Vector2.h>

#include <SDL.h>

#include <memory>

class Renderer;
class Texture;
class Transform;
class Matrix3;

class Sprite
{
public:
  Sprite(const std::shared_ptr<Texture>& texture);
  Sprite(const std::shared_ptr<Texture>& texture, const SDL_Rect& rect);

  Sprite(const Sprite&) = default;
  Sprite(Sprite&&) = default;
  Sprite& operator=(const Sprite&) = default;
  Sprite& operator=(Sprite&&) = default;
  ~Sprite() = default;

  const Vector2& GetOrigin() const;

  int GetWidth() const;
  int GetHeight() const;

  void SetOrigin(const Vector2& origin);
  void SetRect(SDL_Rect rect);

  void Resize(int width, int height);
  void Draw(Renderer& renderer, const Matrix3& matrix);

private:
  std::shared_ptr<Texture> _texture;

  SDL_Rect _rect;

  Vector2 _origin{ .5f, .5f };

  int _width;
  int _height;
};