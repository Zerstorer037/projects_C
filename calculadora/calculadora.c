#include <stdio.h>
#include <math.h>

float suma(float *n1, float *n2) {
    return *n1 + *n2;  // Usamos * para acceder al valor al que apunta el puntero
}

float resta(float *n1, float *n2) {
    return *n1 - *n2;
}

float division(float *n1, float *n2) {
    return *n1 / *n2;
}

float multiplicar(float *n1, float *n2) {
    return *n1 * *n2;
}

int main() {
    float n1 = 0;
    float n2 = 0;
    
    printf("Ingresa tu primer numero: \n");
    scanf("%f", &n1);  // Usamos & para pasar la dirección de memoria
    
    printf("Ingresa tu segundo numero: \n");
    scanf("%f", &n2);  // Usamos & para pasar la dirección de memoria

    // Pasamos las direcciones de las variables n1 y n2 a las funciones
    printf("La suma es: %.2f\n", suma(&n1, &n2));
    printf("La resta es: %.2f\n", resta(&n1, &n2));
    printf("La multiplicar es: %.2f\n", multiplicar(&n1, &n2));
    printf("La division es: %.2f\n", division(&n1, &n2));
}
/*
-recordemos que cuando uno usa scanf(tiene que declarar que "%f" lo agarra  y lo guarada en la variable que quieras)
-"%.2f\n" es la cantidad de decimales que quieres que muestre en pantalla 
*/