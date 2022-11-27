#pragma once

#include <SDL.h>
#include <string>

class Surface
{
public:
  Surface(int width, int height);
  Surface(const Surface&) = delete;
  Surface(Surface&& surface) noexcept;
  ~Surface();

  void FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  const std::string& GetFilepath() const;
  SDL_Surface* GetHandle() const;
  Uint8* GetPixels();
  const Uint8* GetPixels() const;

  bool IsValid() const;

  Surface& operator=(const Surface&) = delete;
  Surface& operator=(Surface&& surface) noexcept;

  static Surface LoadFromFile(std::string filepath);

private:
  Surface(SDL_Surface* surface, std::string filepath = "");

  SDL_Surface* m_surface;
  std::string m_filepath;
};