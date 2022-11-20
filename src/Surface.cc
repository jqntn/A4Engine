#include <Surface.h>

#include <SDL_image.h>

#include <iostream>

Surface::Surface(SDL_Surface* surface)
  : _surface(surface)
{
}

Surface::~Surface()
{
  SDL_FreeSurface(_surface);
}

Surface::Surface(Surface&& surface) noexcept
  : _surface(std::exchange(surface._surface, nullptr))
{
}

Surface&
Surface::operator=(Surface&& surface) noexcept
{
  std::swap(_surface, surface._surface);
  return *this;
}

SDL_Surface*
Surface::GetHandle() const
{
  return _surface;
}

Surface
Surface::LoadFromFile(const char* path)
{
  auto surface = IMG_Load(path);

  if (!surface)
    std::cerr << IMG_GetError() << std::endl;

  return Surface(surface);
}