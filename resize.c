//copies and enlarges bitmap image by number given at runtime
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 || argv[1] == NULL)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *number = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    int n = atoi(number);
    if (n <= 0)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    BITMAPFILEHEADER newbf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    newbf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    BITMAPINFOHEADER newbi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    newbi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //update new file's width and height
    newbi.biWidth = bi.biWidth * n;
    newbi.biHeight = bi.biHeight * n;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    newbf.bfSize = 54 + (newbi.biWidth * (sizeof(RGBTRIPLE)) + newPadding) * abs(newbi.biHeight);
    newbi.biSizeImage = newbf.bfSize - 54;

    // write outfile's BITMAPFILEHEADER
    //fread(pointer to a struct that you're reading from, size of each element to write, number of elements to write, file to write to)
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //repeat rows n times in new file
        int row = 0;
        while (row < n)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // for each pixel in the row write pixel n times
                for (int p = 0; p < n; p++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }

            // if row < n - 1; repeat read and write
            if (row < (n - 1))
            {
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }

            row++;
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
