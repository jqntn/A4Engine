#include <Engine/Surface.hh>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <iostream>

Surface::Surface(int width, int height)
{
  m_surface = SDL_CreateRGBSurfaceWithFormat(
    0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
}

Surface::Surface(Surface&& surface) noexcept
  : m_filepath(std::move(surface.m_filepath))
{
  m_surface = surface.m_surface;
  surface.m_surface = nullptr;
}

Surface::~Surface()
{
  if (m_surface)
    SDL_FreeSurface(m_surface);
}

void
Surface::FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  assert(m_surface);
  SDL_FillRect(m_surface, &rect, SDL_MapRGBA(m_surface->format, r, g, b, a));
}

const std::string&
Surface::GetFilepath() const
{
  return m_filepath;
}

SDL_Surface*
Surface::GetHandle() const
{
  return m_surface;
}

Uint8*
Surface::GetPixels()
{
  return static_cast<Uint8*>(m_surface->pixels);
}

const Uint8*
Surface::GetPixels() const
{
  return static_cast<const Uint8*>(m_surface->pixels);
}

bool
Surface::IsValid() const
{
  return m_surface != nullptr;
}

Surface&
Surface::operator=(Surface&& surface) noexcept
{
  m_filepath = std::move(surface.m_filepath);
  std::swap(m_surface, surface.m_surface);
  return *this;
}

Surface
Surface::LoadFromFile(std::string filepath)
{
  SDL_Surface* surface = IMG_Load(filepath.c_str());
  if (!surface)
    std::cerr << IMG_GetError() << std::endl;

  return Surface(surface, std::move(filepath));
}

Surface::Surface(SDL_Surface* surface, std::string filepath)
  : m_surface(surface)
  , m_filepath(std::move(filepath))
{
}