#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;
    int spaces = 0;
    int specialchar = 0;

    string text = get_string("Text: \n");

    for(int i = 0;i < strlen(text);i++)
    {
        if((int)toupper(text[i]) >= 65 && (int)toupper(text[i]) <= 90){
            letters++;
        }

        if((int)text[i] == 32)
        {
            spaces++;
            words = spaces + 1;
        }

        if((int)text[i] == 33 || (int)text[i] == 46 || (int)text[i] == 63)
        {
            sentences++;
        }
    }

    float L = ((float)letters /(float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;

    float index = ((0.0588 * L) - (0.296 * S)) - 15.8;


    int inteiro = index * 10;
    if(inteiro % 10 >= 5)
    {
        inteiro = (inteiro / 10) + 1;
    } else
    {
        inteiro = inteiro / 10;
    }


    //printf("index: %f\n", index);
    //printf("inteiro: %d\n", inteiro);

    if(inteiro < 1)
    {
        printf("Before Grade 1\n");
    } else if(inteiro >= 1 && inteiro <= 16)
    {
        printf("Grade %d\n", (int)inteiro);
    } else
    {
        printf("Grade 16+\n");
    }










}
