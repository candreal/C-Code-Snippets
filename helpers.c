#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //set each of R, G, B to the average (R+G+B)/3
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (round)(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //set each of R, G, B to the corresponding sepia R, G, B
    int sRed = 0, sGreen = 0, sBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //compute the sepia R, G, B
            sRed = (round)((0.189 * (float)image[i][j].rgbtBlue) + (0.769 * (float)image[i][j].rgbtGreen) + (0.393 *
                           (float)image[i][j].rgbtRed));
            sGreen = (round)((0.168 * (float)image[i][j].rgbtBlue) + (0.686 * (float)image[i][j].rgbtGreen) + (0.349 *
                             (float)image[i][j].rgbtRed));
            sBlue = (round)((0.131 * (float)image[i][j].rgbtBlue) + (0.534 * (float)image[i][j].rgbtGreen) + (0.272 *
                            (float)image[i][j].rgbtRed));
            //check if the values are more than 255
            if (sRed > 255)
            {
                sRed = 255;
            }
            if (sGreen > 255)
            {
                sGreen = 255;
            }
            if (sBlue > 255)
            {
                sBlue = 255;
            }
            image[i][j].rgbtBlue = sBlue;
            image[i][j].rgbtGreen = sGreen;
            image[i][j].rgbtRed = sRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create buffer variables
    int bRed = 0, bGreen = 0, bBlue = 0;
    int end = 0;
    //iterate through image, setting the buffer variable to one value, then setting the other value to the first, and finally setting the other value to the buffer value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (float)(width / 2.0); j++)
        {
            end = width - 1 - j;
            //set buffer values to the values of image[i][j]
            bRed = image[i][j].rgbtRed;
            bGreen = image[i][j].rgbtGreen;
            bBlue = image[i][j].rgbtBlue;

            //set image[i][j] to the value of image[width-1-i][j]
            image[i][j].rgbtRed = image[i][end].rgbtRed;
            image[i][j].rgbtGreen = image[i][end].rgbtGreen;
            image[i][j].rgbtBlue = image[i][end].rgbtBlue;

            //set image[width-1-i][j] to value of buffers
            image[i][end].rgbtRed = bRed;
            image[i][end].rgbtGreen = bGreen;
            image[i][end].rgbtBlue = bBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a variable for calculating the average for a pixel, and a blurry image variable
    RGBTRIPLE blurry[height][width];
    int sum = 0, num = 0, avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top row first
            if (i == 0)
            {
                if (j == 0)
                {
                    //top left corner, only averaging 4 pixels
                    num = 4;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else if (j == width - 1)
                {
                    //top right corner, only averaging 4 pixels
                    num = 4;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else
                {
                    //top row in between two corners, averaging 6 pixels
                    num = 6;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j -
                            1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j -
                            1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j -
                            1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
            }
            //top row done, now do bottom row
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    //bottom left corner, only averaging 4 pixels
                    num = 4;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else if (j == width - 1)
                {
                    //bottom right corner, only averaging 4 pixels
                    num = 4;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else
                {
                    //bottom row in between two corners, averaging 6 pixels
                    num = 6;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j -
                            1].rgbtRed + image[i - 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j -
                            1].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j -
                            1].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
            }
            //now what is left is 0 < i < height - 1
            else
            {
                //left column, j = 0
                if (j == 0)
                {
                    //averaging 6 pixels
                    num = 6;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j +
                            1].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j +
                            1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j +
                            1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else if (j == width - 1)
                {
                    //averaging 6 pixels
                    num = 6;
                    //calculate red first
                    sum = image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j -
                            1].rgbtRed + image[i + 1][j - 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j -
                            1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j -
                            1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
                else
                {
                    //the border pixels have been calculated, now the inside averaging 9 pixels
                    num = 9;
                    //calculate red first
                    sum = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                          image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtRed = avg;
                    //calculate green
                    sum = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                          image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j +
                                  1].rgbtGreen;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtGreen = avg;
                    //calculate blue
                    sum = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                          image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j +
                                  1].rgbtBlue;
                    avg = (round)((float)sum / (float)num);
                    blurry[i][j].rgbtBlue = avg;
                }
            }
        }
    }
    //now copy blurry[i][j] into image[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurry[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurry[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurry[i][j].rgbtBlue;
        }
    }
    return;
}
