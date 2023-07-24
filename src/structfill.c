#include <stdio.h>
#include <string.h>
#include "esf2.h"

// fill sf2 sample header struct
struct sfSample shdr_fill(FILE *fptr)
{
    struct sfSample tempStr;

    fgets(tempStr.smplName, 21, fptr);
    fread(&tempStr.smplStart, sizeof(DWORD), 1, fptr);
    fread(&tempStr.smplEnd, sizeof(DWORD), 1, fptr);
    fread(&tempStr.lpStart, sizeof(DWORD), 1, fptr);
    fread(&tempStr.lpEnd, sizeof(DWORD), 1, fptr);
    fread(&tempStr.smplRate, sizeof(DWORD), 1, fptr);
    fread(&tempStr.orgPitch, sizeof(BYTE), 1, fptr);
    fread(&tempStr.pitchCor, sizeof(CHAR), 1, fptr);
    fread(&tempStr.smplLink, sizeof(WORD), 1, fptr);
    fread(&tempStr.smplType, sizeof(WORD), 1, fptr);

    return tempStr;
}

// fill wave headers
struct wavHeader whdr_fill(struct sfSample shdr, int num_samples)
{
    struct wavHeader tmpWavStr;
    // checks for stero
    if (shdr.smplType != 1)
    {
        printf("%i sampletype\n", shdr.smplType);
        tmpWavStr.chunkSize = 36 + (num_samples * 2) * 2;
        tmpWavStr.numChannels = 2;
    }
    else
    {
        tmpWavStr.chunkSize = 36 + (num_samples * 2);
        tmpWavStr.numChannels = 1;
    }

    // RIFF CHUNK
    strcpy(tmpWavStr.chunkID, "RIFF");
    strcpy(tmpWavStr.format, "WAVE");

    // fmt CHUNK
    strcpy(tmpWavStr.subChunk1ID, "fmt ");
    tmpWavStr.subChunk1Size = 16; // 16 is the byte size of the rest of this chunk
    tmpWavStr.audioFormat = 1;
    tmpWavStr.sampleRate = shdr.smplRate;
    tmpWavStr.bitsPerSample = 16;
    tmpWavStr.byteRate = tmpWavStr.sampleRate * tmpWavStr.numChannels * tmpWavStr.bitsPerSample / 8;
    tmpWavStr.blockAlign = tmpWavStr.numChannels * tmpWavStr.bitsPerSample / 8;

    // data CHUNK
    strcpy(tmpWavStr.subChunk2ID, "data");
    tmpWavStr.subChunk2Size = num_samples * tmpWavStr.numChannels * tmpWavStr.bitsPerSample / 8;

    return tmpWavStr;
}