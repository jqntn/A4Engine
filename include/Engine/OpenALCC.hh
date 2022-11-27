#pragma once

#include <AL/al.h>
#include <AL/alc.h>

class OpenALCC
{
public:
  OpenALCC();
  ~OpenALCC();

private:
  ALCdevice* _device;
  ALCcontext* _context;
};