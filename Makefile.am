## makefile.am
## Copyright 2017 Mac Radigan
## All Rights Reserved

AM_LDFLAGS  = -pthread                                                        

AM_CPPFLAGS = -I$(top_srcdir)/include                                        \
              -std=c++11
AM_FCFLAGS  = -Jmod

seq_ldadd                 = libseq.la                                         

bin_PROGRAMS              = test_seq                                          

test_seq_SOURCES          = src/tests/test_seq.cc
test_seq_LDADD            = $(seq_ldadd)

lib_LTLIBRARIES          = libseq.la
libseq_la_SOURCES        = src/packages/midi/MidiEvent.cc                    \
                           src/packages/midi/MidiReader.cc                    

libseq_la_LIBADD         =                                                    

libseq_la_LDFLAGS        = -export-symbols-regex '^seq_[^_]' -fPIC           \
                           -shared -pthread                                   

pkginclude_HEADERS       = include/packages/midi/MidiEvent.h                 \
                           include/packages/midi/MidiReader.h                 
## *EOF*
