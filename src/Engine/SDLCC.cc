#include <Engine/SDLCC.hh>

#include <SDL.h>

SDLCC::SDLCC()
{
  SDL_Init(0);
}

SDLCC::~SDLCC()
{
  SDL_Quit();
}

bool
SDLCC::PollEvent(SDL_Event* event)
{
  return SDL_PollEvent(event);
}