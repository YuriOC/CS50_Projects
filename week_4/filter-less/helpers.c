#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {

            int red = ((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) +
                       (0.189 * image[i][j].rgbtBlue)) *
                      10;
            if (red > 2550)
            {
                red = 2550;
            }
            else if (red % 10 != 0 && red % 10 >= 5)
            {
                red += 10;
            }

            int green = ((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) +
                         (0.168 * image[i][j].rgbtBlue)) *
                        10;
            if (green > 2550)
            {
                green = 2550;
            }
            else if (green % 10 != 0 && green % 10 >= 5)
            {
                green += 10;
            }

            int blue = ((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) +
                        (0.131 * image[i][j].rgbtBlue)) *
                       10;
            if (blue > 2550)
            {
                blue = 2550;
            }
            else if (blue % 10 != 0 && blue % 10 >= 5)
            {
                blue += 10;
            }

            image[i][j].rgbtRed = red / 10;
            image[i][j].rgbtGreen = green / 10;
            image[i][j].rgbtBlue = blue / 10;
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
            if(somaRed % 10 >= 5)
            {
                image[i][j].rgbtRed = (somaRed / 10) + 1;
            } else
            {
                image[i][j].rgbtRed = somaRed / 10;
            }

            somaGreen = somaGreen * 10 / count;
            if(somaGreen % 10 >= 5)
            {
                image[i][j].rgbtGreen = (somaGreen / 10) + 1;
            } else
            {
                image[i][j].rgbtGreen = somaGreen / 10;
            }

            somaBlue = somaBlue * 10 / count;
            if(somaBlue % 10 >= 5)
            {
                image[i][j].rgbtBlue = (somaBlue / 10) + 1;
            } else
            {
                image[i][j].rgbtBlue = somaBlue / 10;
            }
        }
    }
    return;
}
