
#ifndef _ESF2_H_
#define _ESF2_H_

#include <stdio.h>
#include <stdint.h>

// TYPEDEFS
// types to mirror sf2 spec
// this is based on 90's documentation, so names kinda wrong
typedef uint8_t BYTE;   // unsigned byte
typedef int8_t CHAR;    // signed byte, not actually a char
typedef uint16_t WORD;  // unsigned 2 bytes
typedef uint32_t DWORD; // unsigned 4 bytes
typedef char FOURCC[5]; // always to be interpreted as letters, includes space for null terminator
// others
typedef char FOURCC_ACT[4]; // same as FOURCC but without space for null term

// VARIABLE DEC
struct sfSample;   // sf2 sample headers
struct wavHeader;  // wav file header
struct riffHeader; // for sf2 file reading
struct chunkHeader;

// FUNCTION DECS
// live in iterators.c
void rhdr_read(struct riffHeader *rhdr, FILE *sh_fptr);
void list_read(struct chunkHeader *chdr, FILE *sh_fptr, int list_count);
void long_read(struct chunkHeader *chdr, FILE *sh_fptr);
void seek_thru(struct chunkHeader chdr, FILE *sh_fptr);
void shdr_find(struct chunkHeader *chdr, FILE *fptr);
// live in structfill.c
struct sfSample shdr_fill(FILE *sf_fptr);
struct wavHeader whdr_fill(struct sfSample, int num_samples);
// live in verify.c
void rhdr_ver(struct riffHeader);
void list_ver(struct chunkHeader, int list_count);
void lr_ver(struct chunkHeader);
int shdr_ver(struct chunkHeader);
// live in filenameset.c
void fname_set(struct sfSample shdr, char *filename);
// live in filewrite.c
void whdr_write(struct wavHeader whdr, FILE *w_fptr);
void mono_pull(FILE *sf_fptr, FILE *w_fptr, int t_samples);
void stereo_pull(FILE *sf_l_fptr, FILE *sf_r_fptr, FILE *w_fptr, int t_samples);

// STRUCTURES
// taken from soundfont spec v2.01 - sample header, data types match spec
struct sfSample
{
    char smplName[21];
    DWORD smplStart;
    DWORD smplEnd;
    DWORD lpStart;
    DWORD lpEnd;
    DWORD smplRate;
    BYTE orgPitch;
    CHAR pitchCor;
    WORD smplLink;
    WORD smplType;
};

// taken from sapp.org wave format page
struct wavHeader
{
    // RIFF CHUNK
    FOURCC chunkID;  // always 'RIFF'
    DWORD chunkSize; // filesize following this and prior
    FOURCC format;   // always 'WAVE'
    // fmt CHUNK
    FOURCC subChunk1ID;  // always 'fmt '
    DWORD subChunk1Size; // always 16
    WORD audioFormat;    // always 1
    WORD numChannels;    // 1 for mono, 2 for stereo
    DWORD sampleRate;
    DWORD byteRate;     // == SampleRate * NumChannels * BitsPerSample/8
    WORD blockAlign;    // == NumChannels * BitsPerSample/8 // The number of bytes for one sample including all channels
    WORD bitsPerSample; // always 16
    // data CHUNK
    FOURCC subChunk2ID;  // always 'data'
    DWORD subChunk2Size; // i think(shdr.smplEnd-shdr.smplStart);
};

// used to pull the riff file main header
struct riffHeader
{
    FOURCC chunkID; // should always be RIFF
    DWORD chunkSize;
    FOURCC chunkID2; // should always be sfbk at offset 8-11
};

// as above but for subchunks
struct chunkHeader
{
    FOURCC chunkID;
    FOURCC chunkLong; // only used for certain situatons where the fourcc is followed directly by another
    DWORD chunkSize;
};

#endif /*_ESF2_H_*/