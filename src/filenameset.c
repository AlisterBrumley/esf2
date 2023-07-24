#include <stdio.h>
#include <string.h>
#include "esf2.h"

// for printing into filenames
// accesible directly by number pulled from sample headers
// ie; midinotes[60] = middle C/C4
const char midinotes_arr[128][8] = {
    "C-1", "C#/Db-1", "D-1", "D#/Eb-1", "E-1", "F-1", "F#/Gb-1", "G-1", "G#/Ab-1", "A-1", "A#/Bb-1", "B-1",
    "C0", "C#/Db0", "D0", "D#/Eb0", "E0", "F0", "F#/Gb0", "G0", "G#/Ab0", "A0", "A#/Bb0", "B0",
    "C1", "C#/Db1", "D1", "D#/Eb1", "E1", "F1", "F#/Gb1", "G1", "G#/Ab1", "A1", "A#/Bb1", "B1",
    "C2", "C#/Db2", "D2", "D#/Eb2", "E2", "F2", "F#/Gb2", "G2", "G#/Ab2", "A2", "A#/Bb2", "B2",
    "C3", "C#/Db3", "D3", "D#/Eb3", "E3", "F3", "F#/Gb3", "G3", "G#/Ab3", "A3", "A#/Bb3", "B3",
    "C4", "C#/Db4", "D4", "D#/Eb4", "E4", "F4", "F#/Gb4", "G4", "G#/Ab4", "A4", "A#/Bb4", "B4",
    "C5", "C#/Db5", "D5", "D#/Eb5", "E5", "F5", "F#/Gb5", "G5", "G#/Ab5", "A5", "A#/Bb5", "B5",
    "C6", "C#/Db6", "D6", "D#/Eb6", "E6", "F6", "F#/Gb6", "G6", "G#/Ab6", "A6", "A#/Bb6", "B6",
    "C7", "C#/Db7", "D7", "D#/Eb7", "E7", "F7", "F#/Gb7", "G7", "G#/Ab7", "A7", "A#/Bb7", "B7",
    "C8", "C#/Db8", "D8", "D#/Eb8", "E8", "F8", "F#/Gb8", "G8", "G#/Ab8", "A8", "A#/Bb8", "B8",
    "C9", "C#/Db9", "D9", "D#/Eb9", "E9", "F9", "F#/Gb9", "G9"};

void fname_set(struct sfSample shdr, char *filename)
{
    char delim[2] = "_";
    char ext[5] = ".wav";
    char pitch[3];
    sprintf(pitch, "%i", shdr.pitchCor);
    strcpy(filename, shdr.smplName);
    strcat(filename, delim);
    strcat(filename, midinotes_arr[shdr.orgPitch]);
    strcat(filename, delim);
    strcat(filename, pitch);
    strcat(filename, ext);
}