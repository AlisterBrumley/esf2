// functions to iterate through the SF2 file
#include <stdio.h>
#include <string.h>
#include "esf2.h"

// reads the first 12 bytes into the riffheader struct and verifies its a valid RIFF and SF2 file
void rhdr_read(struct riffHeader *rhdr, FILE *fptr)
{
    fgets(rhdr->chunkID, sizeof(FOURCC), fptr);
    fread(&rhdr->chunkSize, sizeof(DWORD), 1, fptr);
    fgets(rhdr->chunkID2, sizeof(FOURCC), fptr);
    rhdr_ver(*rhdr);
}

// reads chunk data and and verifies
void list_read(struct chunkHeader *chdr, FILE *fptr, int list_cnt)
{
    fgets(chdr->chunkID, sizeof(FOURCC), fptr);
    fread(&chdr->chunkSize, sizeof(DWORD), 1, fptr);
    list_ver(*chdr, list_cnt);
    list_cnt++;
}

// reads chunk data with 2xFOURCC ID's and verifies
void long_read(struct chunkHeader *chdr, FILE *fptr)
{
    fgets(chdr->chunkID, sizeof(FOURCC), fptr);
    fgets(chdr->chunkLong, sizeof(FOURCC), fptr);
    fread(&chdr->chunkSize, sizeof(DWORD), 1, fptr);
    lr_ver(*chdr); // returns boolean
}

// seeks from data in chdr to next list
void seek_thru(struct chunkHeader chdr, FILE *fptr)
{
    fseek(fptr, chdr.chunkSize, SEEK_CUR);
}

// seeks to next and reads into chdr buffer
void shdr_find(struct chunkHeader *chdr, FILE *fptr)
{
    seek_thru(*chdr, fptr);
    fgets(chdr->chunkID, sizeof(FOURCC), fptr);
    fread(&chdr->chunkSize, sizeof(DWORD), 1, fptr);
}

