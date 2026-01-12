#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{

    // tamanho max da string
    const int MaxLarge = 26;

    // se nao tiver nenhum valor depois do ./
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // se nao for do mesmo tamanho determinado
    if (strlen(argv[1]) != MaxLarge)
    {
        printf("Key must contain %d characters.\n", MaxLarge);
        return 1;
    }

    // variaveis para verificar repetidos
    int numberUp = 0;
    int numberLow = 0;
    int listNumbers[MaxLarge];

    // cria uma lista apenas com o numero 30.
    for (int j = 0; j < MaxLarge; j++)
    {
        listNumbers[j] = 30;
    }

    // verifica se o character e uma letra, e armazena no teste
    for (int i = 0; i < MaxLarge; i++)
    {
        if (isalpha(argv[1][i]) && isupper(argv[1][i]))
        {
            numberUp = argv[1][i] - 65;
            listNumbers[numberUp] = numberUp;
        }
        else if (isalpha(argv[1][i]) && islower(argv[1][i]))
        {
            numberLow = argv[1][i] - 97;
            listNumbers[numberLow] = numberLow;
            argv[1][i] -= 32;
        }
        else
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // testa se nao tem repetidos.
    for (int k = 0; k < MaxLarge; k++)
    {
        if (listNumbers[k] != k)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    string plainText = get_string("Plaintext: \n");
    int value = 0;

    for (int l = 0; l < strlen(plainText); l++)
    {
        if (isalpha(plainText[l]) && isupper(plainText[l]))
        {
            value = plainText[l] - 65;
            plainText[l] = argv[1][value];
        }
        else if (isalpha(plainText[l]) && islower(plainText[l]))
        {
            value = plainText[l] - 97;
            plainText[l] = argv[1][value] + 32;
        }
    }

    printf("ciphertext: %s\n", plainText);
}
