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
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
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
    //create avariable the same height and width for blurred output while keeping original values intact
        //2d array and copy the values into the new RGBTRIPLE
    
    //create copy to ref
    RGBTRIPLE refImg[height][width];
   
    
    for ( int i = 0; i < height; i++)
    {
        for ( int j = 0; j < width; j++)
        {
        
            refImg[i][j] = image[i][j];
            
            float refR=0.0 , refG=0.0, refB=0.0; 
            int cells =0;
            for (int k = -1; k<=1;k++)
            {
                for (int l =-1; l<=1; l++)
                {
                    if(i >=0  && i < height &&j >=0 && j <width)
                    {
                        refR += image[i+k][j+l].rgbtRed;
                        refB += image[i+k][j+l].rgbtBlue;
                        refG += image[i+k][j+l].rgbtGreen;
                        cells++;
                    }
                }
            }
          

            refImg[i][j].rgbtRed = round(refR /  cells);
            refImg[i][j].rgbtBlue = round(refB /  cells);
            refImg[i][j].rgbtGreen = round(refG /  cells);
            
              
          }
    }
    for ( int i = 0; i < height; i++)
    {
        for ( int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = refImg[i][j].rgbtRed;
            image[i][j].rgbtBlue = refImg[i][j].rgbtBlue;
            image[i][j].rgbtGreen = refImg[i][j].rgbtGreen;
        }
    }
    return;
    
}
