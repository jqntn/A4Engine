#pragma once

#include <SDL.h>
#include <string>

class Window
{
public:
  Window(const std::string& title, int width, int height, Uint32 flags = 0);
  Window(const std::string& title,
         int x,
         int y,
         int width,
         int height,
         Uint32 flags = 0);
  Window(const Window&) = delete;
  Window(Window&& window) noexcept;
  ~Window();

  SDL_Window* GetHandle() const;

  Window& operator=(const Window&) = delete;
  Window& operator=(Window&& window) noexcept;

private:
  SDL_Window* m_window;
};