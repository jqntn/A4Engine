#pragma once

#include <SDL.h>
#include <string>

class SDLppSurface
{
public:
  SDLppSurface(int width, int height);
  SDLppSurface(const SDLppSurface&) = delete;
  SDLppSurface(SDLppSurface&& surface) noexcept;
  ~SDLppSurface();

  void FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  const std::string& GetFilepath() const;
  SDL_Surface* GetHandle() const;
  Uint8* GetPixels();
  const Uint8* GetPixels() const;

  bool IsValid() const;

  SDLppSurface& operator=(const SDLppSurface&) = delete;
  SDLppSurface& operator=(SDLppSurface&& surface) noexcept;

  static SDLppSurface LoadFromFile(std::string filepath);

private:
  SDLppSurface(SDL_Surface* surface, std::string filepath = "");

  SDL_Surface* m_surface;
  std::string m_filepath;
};