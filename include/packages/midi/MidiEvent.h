/* MidiEvent.h
 * Copyright 2017 Mac Radigan
 * All Rights Reserved
 */

#include <inttypes.h>

#pragma once

  #define MIDI__MTHD                          (0x4d546864)
  #define MIDI__MTRK                          (0x4d54726b)
  #define MIDI__MTHD_LENGTH                   (0x00000006)

  #define MIDI__EVENT_META                    (0xff)
  #define MIDI__EVENT_SYSEX                   (0xf0)
  #define MIDI__EVENT_SYSEX_ESCAPE            (0xf7)

  // Sequence Number:               FF 00 02
  #define MIDI__SEQUENCE_NUMBER               (0xff00)
  // Text Event:                    FF 01 len text
  #define MIDI__TEXT_EVENT                    (0xff01)
  // Copyright Notice:              FF 02 len text
  #define MIDI__COPYRIGHT_NOTICE              (0xff02)
  // Track Name:                    FF 03 len text
  #define MIDI__TRACK_NAME                    (0xff03)
  // Instrument Name:               FF 04 len text
  #define MIDI__INSTRUMENT_NAME               (0xff04)
  // Lyric:                         FF 05 len text
  #define MIDI__LYRIC                         (0xff05)
  // Marker:                        FF 06 len text
  #define MIDI__MARKER                        (0xff06)
  // Cue Point:                     FF 07 len text
  #define MIDI__CUE_POINT                     (0xff07)
  // MIDI Channel Prefix:           FF 20 01 cc
  #define MIDI__CHANNEL_PREFIX                (0x2001)
  // End Of Track:                  FF 2F 00
  #define MIDI__END_OF_TRACK                  (0x2f00)
  // Set Tempo:                     FF 51 03 tttttt
  #define MIDI__SET_TEMPO                     (0x5103)
  // SMPTE Offset:                  FF 54 05 hr mn se fr ff
  #define MIDI__SMPTE_OFFSET                  (0x5405)
  // Time Signature:                FF 58 04 nn dd cc bb
  #define MIDI__TIME_SIGNATURE                (0xff5804)
  // Key Signature:                 FF 59 02 sf mi
  //   sf = -7: 7 flats
  //   sf = -1: 1 flat 
  //   sf =  0: key of C
  //   sf =  1: 1 sharp
  //   sf =  7: 7 sharps
  //   mi =  0: major key
  //   mi =  1: minor key
  #define MIDI__KEY_SIGNATURE                 (0xff5902)
  // Sequencer Specific Meta-Event: FF 7F len data
  #define MIDI__SEQUENCER_SPECIFIC_META_EVENT (0xff7f)

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct __attribute__((packed)) midi_header_s
  {
    static const uint32_t magic = { MIDI__MTHD };
    // LENGTH: 32-bit representation of the number 6 (high byte first)
    static const uint32_t length = MIDI__MTHD_LENGTH;
    // FORMAT: 16-bit MSB first 
    //   0 - the file contains a single multi-channel track
    //   1 - the file contains one or more simultaneous tracks (or MIDI outputs of a sequence)
    //   2 - the file contains one or more sequentially independent track patterns
    uint16_t format;
    // NTRKS: 16-bit MSB first 
    //   1 - for a SMF format 0 file
    uint16_t ntracks;
    // DIVISION: 16-bit MSB first 
    //   metrical time:
    //     If bit 15 is zero, then bits 14-0 represent the number of 
    //       delta ticks which make up a quarter note.
    //   time-code-based time:
    //     If bit 15 is one, then bits 14-0 represent the number of 
    //       subdivisions of a second, in a way consitent with SMPTE and MIDI 
    //       Time Code.
    //       Bits 14-8 contain one of the four values -24, -25, -29, or -30, 
    //       correpsonding to the four standard SMPTE and MIDI Time Code 
    //       formats (-29 corresponds to 30 drop frome), and represents the 
    //       number of frames per seconds.  These negative numbers are stored 
    //       in two's compliment form.  The second byte (stored positive) is 
    //       the resolution within a frame:  typical values may be 4 (MIDI 
    //       Time Code resolution), 8, 10, 80 (bit resolution), or 100.
    //     
    uint16_t division;
  } midi_header_t;

  typedef struct __attribute__((packed)) midi_event_s
  {
    uint16_t  delta_time;
    uint16_t  event;
    uint8_t  *data;
  } midi_event_t;

  typedef struct __attribute__((packed)) midi_meta_s
  {
    static const uint8_t magic = { MIDI__EVENT_META };
    uint16_t  length;
    uint8_t  *data;
  } midi_meta_t;

  typedef struct __attribute__((packed)) midi_sysex_s
  {
    static const uint8_t magic = { MIDI__EVENT_SYSEX };
    uint16_t  length;
    uint8_t  *data;
  } midi_sysex_t;

  typedef struct __attribute__((packed)) midi_sysex_escape_s
  {
    static const uint8_t magic = { MIDI__EVENT_SYSEX_ESCAPE };
    uint16_t  length;
    uint8_t  *data;
  } midi_sysex_escape_t;

  typedef union midi_events_u
  {
    midi_event_t        event;
    midi_meta_t         meta;
    midi_sysex_t        sysex;
    midi_sysex_escape_t sysex_escape;
  } midi_events_t;

  typedef struct __attribute__((packed)) midi_track_s
  {
    static const uint32_t magic = { MIDI__MTRK };
    uint16_t       chunk_type;
    uint16_t       length;
    midi_events_t *events;
  } midi_track_t;

#ifdef __cplusplus
}
#endif

  class MidiEvent
  {
    public:

      MidiEvent();

      virtual ~MidiEvent();

    protected:

    private:

  };

// *EOF*
