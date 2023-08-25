#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w< width; w ++)
        {
            BYTE mean = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = mean;
            image[h][w].rgbtGreen = mean;
            image[h][w].rgbtRed = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    //sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    //sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    //sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            int sum1 = round(0.189*image[h][w].rgbtBlue + 0.769*image[h][w].rgbtGreen + 0.393*image[h][w].rgbtRed);
            image[h][w].rgbtRed = (BYTE)((sum1>255)?255:sum1);
            int sum2 = round(0.168*image[h][w].rgbtBlue + 0.686*image[h][w].rgbtGreen + 0.349*image[h][w].rgbtRed);
            image[h][w].rgbtGreen = (BYTE)((sum2>255)?255:sum2);
            int sum3 = round(0.131*image[h][w].rgbtBlue + 0.534*image[h][w].rgbtGreen + 0.272*image[h][w].rgbtRed);
            image[h][w].rgbtBlue = (BYTE)((sum3>255)?255:sum3);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int h = 0; h < height; h ++)
    {
        for (int i = 0; i < width / 2; i ++)
        {
            RGBTRIPLE tmp = image[h][i];
            image[h][i] = image[h][width-1-i];
            image[h][width-1-i] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            copy[h][w].rgbtRed = image[h][w].rgbtRed;
            copy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            copy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }
    for (int h = 0; h < height; h ++)
    {
        for (int w = 0; w < width; w ++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int ctr = 1;
            sumRed += copy[h][w].rgbtRed;
            sumGreen += copy[h][w].rgbtGreen;
            sumBlue += copy[h][w].rgbtBlue;
            if (w-1>=0) {sumRed += copy[h][w-1].rgbtRed;sumGreen += copy[h][w-1].rgbtGreen;sumBlue += copy[h][w-1].rgbtBlue;ctr ++;}
            if (h-1>=0) {sumRed += copy[h-1][w].rgbtRed;sumGreen += copy[h-1][w].rgbtGreen;sumBlue += copy[h-1][w].rgbtBlue;ctr ++;}
            if (w-1>=0 && h-1>=0) {sumRed += copy[h-1][w-1].rgbtRed;sumGreen += copy[h-1][w-1].rgbtGreen;sumBlue += copy[h-1][w-1].rgbtBlue;ctr ++;}
            if (w+1<=width-1) {sumRed += copy[h][w+1].rgbtRed;sumGreen += copy[h][w+1].rgbtGreen;sumBlue += copy[h][w+1].rgbtBlue;ctr ++;}
            if (w+1<=width-1 && h-1>=0) {sumRed += copy[h-1][w+1].rgbtRed;sumGreen += copy[h-1][w+1].rgbtGreen;sumBlue += copy[h-1][w+1].rgbtBlue;ctr ++;}
            if (w+1<=width-1 && h+1<=height-1) {sumRed += copy[h+1][w+1].rgbtRed;sumGreen += copy[h+1][w+1].rgbtGreen;sumBlue += copy[h+1][w+1].rgbtBlue;ctr ++;}
            if (h+1<=height-1) {sumRed += copy[h+1][w].rgbtRed;sumGreen += copy[h+1][w].rgbtGreen;sumBlue += copy[h+1][w].rgbtBlue;ctr ++;}
            if (w-1>=0 && h+1<=height-1) {sumRed += copy[h+1][w-1].rgbtRed;sumGreen += copy[h+1][w-1].rgbtGreen;sumBlue += copy[h+1][w-1].rgbtBlue;ctr ++;}
            image[h][w].rgbtRed = round(sumRed*1.0 / ctr*1.0);
            image[h][w].rgbtGreen = round(sumGreen*1.0 / ctr*1.0);
            image[h][w].rgbtBlue = round(sumBlue*1.0 / ctr*1.0);
        }
    }
    return;
}
