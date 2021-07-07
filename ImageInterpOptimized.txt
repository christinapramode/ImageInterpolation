 /*
  * Image Interpolation in C
  * using Intrinsics functions
  * By Christina Ann Pramode
  */

#include <stdio.h>
#include <stdlib.h>
#include <c6x.h>

void interpImg(unsigned char* restrict input, const int width, unsigned char* restrict interpOut);

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

    #pragma MUST_ITERATE(256);
    for (row = 0; row < height; row++)
    {
        
// Reading from the input image 256x256
	#pragma MUST_ITERATE(256);
    	for (i = 0; i < width; i++)
        {
            iread = fread(&px, sizeof(unsigned char), 1, fin);
            rev[i] = px;
        }


        // Setting timer and calling the function interpImg

        TSCL = 0;   /*Enable timer by writing any value on the TSC register*/
        start = _itoll(TSCH, TSCL);   /*read 64-bit TSC register with Upper & lower words*/

        interpImg(rev, width, revout);

        end = _itoll(TSCH, TSCL);    /*read 64-bit TSC register with Upper & lower words*/
        cycles_example = end - start;
        sumcycles += cycles_example; // Take sum of cycles of each row


        // Writing to the output image 512x256
	 #pragma MUST_ITERATE(512);
        for (i = 0; i < 2 * width; i++)
            if (i < 2 * width && row < height)
                fwrite(&revout[i], sizeof(unsigned char), 1, fout);

    }

    printf("Value is %d \n", sumcycles);

    fclose(fout);
    fclose(fin);

    return 0;
}


// FUNCTION USING INTRINSICS
void interpImg(unsigned char* restrict input, const int width, unsigned char* restrict interpOut)
{
	int i, o=0;
	unsigned a0_a3, al, ah, x, y, z, avg;

	#pragma MUST_ITERATE(256);
	for (i = 0; i < width; i += 2)
	{
		a0_a3 = _mem4(&input[i]);

		al = _unpklu4(a0_a3);
		ah = _unpkhu4(a0_a3);

		x = _swap4(al);
		y = _shrmb(ah,al);
		z = _avgu4(x, y);

		avg = _add4(al, z);

		_amem4(&interpOut[i+o]) = avg;
		o+=2;
	}
}
