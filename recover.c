//recover files in .raw memory card
#include<cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2 || argv[1] == NULL)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //name the card/image were reading as readfile
    char *readfile = argv[1];

    // open readfile
    FILE *readptr = fopen(readfile, "r");
    if (readptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", readfile);
        return 2;
    }

    //create readBuffer to read into
    unsigned char *readBuffer = malloc(512);

    if (readBuffer == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", readfile);
        return 3;
    }

    //create bool to check if we have found a jpg
    bool (jpgNew) = false;

    //create counter for the number of files found and a file pointer
    int filenumber = 0;
    FILE *new_jpg_ptr = NULL;
    char filename[8];


    // read through card file and continue loop until 'number' = 0
    while (fread(readBuffer, 1, 512, readptr) != 0x00)
    {
        //if we reach the header pattern of jpg
        if (readBuffer [0] == 0xff && readBuffer [1] == 0xd8 && readBuffer [2] == 0xff && (readBuffer [3] & 0xf0) == 0xe0)
        {

            //if there is not already a JPEG file found
            if (!jpgNew)
            {
                //open new file
                sprintf(filename, "%03i.jpg", filenumber);
                new_jpg_ptr = fopen(filename, "w");
                if (new_jpg_ptr == NULL)
                {
                    return 4;
                }

                //add to counter of files found
                filenumber++;

                //write files from readBuffer into new img file
                fwrite(readBuffer, 1, 512, new_jpg_ptr);

                //change the bool value
                (jpgNew) = true;
            }

            //if there is already a JPEG file found
            else
            {
                //close the previous file which would now be complete
                fclose(new_jpg_ptr);

                //open new file
                sprintf(filename, "%03i.jpg", filenumber);
                new_jpg_ptr = fopen(filename, "w");
                if (new_jpg_ptr == NULL)
                {
                    return 5;
                }

                //add to counter of files found
                filenumber++;

                //write files from readBuffer into new img file
                fwrite(readBuffer, 1, 512, new_jpg_ptr);
            }
        }

        // else if we do not see pattern of header bytes
        else
        {
            //if already found a jpg file which is open then write the bytes to that file
            if (jpgNew)
            {
                fwrite(readBuffer, 1, 512, new_jpg_ptr);
            }

            //if no file found yet, discard and move on
            if (!jpgNew)
            {
                continue;
            }
        }
    }

    //free memory
    free(readBuffer);

    //close pointers and end program successfully
    fclose(readptr);
    fclose(new_jpg_ptr);

    return 0;

}