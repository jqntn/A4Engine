#include <Texture.h>

#include <Renderer.h>
#include <Surface.h>

#include <SDL_image.h>

#include <memory>

Texture::Texture(SDL_Texture* texture)
  : _texture(texture)
{
}

Texture::~Texture()
{
  SDL_DestroyTexture(_texture);
}

Texture::Texture(Texture&& texture) noexcept
  : _texture(std::exchange(texture._texture, nullptr))
{
}

Texture&
Texture::operator=(Texture&& texture) noexcept
{
  std::swap(_texture, texture._texture);
  return *this;
}

SDL_Texture*
Texture::GetHandle() const
{
  return _texture;
}

SDL_Rect
Texture::GetRect() const
{
  SDL_Rect rect{};
  rect.x = 0;
  rect.y = 0;

  SDL_QueryTexture(_texture, nullptr, nullptr, &rect.w, &rect.h);

  return rect;
}

Texture
Texture::LoadFromFile(Renderer& renderer, const char* path)
{
  return LoadFromSurface(renderer, Surface::LoadFromFile(path));
}

Texture
Texture::LoadFromSurface(Renderer& renderer, const Surface& surface)
{
  auto tex =
    SDL_CreateTextureFromSurface(renderer.GetHandle(), surface.GetHandle());

  return Texture(tex);
}