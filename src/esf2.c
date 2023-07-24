#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
// #include <getopt.h> // TODO
#include "esf2.h"

int main(int argc, char *argv[])
{
    // check args kick out if no filename given
    if (argc != 2)
    {
        printf("invalid arguments!\nUSAGE: './esf2 [filename].sf2'\n");
        return 1;
    }

    // open filepointer for sample header
    FILE *shdr_fptr = fopen(argv[1], "r");
    if (shdr_fptr == NULL)
    {
        printf("file not found!\n");
        return 2;
    }

    // structs for file data chunks
    struct riffHeader rhdr;
    struct chunkHeader chdr;

    // passed to list_read to report failure
    int list_cnt = 1;
    // check if .sf2 file
    rhdr_read(&rhdr, shdr_fptr);
    list_read(&chdr, shdr_fptr, list_cnt); // 1st LIST
    seek_thru(chdr, shdr_fptr);
    list_read(&chdr, shdr_fptr, list_cnt); // 2nd LIST
    // storing file position for pcm data reading later
    int sdta_fseek_pos = ftell(shdr_fptr);
    seek_thru(chdr, shdr_fptr);
    list_read(&chdr, shdr_fptr, list_cnt); // 3rd/last LIST
    // iterate into 3rd list and checks is valid
    long_read(&chdr, shdr_fptr);

    // iterates through 3rd list chunk until finds sdta and shdr ID
    // reads header, if not what we need, uses chunksize to seek to next ID
    while (shdr_ver(chdr) != 1)
    {
        shdr_find(&chdr, shdr_fptr);
    }

    // chunk sizes here need to be a multiple of 46, if not the file is invalid (following spec)
    if (chdr.chunkSize % 46 != 0)
    {
        printf("sample header size mismatch - file likely corrupt\n");
        fclose(shdr_fptr);
        return 16; // make exit in above func
    }

    // remove 46 byte padding and get total amount of samples (based on sample headers)
    int total_samples = (chdr.chunkSize - 46) / 46;

    // filling shdr_array and closing ptr after done
    struct sfSample shdr_arr[total_samples];
    for (int i = 0; i < total_samples; i++)
    {
        shdr_arr[i] = shdr_fill(shdr_fptr);
    }
    fclose(shdr_fptr);

    // new filepointers for pcm ripping
    // if mono only using sf_dat_l
    // same file as prior so no need for input validation
    FILE *sf_pcm_l = fopen(argv[1], "r");
    FILE *sf_pcm_r = fopen(argv[1], "r");

    // seeking L pointer to start of PCM data, mirror position with the R pointer
    fseek(sf_pcm_l, sdta_fseek_pos, SEEK_SET);
    long_read(&chdr, sf_pcm_l);

    // setting to the start point of PCM data
    sdta_fseek_pos = ftell(sf_pcm_l);

    // filling wavhdr and then extracting
    // l to iterate as it will also mean 'left' in stereo
    for (int l = 0; l < total_samples; l++)
    {
        // (re)setting file pointers to PCM data start
        fseek(sf_pcm_l, sdta_fseek_pos, SEEK_SET);
        fseek(sf_pcm_r, sdta_fseek_pos, SEEK_SET);

        // total number of samples for each
        int num_samples = shdr_arr[l].smplEnd - shdr_arr[l].smplStart;

        // checking for stereo sample headers, skipping right sample headers
        if (shdr_arr[l].smplType == 2)
        {
            continue;
        }
        else if (shdr_arr[l].smplType == 4)
        {
            int r = shdr_arr[l].smplLink;
            fseek(sf_pcm_l, shdr_arr[l].smplStart * 2, SEEK_CUR);
            fseek(sf_pcm_r, shdr_arr[r].smplStart * 2, SEEK_CUR);
        }
        else
        {

            fseek(sf_pcm_l, shdr_arr[l].smplStart * 2, SEEK_CUR);
        }

        // creating wav header
        struct wavHeader wav_hdr = whdr_fill(shdr_arr[l], num_samples);

        // file name creation
        char wav_fn[37]; // max length is 36 based on other values, plus null term
        fname_set(shdr_arr[l], wav_fn);

        // creating wav file
        FILE *wav_file = fopen(wav_fn, "w");
        if (wav_file == NULL)
        {
            printf("file could not be created");
            return 22;
        }

        // writing header
        whdr_write(wav_hdr, wav_file);

        // writing sample data
        if (shdr_arr[l].smplType == 4)
        {
            // stereo extract
            stereo_pull(sf_pcm_l, sf_pcm_r, wav_file, num_samples);
        }
        else
        {
            // mono extract
            mono_pull(sf_pcm_l, wav_file, num_samples);
        }

        fclose(wav_file);
    }

    // END OF PCM RIP
    //      //      //      //      //      //      //      //      //

    fclose(sf_pcm_l);
    fclose(sf_pcm_r);
}
