#include <cs50.h>
#include <math.h>
#include <stdio.h>

long potencia(int base, int expoente)
{
    long long int resultado = 1;
    if (expoente == 0)
    {
        return 1;
    }

    for (int i = expoente; i != 0; i--)
    {
        resultado *= base;
    }

    return resultado;
}

int main(void)
{

    long int number = 0;
    int contador = 0;
    int check1 = 0;
    int check2 = 0;
    // cartao 0 = invalido  / cartao 1 = visa / cartao 2 = mastercard / cartao 3 = amex
    int cartao = 0;

    // Input do numero
    do
    {
        number = get_long("Digite o Numero do seu cartao.\n");
    }
    while (number < 0);

    long int number1 = number;
    // quantidade de digitos
    while (number1 != 0)
    {
        number1 /= 10;
        contador++;
    }

    // check1

    if (contador != 13 && contador != 15 && contador != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        for (int i = 2; i <= contador; i += 2)
        {
            int precheck = ((number * 10) / potencia(10, i) % 10) * 2;
            int precheck2 = (precheck / 10) + (precheck % 10);
            check1 += precheck2;
        }
        for (int j = 1; j <= contador; j += 2)
        {
            check2 += ((number * 10) / potencia(10, j) % 10);
        }

        if ((check1 + check2) % 10 != 0)
        {
            printf("INVALID\n");
        }
        else
        {
            if (((number * 10) / potencia(10, contador) % 10 == 4) && (contador == 13 || contador == 16))
            {
                printf("VISA\n");
            }
            else if (((number * 10) / potencia(10, contador) % 10 == 3) &&
                     ((number * 10) / potencia(10, contador - 1) % 10 == 4 ||
                      (number * 10) / potencia(10, (contador - 1)) % 10 == 7) &&
                     (contador == 15))
            {
                printf("AMEX\n");
            }
            else if (((number * 10) / potencia(10, contador) % 10 == 5) &&
                     ((number * 10) / potencia(10, (contador - 1)) % 10 >= 1 &&
                      (number * 10) / potencia(10, (contador - 1)) % 10 <= 5) &&
                     (contador == 16))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}
