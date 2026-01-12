#include <stdio.h>
#include <cs50.h>
#include <math.h>


long potencia(int base, int expoente){
    int resultado = 1;
    if (expoente == 0){
        return 1;
    }

    for(int i = expoente;i != 0;i--){
        resultado *= base;
    }
    return resultado;
}

int main (void){

    long int number = 0;
    int contador = 0;
    int check1 = 0;

    int a = potencia(5, 3);

    printf("%d\n", a);



    // Input do numero
    /*
    do{
        number = get_long("Digite o Numero do seu cartao.\n");
    } while(number < 0);

    // quantidade de digitos
    while (number != 0) {
        number /= 10;
        contador++;
    }

    printf("%d\n", contador);*/

// numero / (10 * casas) % 10
}
