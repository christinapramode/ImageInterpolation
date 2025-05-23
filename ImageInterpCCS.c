 /*
  * Image Interpolation in C, Code to run in CCS with profiling added
  * By Christina Ann Pramode 
  */

#include <stdio.h>
#include <stdlib.h>
#include <c6x.h>

void interpImg(unsigned char* input, int width, int height, unsigned char* interpOut);

int main()
{
    FILE* fin, * fout;
    unsigned char* rev, * revout, px;
    int height, width, iread, row, i;
    volatile unsigned long long start, end, cycles_example, xcycles, sumcycles = 0;

    width = 256, height = 256;

    // Opening the input and output files
    fin = fopen("Image1_256x256.raw", "rb");
    if (fin == NULL) {
        perror("Failed: ");
        return 1;
    }
    fout = fopen("Image1_512x256.raw", "wb");

    // Memory Allocation for input & output image arrays
    rev = malloc(width * sizeof(unsigned char));
    revout = malloc(2 * width * sizeof(unsigned char));

    for (row = 0; row < height; row++)
    {
        // Reading from the input image 256x256
        for (i = 0; i < width; i++)
        {
            iread = fread(&px, sizeof(unsigned char), 1, fin);
            rev[i] = px;
        }

        // Setting timer and calling the function interpImg

        TSCL = 0;   /*Enable timer by writing any value on the TSC register*/
        start = _itoll(TSCH, TSCL);   /*read 64-bit TSC register with Upper & lower words*/

        interpImg(rev, width, height, revout);

        end = _itoll(TSCH, TSCL);    /*read 64-bit TSC register with Upper & lower words*/
        cycles_example = end - start;
        sumcycles += cycles_example; // Take sum of cycles of each row


        // Writing to the output image 512x256
        for (i = 0; i < 2 * width; i++)
            if (i < 2 * width && row < height)
                fwrite(&revout[i], sizeof(unsigned char), 1, fout);

    }

    printf("Value is %d \n", sumcycles);

    fclose(fout);
    fclose(fin);

    return 0;
}

void interpImg(unsigned char* input, int width, int height, unsigned char* interpOut)
{
    int i, j, x;
    j = 0;
    while (j < width) {
        for (i = 0; i < 2 * width; i++) {
            if (i % 2 == 0) {
                interpOut[i] = input[j];
                j++;
            }
            if (i % 2 != 0) {
                x = (input[j] + input[j - 1] + 1) / 2;
                interpOut[i] = x;  
            }
        }
    }
}
