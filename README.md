# ESF2
## soundfont (.sf2) wave extractor

A simple CLI program to extract audio from .sf2 files. Navigate to the folder you want the extracted files to be in, place the executable in the folder, and run the command `./esf2 [YOUR_SOUNDFONT_HERE].sf2` and let it rip. 

Filenames incidate original pitch and pitch correction applied on SF2 playback (in cents) ie. `"snare_D#/Eb3_-5.wav"` or `"ARR1_C4_0.wav"`.

Works for both mono and stereo samples, but untested on ROM samples. Confirmed to work on MacOS, testing on other OS's soon.

Makefile coming soon! But for now, building can be done by navigating into the /src directory and running:

`clang -o esf2 esf2.c iterators.c structfill.c verify.c filenameset.c filewrite.c`
