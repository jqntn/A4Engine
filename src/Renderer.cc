#include <Renderer.h>

#include <Texture.h>
#include <Window.h>

#include <memory>

Renderer::Renderer(const Window& window)
{
  _renderer = SDL_CreateRenderer(window.GetHandle(), 0, 0);
}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(_renderer);
}

Renderer::Renderer(Renderer&& renderer) noexcept
  : _renderer(std::exchange(renderer._renderer, nullptr))
{
}

Renderer&
Renderer::operator=(Renderer&& renderer) noexcept
{
  std::swap(_renderer, renderer._renderer);
  return *this;
}

SDL_Renderer*
Renderer::GetHandle() const
{
  return _renderer;
}

void
Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void
Renderer::Clear()
{
  SDL_RenderClear(_renderer);
}

void
Renderer::Present()
{
  SDL_RenderPresent(_renderer);
}

void
Renderer::RenderCopy(const Texture& texture)
{
  SDL_RenderCopy(_renderer, texture.GetHandle(), nullptr, nullptr);
}

void
Renderer::RenderCopy(const Texture& texture, const SDL_Rect& dst)
{
  SDL_RenderCopy(_renderer, texture.GetHandle(), nullptr, &dst);
}

void
Renderer::RenderCopy(const Texture& texture,
                     const SDL_Rect& src,
                     const SDL_Rect& dst)
{
  SDL_RenderCopy(_renderer, texture.GetHandle(), &src, &dst);
}