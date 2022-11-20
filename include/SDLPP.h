#pragma once

#include <SDL.h>

class SDLPP
{
public:
  SDLPP();
  ~SDLPP();

  SDLPP(const SDLPP&) = delete;
  SDLPP(SDLPP&&) = delete;
  SDLPP& operator=(const SDLPP&) = delete;
  SDLPP& operator=(SDLPP&&) = delete;

  const SDL_Event& GetEvent() const;

  bool PollEvent();

private:
  const Uint32 _flags{};

  SDL_Event _event{};
};