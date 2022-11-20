#pragma once

#include <SDL.h>

class Texture;
class Window;

class Renderer
{
public:
  Renderer(const Window& window);

  Renderer(const Renderer&) = delete;
  Renderer(Renderer&&) noexcept;
  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) noexcept;
  ~Renderer();

  SDL_Renderer* GetHandle() const;

  void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void Clear();
  void Present();
  void RenderCopy(const Texture& texture);
  void RenderCopy(const Texture& texture, const SDL_Rect& dst);
  void RenderCopy(const Texture& texture,
                  const SDL_Rect& src,
                  const SDL_Rect& dst);

private:
  SDL_Renderer* _renderer;
};