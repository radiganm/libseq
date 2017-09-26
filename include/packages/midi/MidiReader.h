/* MidiReader.h
 * Copyright 2017 Mac Radigan
 * All Rights Reserved
 */

#include <inttypes.h>
#include <string.h>
#include <mutex>
#include <deque>
#include <array>

#include "packages/midi/MidiEvent.h"

#ifndef midireader_h
#define midireader_h

  #define MIDI_BUFFER_SIZE (100 * 1024)

  class MidiReader
  {
    public:

      MidiReader();

      virtual ~MidiReader();

      ssize_t read(int fd, void *data, size_t nevents);

      size_t fread(void *data, size_t nevents, FILE *stream);

      bool parse(const void * const data, size_t size);

    protected:

    private:
      std::deque<MidiEvent> events_;
      std::array<uint8_t, MIDI_BUFFER_SIZE> buffer{};

  };

#endif
