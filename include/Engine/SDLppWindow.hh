#pragma once

#include <SDL.h>
#include <string>

class SDLppWindow
{
public:
  SDLppWindow(const std::string& title,
              int width,
              int height,
              Uint32 flags = 0);
  SDLppWindow(const std::string& title,
              int x,
              int y,
              int width,
              int height,
              Uint32 flags = 0);
  SDLppWindow(const SDLppWindow&) = delete;
  SDLppWindow(SDLppWindow&& window) noexcept;
  ~SDLppWindow();

  SDL_Window* GetHandle() const;

  SDLppWindow& operator=(const SDLppWindow&) = delete;
  SDLppWindow& operator=(SDLppWindow&& window) noexcept;

private:
  SDL_Window* m_window;
};