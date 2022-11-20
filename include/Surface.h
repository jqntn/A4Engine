#pragma once

#include <SDL.h>

class Surface
{
public:
  Surface(const Surface&) = delete;
  Surface(Surface&&) noexcept;
  Surface& operator=(const Surface&) = delete;
  Surface& operator=(Surface&&) noexcept;
  ~Surface();

  SDL_Surface* GetHandle() const;

  static Surface LoadFromFile(const char* path);

private:
  Surface(SDL_Surface* surface);

  SDL_Surface* _surface;
};