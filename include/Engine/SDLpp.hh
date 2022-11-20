#pragma once

union SDL_Event;

class SDLpp
{
public:
  SDLpp();
  SDLpp(const SDLpp&) = delete;
  SDLpp(SDLpp&&) = delete;
  ~SDLpp();

  SDLpp& operator=(const SDLpp&) = delete;
  SDLpp& operator=(SDLpp&&) = delete;

  static bool PollEvent(SDL_Event* event);
};