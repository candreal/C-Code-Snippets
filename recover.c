#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //check that there is exactly 1 command line argument. if not, remind the user of correct usage, and return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    //open mem card file. File *f = fopen(argv[1], "r");
    char *name = argv[1];

    FILE *f = fopen(name, "r");

    //check that the file can be opened. if not, inform the user and return 1.
    if (f == NULL)
    {
        printf("Error: file cannot be opened. Please try again\n");
        return 1;
    }
    else
    {
        printf("file opened successfully.\n");
    }

    //look through file for beginning of a JPEG
    //create a buffer to store each block, and an integer to count how many jpegs have been found, and a string filename
    unsigned char buffer[512];
    int numPics = 0;
    int dataWritten = 512;
    char *jpgfilename = malloc(8);
    FILE *img = fopen(jpgfilename, "w");

    //parse through file, finding 50 jpegs
    do
    {
        //write 512 bytes, or 1 block, into a buffer
        dataWritten = fread(buffer, 1, 512, f);

        //when a JPEG is found, open a new JPEG and write 512 bytes of data at a time until a new JPEG is found
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] & 0xf0) == 0xe0)
        {
            //found a jpeg, woo!    printf("#%i jpeg found!\n", numPics);

            //if I have a previous file open, close that one
            if (numPics != 0)
            {
                //printf("Yo gotta close the last jpeg dawg!\n");
                fclose(img);
            }

            //open a new file with the name # + numPics + .jpg, and write the current block from the buffer into the image file
            sprintf(jpgfilename, "%03i.jpg", numPics);
            img = fopen(jpgfilename, "w");
            fwrite(buffer, 1, 512, img);

            //increment numPics
            numPics++;
        }
        else
        {
            //this is not a jpeg file, so if I have a file open, continue to read this block into that open file.
            if (numPics != 0)
            {
                //printf("continuing on this %i jpeg journey\n", numPics);
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                //printf("no jpeg yet!\n");
            }
        }

    }
    while (dataWritten == 512);

    fclose(img);
    fclose(f);
    free(jpgfilename);

}
