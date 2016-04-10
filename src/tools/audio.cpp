#include "common_structs.hpp"
#include <iostream>

void	playSound(t_sound *sound)
{
  audioPos = sound->buffer;
  audioLen = sound->lenght;
  if (SDL_OpenAudio(&sound->spec, NULL) < 0)
    {
      std::cerr << "Couldn't open audio (" << SDL_GetError() << ")\n";
      exit(1);
    }
  SDL_PauseAudio(0);
  while (audioLen > 0)
    SDL_Delay(100);
  SDL_CloseAudio();
}

void	myAudioCallback(void *data, Uint8 *stream, int len)
{
  (void)data;
  if (!(audioLen))
    return ;
  len = (len > (int)audioLen) ? audioLen : len;
  SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);
  *audioPos += len;
  audioLen -= len;
}
