#pragma once

#include <SDL.h>

class Renderer;
class Surface;

class Texture
{
public:
  Texture(const Texture&) = delete;
  Texture(Texture&&) noexcept;
  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&&) noexcept;
  ~Texture();

  SDL_Texture* GetHandle() const;
  SDL_Rect GetRect() const;

  static Texture LoadFromFile(Renderer& renderer, const char* path);
  static Texture LoadFromSurface(Renderer& renderer, const Surface& surface);

private:
  Texture(SDL_Texture* texture);

  SDL_Texture* _texture;
};