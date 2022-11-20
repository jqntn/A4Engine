#include <Engine/SDLpp.hh>

#include <SDL.h>

SDLpp::SDLpp()
{
  SDL_Init(0);
}

SDLpp::~SDLpp()
{
  SDL_Quit();
}

bool
SDLpp::PollEvent(SDL_Event* event)
{
  return SDL_PollEvent(event);
}