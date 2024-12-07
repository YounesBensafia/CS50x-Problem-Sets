#include "helpers.h"
#include <math.h>
#define RED 0
#define GREEN 1
#define BLUE 2
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int clr = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = clr;
            image[i][j].rgbtGreen = clr;
            image[i][j].rgbtBlue = clr;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed < 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if (sepiaGreen < 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaBlue < 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int i = 0;
    int j;
    while (i < height)
    {
        j = 0;
        while (j < width / 2)
        {
            temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp;
            j++;
        }
        i++;
    }
    return;
}

int calculate_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int position)
{
    float count = 0;
    int sum = 0;
    for (int r = i - 1; r <= (i + 1); r++)
    {
        for (int c = j - 1; c <= (j + 1); c++)
        {
            if (r < 0 || r >= height || c < 0 || c >= width)
            {
                continue;
            }
            if (position == RED)
            {
                sum += image[r][c].rgbtRed;
            }
            else
            {
                if (position == GREEN)
                {
                    sum += image[r][c].rgbtGreen;
                }
                else
                {
                    sum += image[r][c].rgbtBlue;
                }
            }
            count++;
        }
    }
    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cp[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            cp[r][c] = image[r][c];
        }
    }
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c].rgbtRed = calculate_blur(r, c, height, width, cp, RED);
            image[r][c].rgbtGreen = calculate_blur(r, c, height, width, cp, GREEN);
            image[r][c].rgbtBlue = calculate_blur(r, c, height, width, cp, BLUE);
        }
    }
    return;
}
