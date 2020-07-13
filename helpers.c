#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {  
        for(int j = 0; j < width; j++)
        { 
             float mean = round(( image[i][j].rgbtRed +  image[i][j].rgbtGreen + image[i][j].rgbtBlue )/3.00); 
            image[i][j].rgbtRed= mean;
            image[i][j].rgbtBlue= mean;
            image[i][j].rgbtGreen= mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {  
        for(int j = 0; j < width; j++)
        { 
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
//i = down and j = across, 
//temp = array[i][j], array[i][j] = array[i][width.length-j], array[i][width.legnth-j] = temp
//^swapping the first and last pixel in an row

//using a temp variable swap with the width
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {  
        for(int j = 0; j < width / 2; j++)
        {   
          
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width-(j+1)];
                image[i][j/2] = image[i][j/2];
                image[i][width-(j+1)] = temp;
                
            
                
        }
    }    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
