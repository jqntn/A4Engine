#include <Engine/Sound.hh>

#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

#include <stdexcept>
#include <vector>

Sound::Sound(std::string filepath, ALuint buffer, ALuint source)
  : _filepath(filepath)
  , _buffer(buffer)
  , _source(source)
{
}

Sound::~Sound() {}

const std::string&
Sound::GetFilepath() const
{
  return _filepath;
}

const ALuint&
Sound::GetBuffer() const
{
  return _buffer;
}

const ALuint&
Sound::GetSource() const
{
  return _source;
}

void
Sound::Play(bool loop)
{
  alSourcei(_source, AL_LOOPING, loop);

  alSourcePlay(_source);
}

Sound
Sound::LoadFromFile(const std::string& filepath)
{
  drwav wav;

  ALuint buffer;
  ALuint source;

  if (!drwav_init_file(&wav, filepath.c_str(), nullptr))
    throw std::runtime_error("failed to load sound file");

  std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
  drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

  alGenBuffers(1, &buffer);
  alBufferData(buffer,
               (wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
               samples.data(),
               samples.size() * sizeof(std::int16_t),
               wav.sampleRate);

  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);

  drwav_uninit(&wav);

  return Sound(filepath, buffer, source);
}