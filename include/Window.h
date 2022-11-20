#pragma once

#include <SDL.h>

class Window
{
public:
  Window(const char* title, int w, int h, Uint32 flags = 0);
  Window(const char* title, int x, int y, int w, int h, Uint32 flags = 0);

  Window(const Window&) = delete;
  Window(Window&&) noexcept;
  Window& operator=(const Window&) = delete;
  Window& operator=(Window&&) noexcept;
  ~Window();

  SDL_Window* GetHandle() const;

  bool IsOpen() const;
  void Close();

private:
  SDL_Window* _window;

  bool _isOpen = true;
};