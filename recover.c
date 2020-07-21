#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    if (fopen(argv[1], "r") == NULL)
    {
        printf("File failed to open.");
        return 1;
    }
    FILE *image = fopen(argv[1], "r");
    char ch;
    while ( (ch = fgetc(image)) != EOF)
    {
        printf("%c",ch);
    }
}
