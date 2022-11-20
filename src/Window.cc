#include <Window.h>

#include <memory>

Window::Window(const char* title, int w, int h, Uint32 flags)
  : Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags)
{
}

Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags)
{
  _window = SDL_CreateWindow(title, x, y, w, h, flags);
}

Window::~Window()
{
  SDL_DestroyWindow(_window);
}

Window::Window(Window&& window) noexcept
  : _window(std::exchange(window._window, nullptr))
{
}

Window&
Window::operator=(Window&& window) noexcept
{
  std::swap(_window, window._window);
  return *this;
}

SDL_Window*
Window::GetHandle() const
{
  return _window;
}

bool
Window::IsOpen() const
{
  return _isOpen;
}

void
Window::Close()
{
  _isOpen = false;
}