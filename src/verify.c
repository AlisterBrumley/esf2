#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esf2.h"

// function to verify file as RIFF/SF2
void rhdr_ver(struct riffHeader rhdr)
{
    if (strcmp(rhdr.chunkID, "RIFF") != 0 && strcmp(rhdr.chunkID2, "sfbk") != 0)
    {
        printf("RIFF header not found - file be corrupt or not .sf2\n");
        exit(11);
    }
}

// compares chunkid strings to correct FOURCC to make sure it's a LIST sub-chunk
void list_ver(struct chunkHeader lhdr, int list_cnt)
{
    if (strcmp(lhdr.chunkID, "LIST") != 0)
    {
        printf("LIST header %i not found - file might be corrupt\n", list_cnt);
        exit(12);
    }
}

// compares chunkid strings to 2xFOURCC to check which subchunk
void lr_ver(struct chunkHeader chdr)
{
    // if not pdta or not phdr and not sdta or not smpl exit
    // basically if its not one of the two things we want, it quits
    if ((strcmp(chdr.chunkID, "pdta") != 0 || strcmp(chdr.chunkLong, "phdr") != 0) &&
        (strcmp(chdr.chunkID, "sdta") != 0 || strcmp(chdr.chunkLong, "smpl") != 0))
    {
        printf("correct strings not found - file might be corrupt\n");
        exit(13);
    }
}

// compares chunkid strings to correct FOURCC to make sure it's a sample header sub-chunk
// runs in a while loop
int shdr_ver(struct chunkHeader chdr)
{
    if (strcmp(chdr.chunkID, "shdr") != 0)
    {
        return 0;
    }
    return 1;
}
