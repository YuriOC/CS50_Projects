#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int start, target;
    int anos = 0;

    // Start size imput
    do
    {
        start = get_int("Start Size: \n");
    }
    while (start < 9);

    // Target size imput
    do
    {
        target = get_int("Target Size: \n");
    }
    while (target < start);

    for (int i = 0; start < target; i++)
    {
        start = start + (start / 3) - (start / 4);
        anos++;
    }

    printf("Years: %d\n", anos);
}
