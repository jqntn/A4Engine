#pragma once

union SDL_Event;

class SDLCC
{
public:
  SDLCC();
  SDLCC(const SDLCC&) = delete;
  SDLCC(SDLCC&&) = delete;
  ~SDLCC();

  SDLCC& operator=(const SDLCC&) = delete;
  SDLCC& operator=(SDLCC&&) = delete;

  static bool PollEvent(SDL_Event* event);
};