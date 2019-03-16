/*
   Ryskim audio module.
   Microtrans Games Inc.

   Author: Cro Magnon, 2019
*/

#include <cmath>

#include "audio.h"
#include "util.h"


namespace audio {

   Stream::Stream() {
      stream = InitAudioStream(22050, 16, 1);
   }

   void Stream::play_sine(float frequency) {
      int old_wavelength = wavelength;
      wavelength = (int)(22050/frequency);
      if (wavelength > MAX_SAMPLES/2) wavelength = MAX_SAMPLES/2;
      if (wavelength < 1) wavelength = 1;
            
      for (int i = 0; i < wavelength*2; i++) {
         data[i] = (short)(std::sinf(((2*PI*(float)i/wavelength)))*32000);
      }

      // Scale read cursor's position to minimize transition artifacts
      read_cursor = (int)(read_cursor * ((float)wavelength / (float)old_wavelength));

      if (!playing) {
         PlayAudioStream(stream);
         playing = true;
      }
   }

   void Stream::update() {
        // Refill audio stream if required
        if (playing && IsAudioBufferProcessed(stream)) 
        {
            // Synthesize a buffer that is exactly the requested size
            int writeCursor = 0;
            
            while (writeCursor < MAX_SAMPLES_PER_UPDATE) 
            {
                // Start by trying to write the whole chunk at once
                int writeLength = MAX_SAMPLES_PER_UPDATE-writeCursor;
                
                // Limit to the maximum readable size
                int readLength = wavelength - read_cursor;
                
                if (writeLength > readLength) writeLength = readLength;

                // Write the slice
                memcpy(write_buf + writeCursor, data + read_cursor, writeLength*sizeof(short));
                
                // Update cursors and loop audio
                read_cursor = (read_cursor + writeLength) % wavelength;
                
                writeCursor += writeLength;
            }
            
            // Copy finished frame to audio stream
            UpdateAudioStream(stream, write_buf, MAX_SAMPLES_PER_UPDATE);
        }
   }

   Stream::~Stream() {
      CloseAudioStream(stream);
   }

   void init() {
      InitAudioDevice();
   }

   void shutdown() {
      CloseAudioDevice();
   }
}