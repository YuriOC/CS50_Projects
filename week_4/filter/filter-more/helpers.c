#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {

            int result =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) * 10 / 3;
            if (result % 10 == 0)
            {
                image[i][j].rgbtRed = result / 10;
                image[i][j].rgbtBlue = result / 10;
                image[i][j].rgbtGreen = result / 10;
            }
            else if (result % 10 != 0 && result % 10 < 5)
            {
                image[i][j].rgbtRed = result / 10;
                image[i][j].rgbtBlue = result / 10;
                image[i][j].rgbtGreen = result / 10;
            }
            else if (result % 10 != 0 && result % 10 >= 5)
            {
                image[i][j].rgbtRed = (result / 10) + 1;
                image[i][j].rgbtBlue = (result / 10) + 1;
                image[i][j].rgbtGreen = (result / 10) + 1;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            image[i][j] = copy[i][(width - 1) - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
            int somaRed = 0;
            int somaGreen = 0;
            int somaBlue = 0;
            int count = 0;
            int result = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + l >= 0 && j + l <= width - 1))
                    {
                        somaRed += copy[i + k][j + l].rgbtRed;
                        somaGreen += copy[i + k][j + l].rgbtGreen;
                        somaBlue += copy[i + k][j + l].rgbtBlue;
                        count++;
                    }
                }
            }

            somaRed = somaRed * 10 / count;
            if (somaRed % 10 >= 5)
            {
                image[i][j].rgbtRed = (somaRed / 10) + 1;
            }
            else
            {
                image[i][j].rgbtRed = somaRed / 10;
            }

            somaGreen = somaGreen * 10 / count;
            if (somaGreen % 10 >= 5)
            {
                image[i][j].rgbtGreen = (somaGreen / 10) + 1;
            }
            else
            {
                image[i][j].rgbtGreen = somaGreen / 10;
            }

            somaBlue = somaBlue * 10 / count;
            if (somaBlue % 10 >= 5)
            {
                image[i][j].rgbtBlue = (somaBlue / 10) + 1;
            }
            else
            {
                image[i][j].rgbtBlue = somaBlue / 10;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];

    for(int i = 0; i <= height - 1; i++)
    {
        for(int j = 0; j <= width - 1; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i <= height - 1; i++)
    {
        for(int j = 0; j <= width - 1; j++)
        {
            int somaredGX = 0;
            int somagreenGX = 0;
            int somablueGX = 0;

            int somaredGY = 0;
            int somagreenGY = 0;
            int somablueGY = 0;

            int resultRed = 0;
            int resultGreen = 0;
            int resultBlue = 0;

            for(int k = -1; k <= 1; k++)
            {
                for(int l = -1; l <= 1; l++)
                {
                    if((i + k >= 0 && i + k <= height - 1) && (j + l >= 0 && j + l <= width - 1))
                    {
                        somaredGX += (copy[i + k][j + l].rgbtRed * gx[k + 1][l + 1]);
                        somaredGY += (copy[i + k][j + l].rgbtRed * gy[k + 1][l + 1]);
                        somagreenGX += (copy[i + k][j + l].rgbtGreen * gx[k + 1][l + 1]);
                        somagreenGY += (copy[i + k][j + l].rgbtGreen * gy[k + 1][l + 1]);
                        somablueGX += (copy[i + k][j + l].rgbtBlue * gx[k + 1][l + 1]);
                        somablueGY += (copy[i + k][j + l].rgbtBlue * gy[k + 1][l + 1]);
                    }
                }
            }

            resultRed = (sqrt((somaredGX * somaredGX) + (somaredGY * somaredGY))) * 10;
            resultGreen = (sqrt((somagreenGX * somagreenGX) + (somagreenGY * somagreenGY))) * 10;
            resultBlue = (sqrt((somablueGX * somablueGX) + (somablueGY * somablueGY))) * 10;

            if(resultRed % 10 >= 5)
            {
                resultRed = (resultRed / 10) + 1;
            } else
            {
                resultRed = resultRed / 10;
            }

            if(resultRed >= 255)
            {
                resultRed = 255;
            }

            if(resultGreen % 10 >= 5)
            {
                resultGreen = (resultGreen / 10) + 1;
            } else
            {
                resultGreen = resultGreen / 10;
            }

            if(resultGreen >= 255)
            {
                resultGreen = 255;
            }

            if(resultBlue % 10 >= 5)
            {
                resultBlue = (resultBlue / 10) + 1;
            } else
            {
                resultBlue = resultBlue / 10;
            }

            if(resultBlue >= 255)
            {
                resultBlue = 255;
            }

            image[i][j].rgbtRed = resultRed;
            image[i][j].rgbtGreen = resultGreen;
            image[i][j].rgbtBlue = resultBlue;
        }
    }

    return;
}
