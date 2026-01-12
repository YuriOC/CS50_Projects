#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height;

    do
    {
        height = get_int("Qual a largura maxima da piramide? \n");
    }
    while (height < 1 || height > 8);

    int k = height - 1;
    for (int i = 0; i <= height; i++)
    {
        for (int c = 0; c <= k; c++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
        k--;
    }
}
