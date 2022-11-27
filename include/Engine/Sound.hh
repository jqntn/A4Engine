#pragma once

#include <AL/al.h>

#include <string>

class Sound
{
public:
  Sound(const Sound&) = default;
  Sound(Sound&&) = default;
  Sound& operator=(const Sound&) = default;
  Sound& operator=(Sound&&) = default;
  virtual ~Sound();

  const std::string& GetFilepath() const;

  const ALuint& GetBuffer() const;
  const ALuint& GetSource() const;

  void Play(bool loop = false);

  static Sound LoadFromFile(const std::string& filepath);

private:
  Sound(std::string filepath, ALuint buffer, ALuint source);

  std::string _filepath;

  ALuint _buffer;
  ALuint _source;
};