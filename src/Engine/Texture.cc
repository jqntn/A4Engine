#include <Engine/Renderer.hh>
#include <Engine/Surface.hh>
#include <Engine/Texture.hh>
#include <SDL.h>
#include <SDL_image.h>

Texture::Texture(Texture&& texture) noexcept
  : m_filepath(std::move(texture.m_filepath))
{
  m_texture = texture.m_texture;
  texture.m_texture = nullptr;
}

Texture::~Texture()
{
  if (m_texture)
    SDL_DestroyTexture(m_texture);
}

const std::string&
Texture::GetFilepath() const
{
  return m_filepath;
}

SDL_Texture*
Texture::GetHandle() const
{
  return m_texture;
}

SDL_Rect
Texture::GetRect() const
{
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &rect.w, &rect.h);

  return rect;
}

Texture&
Texture::operator=(Texture&& texture) noexcept
{
  m_filepath = std::move(texture.m_filepath);
  std::swap(m_texture, texture.m_texture);
  return *this;
}

Texture
Texture::LoadFromFile(Renderer& renderer, const std::string& filepath)
{
  return LoadFromSurface(renderer, Surface::LoadFromFile(filepath));
}

Texture
Texture::LoadFromSurface(Renderer& renderer, const Surface& surface)
{
  SDL_Texture* texture =
    SDL_CreateTextureFromSurface(renderer.GetHandle(), surface.GetHandle());
  return Texture(texture, surface.GetFilepath());
}

Texture::Texture(SDL_Texture* texture, std::string filepath)
  : m_texture(texture)
  , m_filepath(std::move(filepath))
{
}