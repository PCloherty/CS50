#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    //parameters not met
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //
    if (fopen(argv[1], "r") == NULL)
    {
        printf("File failed to open.");
        return 1;
    }
    //open memory card
    FILE *image = fopen(argv[1], "r");
    FILE *recovered = NULL;
    BYTE buffer [512];
    int imgNum = 0;
    char fileName [12];
    //fread(data(size of indevidual bytes, number of bytes,file to read from))
    while (fread(buffer,1,512,image))
    {
        //bitwise &
        if (buffer[0]==0xff && buffer[1]== 0xd8 && buffer[2]== 0xff && (buffer[3] & 0xf0)==0xe0)
        {
            if (imgNum == 0)
            {
                sprintf(fileName, "%03i.jpg", imgNum);
                recovered = fopen(fileName, "w");
                fwrite(buffer,1,512, recovered);
                imgNum++;
            } else {
                fclose(image);
                sprintf(fileName, "%03i.jpg", imgNum);
                recovered = fopen(fileName, "w");
                 fwrite(buffer,1,512, recovered);
                imgNum++;
            }
        } else if(imgNum>0)
        {
            fwrite(buffer,1,512,recovered);
        }
    }
    fclose(recovered);
    return 0;
}
