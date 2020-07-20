#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //correct parameters
    if (argc != 2)
    {
        printf("correct format is ./recover image");
        return 1;
    }
    FILE *file=fopen(argv[1],"r");
    if(file==NULL)
    {
        printf("cant open");
        return 1;
    }

}
