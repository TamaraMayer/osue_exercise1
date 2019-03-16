/*
   Ryskim audio module.
   Microtrans Games Inc.

   Author: Cro Magnon, 2019
*/
#ifndef RYSKIM_AUDIO
#define RYSKIM_AUDIO

#include "raylib.h"
#include <vector>

namespace audio {
   const int MAX_SAMPLES            =  512;
   const int MAX_SAMPLES_PER_UPDATE = 4096;

   class Stream {
      AudioStream stream;
      short data [sizeof(short) * MAX_SAMPLES];
      short write_buf [sizeof(short) * MAX_SAMPLES_PER_UPDATE];
      int wavelength;
      int read_cursor = 0;
      bool playing = false;
    public:
      Stream();
      void update();
      void play_sine(float frequency);
      ~Stream();
   };

   void init();
   void shutdown();
} // namespace audio

#endif