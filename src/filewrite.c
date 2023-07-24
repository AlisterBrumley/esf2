#include <stdio.h>
#include "esf2.h"

// write out
void whdr_write(struct wavHeader whdr, FILE *w_fptr)
{
    // RIFF CHUNK
    fwrite(whdr.chunkID, sizeof(FOURCC_ACT), 1, w_fptr);
    fwrite(&whdr.chunkSize, sizeof(DWORD), 1, w_fptr);
    fwrite(whdr.format, sizeof(FOURCC_ACT), 1, w_fptr);
    // fmt CHUNK
    fwrite(whdr.subChunk1ID, sizeof(FOURCC_ACT), 1, w_fptr);
    fwrite(&whdr.subChunk1Size, sizeof(DWORD), 1, w_fptr);
    fwrite(&whdr.audioFormat, sizeof(WORD), 1, w_fptr);
    fwrite(&whdr.numChannels, sizeof(WORD), 1, w_fptr);
    fwrite(&whdr.sampleRate, sizeof(DWORD), 1, w_fptr);
    fwrite(&whdr.byteRate, sizeof(DWORD), 1, w_fptr);
    fwrite(&whdr.blockAlign, sizeof(WORD), 1, w_fptr);
    fwrite(&whdr.bitsPerSample, sizeof(WORD), 1, w_fptr);
    // data CHUNK
    fwrite(whdr.subChunk2ID, sizeof(FOURCC_ACT), 1, w_fptr);
    fwrite(&whdr.subChunk2Size, sizeof(DWORD), 1, w_fptr);
}

// mono extract
void mono_pull(FILE *sf_fptr, FILE *w_fptr, int t_samples)
{
    // m for mono
    int16_t m_smpl_buffer;
    // loop through all samples in SF2 and write to new file
    for (int i = 0; i < t_samples; i++)
    {
        fread(&m_smpl_buffer, sizeof(int16_t), 1, sf_fptr);
        fwrite(&m_smpl_buffer, sizeof(int16_t), 1, w_fptr);
    }
}

// stereo extract
void stereo_pull(FILE *sf_l_fptr, FILE *sf_r_fptr, FILE *w_fptr, int t_samples)
{
    // l for left, r for right
    int16_t l_smpl_buffer;
    int16_t r_smpl_buffer;
    // loop through all samples in SF2 and write to new file
    for (int i = 0; i < t_samples; i++)
    {
        // right then left as wav spec does
        fread(&l_smpl_buffer, sizeof(int16_t), 1, sf_l_fptr);
        fwrite(&l_smpl_buffer, sizeof(int16_t), 1, w_fptr);
        fread(&r_smpl_buffer, sizeof(int16_t), 1, sf_r_fptr);
        fwrite(&r_smpl_buffer, sizeof(int16_t), 1, w_fptr);
    }
}