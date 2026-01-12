#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        int check = 0;
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (argv[1][i] >= 48 && argv[1][i] <= 57)
            {
                check = 0;
            }
            else
            {
                check++;
            }
        }

        if (check == 0)
        {
            string text = get_string("Plaintext: \n");
            int index = 0;
            int novo;

            for (int i = 0; i < strlen(text); i++)
            {
                if (isalpha(text[i]) && isupper(text[i]))
                {
                    index = (int) text[i] - 65;
                    novo = (index + key) % 26;
                    text[i] = novo + 65;
                }
                else if (isalpha(text[i]) && islower(text[i]))
                {
                    index = (int) text[i] - 97;
                    novo = (index + key) % 26;
                    text[i] = novo + 97;
                }
            }
            printf("Ciphertext: %s\n", text);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    return 0;
}
