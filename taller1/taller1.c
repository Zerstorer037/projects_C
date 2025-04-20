#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define CANTIDAD_PISOS 7
#define CARGA_ASCENSOR 8
#define MAX_ESPERANDO_PISO 5
#define PESO_POR_PERSONA 73.327542

typedef struct {
    int destino;
} Pasajero;

void inicializar_pisos(int espera[CANTIDAD_PISOS]) {
    for (int i = 0; i < CANTIDAD_PISOS; i++) {
        espera[i] = rand() % (MAX_ESPERANDO_PISO + 1);
    }
}

void bajar_pasajeros(Pasajero ascensor[], int *cantidad, int piso_actual) {
    int i = 0;
    while (i < *cantidad) {
        if (ascensor[i].destino == piso_actual) {
            for (int j = i; j < (*cantidad) - 1; j++) {
                ascensor[j] = ascensor[j + 1];
            }
            (*cantidad)--;
        } else {
            i++;
        }
    }
}

void subir_pasajeros(Pasajero ascensor[], int *cantidad, int espera[], int piso_actual) {
    while (*cantidad < CARGA_ASCENSOR && espera[piso_actual] > 0) {
        Pasajero nuevo;
        do {
            nuevo.destino = rand() % CANTIDAD_PISOS;
        } while (nuevo.destino == piso_actual);

        ascensor[*cantidad] = nuevo;
        (*cantidad)++;
        espera[piso_actual]--;
    }
}

void mostrar_panel_de_estado(
    int piso_actual,
    int cantidad_pasajeros,
    Pasajero ascensor[],
    int espera[],
    int subiendo
) {
    printf("===========================================\n");
    printf("Piso actual: %d\n", piso_actual);
    printf("Dirección: %s\n", subiendo ? "Subiendo" : "Bajando");
    printf("Personas en el ascensor: %d\n", cantidad_pasajeros);
    printf("Peso total: %.6f kg\n", cantidad_pasajeros * PESO_POR_PERSONA);

    printf("\nPersonas esperando en cada piso:\n");
    for (int i = 0; i < CANTIDAD_PISOS; i++) {
        printf("  Piso %d: %d personas\n", i, espera[i]);
    }

    printf("\nPisos marcados en la botonera:\n  ");
    int marcados[CANTIDAD_PISOS] = {0};
    int hay_destinos = 0;

    for (int i = 0; i < cantidad_pasajeros; i++) {
        marcados[ascensor[i].destino] = 1;
    }

    for (int i = 0; i < CANTIDAD_PISOS; i++) {
        if (marcados[i]) {
            printf("%d ", i);
            hay_destinos = 1;
        }
    }

    if (!hay_destinos) {
        printf("(ninguno)");
    }

    printf("\n===========================================\n\n");
}

int main() {
    srand(time(NULL));

    int espera[CANTIDAD_PISOS];
    Pasajero ascensor[CARGA_ASCENSOR];
    int cantidad_pasajeros = 0;
    int piso_actual = 0;
    int subiendo = 1;

    inicializar_pisos(espera);

    printf("Simulación del ascensor iniciada\n");

    while (1) {
        bajar_pasajeros(ascensor, &cantidad_pasajeros, piso_actual);
        subir_pasajeros(ascensor, &cantidad_pasajeros, espera, piso_actual);

        mostrar_panel_de_estado(piso_actual, cantidad_pasajeros, ascensor, espera, subiendo);

        if (subiendo) {
            piso_actual++;
            if (piso_actual == CANTIDAD_PISOS - 1)
                subiendo = 0;
        } else {
            piso_actual--;
            if (piso_actual == 0)
                subiendo = 1;
        }

        sleep(5);
    }
    return 0;
}
