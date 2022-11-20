#include <SDLPP.h>

SDLPP::SDLPP()
{
  SDL_Init(_flags);
}

SDLPP::~SDLPP()
{
  SDL_Quit();
}

const SDL_Event&
SDLPP::GetEvent() const
{
  return _event;
}

bool
SDLPP::PollEvent()
{
  return SDL_PollEvent(&_event);
}