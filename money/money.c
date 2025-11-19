#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    float value;
    int cent25 = 25;
    int cent10 = 10;
    int cent5 = 5;
    int cent1 = 1;
    int total = 0;
    int valorint = 0;

    do
    {
        value = get_float("Digite o valor do troco. \n");
        valorint = round(value * 100);
    }
    while (value < 0);

    while (valorint >= cent25)
    {
        valorint -= cent25;
        total++;
    }

    while (valorint >= cent10)
    {
        valorint -= cent10;
        total++;
    }

    while (valorint >= cent5)
    {
        valorint -= cent5;
        total++;
    }

    while (valorint > 0)
    {
        valorint -= cent1;
        total++;
    }

    printf("Foram usadas %d moedas para dar esse troco.\n", total);
}
