# ESF2
## soundfont (.sf2) wave extractor

A simple CLI program to extract audio from .sf2 files. Navigate to the folder you want the extracted files to be in, place the executable in the folder, and run the command `./esf2 [YOUR_SOUNDFONT_HERE].sf2` and let it rip.

Filenames incidate original pitch and pitch correction applied on SF2 playback (in cents) ie. `"snare_D#/Eb3_-5.wav"` or `"ARR1_C4_0.wav"`.

Works for both mono and stereo samples, but untested on ROM samples. Confirmed to work on MacOS (intel x86_64, g4 ppc), and Fedora Linux(x86_64), binary executables are in relevant folders.

If you want to build your own, simply run `make`! (current makefile is clang only)
