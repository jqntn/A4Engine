#define DR_WAV_IMPLEMENTATION

#include <AL/al.h>
#include <AL/alc.h>
#include <dr_wav.h>
#include <fmt/core.h>
#include <vector>

int
main()
{
  auto deviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
  std::vector<std::string> devices;

  while (true) {
    auto length = std::strlen(deviceList);
    if (length == 0)
      break;

    devices.emplace_back(deviceList, length);

    deviceList += length + 1;
  }

  auto device = alcOpenDevice(nullptr);
  auto context = alcCreateContext(device, nullptr);

  alcMakeContextCurrent(context);

  //

  drwav wav;
  if (!drwav_init_file(&wav, "assets/MaenderAlkoor.wav", nullptr)) {
    fmt::print("failed to load wav");
    return 0;
  }

  ALuint buffer;
  alGenBuffers(1, &buffer);

  std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
  drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

  alBufferData(buffer,
               (wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
               samples.data(),
               samples.size() * sizeof(std::int16_t),
               wav.sampleRate);

  drwav_uninit(&wav);

  ALuint source;
  alGenSources(1, &source);

  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);

  std::getchar();

  //

  alDeleteBuffers(1, &buffer);

  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context);
  alcCloseDevice(device);
}