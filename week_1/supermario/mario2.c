#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height;
    int gap = 2;

    do
    {
        height = get_int("Qual a largura maxima da piramide? \n");
    }
    while (height < 1 || height > 8);

    int c = height - 1;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        for (int l = 0; l < gap; l++)
        {
            printf(" ");
        }
        for (int m = 0; m < i; m++)
        {
            printf("#");
        }
        printf("\n");
        c--;
    }
}
