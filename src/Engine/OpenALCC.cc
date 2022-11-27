#include <Engine/OpenALCC.hh>

OpenALCC::OpenALCC()
{
  _device = alcOpenDevice(nullptr);

  _context = alcCreateContext(_device, nullptr);
  alcMakeContextCurrent(_context);
}

OpenALCC::~OpenALCC()
{
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(_context);

  alcCloseDevice(_device);
}