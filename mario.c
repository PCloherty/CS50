#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    //n = user created number
    int height;
    //do- while loop, keep asking for the height while n is less an         0 or more than 23   
    do 
    {
        height = get_int("height?: ");
    }   
    while (height < 1 || height > 8);
    //incrementing integers v = verticle, height = horizontal
    int vertical;    
    // values for pasting the pyramid
    int space;
    int hash;

    for (vertical = 0 ; vertical < height; vertical++)
    {
        //left
        for (space = height - vertical ; space > 1; space--)
        {
            printf(" ");
        }
        for (hash = 0; hash < vertical + 1 ; hash++)
        {
            printf("#");
        }
        //middle space
        printf("  ");       
        //right
        for (hash = 0; hash < vertical + 1 ; hash++)
        {
            printf("#");
        }
            
        printf("\n");
    }
}
