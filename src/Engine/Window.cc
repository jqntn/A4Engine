#include <Engine/Window.hh>
#include <SDL.h>

Window::Window(const std::string& title, int width, int height, Uint32 flags)
  : Window(title,
           SDL_WINDOWPOS_CENTERED,
           SDL_WINDOWPOS_CENTERED,
           width,
           height,
           flags)
{
}

Window::Window(const std::string& title,
               int x,
               int y,
               int width,
               int height,
               Uint32 flags)
{
  m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
}

Window::Window(Window&& window) noexcept
{
  m_window = window.m_window;
  window.m_window = nullptr;
}

Window::~Window()
{
  if (m_window)
    SDL_DestroyWindow(m_window);
}

SDL_Window*
Window::GetHandle() const
{
  return m_window;
}

Window&
Window::operator=(Window&& window) noexcept
{
  std::swap(m_window, window.m_window);
  return *this;
}