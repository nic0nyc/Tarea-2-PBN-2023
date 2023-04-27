#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//hola
typedef struct vehiculo {
    char * patente;
    char * modelo;
    char * tipo;
    char * marca;
    char * color;
    char * comuna;
    int deuda;
} vehiculo;

int numeroVehiculos = 0;

vehiculo** leerInformacionVehiculos(){

    vehiculo **lista;

    FILE *vehiculosFile;

    vehiculosFile = fopen("vehiculos.txt", "r");

    char linea[200];

    int i = 0;

    while (fgets(linea, 200, vehiculosFile))
    {

        if(i == 0){
            lista = malloc(1 * sizeof(vehiculo));
        }else{
            lista = (vehiculo**) realloc(lista, (i + 1) * sizeof(vehiculo));
        }

        lista[i] = malloc(sizeof(vehiculo));

        char * patente = strtok(linea, ",");
        lista[i]->patente = malloc(sizeof(patente)*sizeof(char));
        strcpy(lista[i]->patente, patente);

        char * modelo = strtok(NULL, ",");
        lista[i]->modelo = malloc(sizeof(modelo)*sizeof(char));
        strcpy(lista[i]->modelo, modelo);

        char * tipo = strtok(NULL, ",");
        lista[i]->tipo = malloc(sizeof(tipo)*sizeof(char));
        strcpy(lista[i]->tipo, tipo);

        char * marca = strtok(NULL, ",");
        lista[i]->marca = malloc(sizeof(marca)*sizeof(char));
        strcpy(lista[i]->marca, marca);

        char * color = strtok(NULL, ",");
        lista[i]->color = malloc(sizeof(color)*sizeof(char));
        strcpy(lista[i]->color, color);

        char * comuna = strtok(NULL, ",");
        comuna[strcspn(comuna, "\n")] = 0;
        lista[i]->comuna = malloc(sizeof(comuna)*sizeof(char));
        strcpy(lista[i]->comuna, comuna);

        lista[i]->deuda = 0;

        i++;
    }

    fclose(vehiculosFile);

    numeroVehiculos = i;

    return lista;
}

void imprimirVehiculo(vehiculo** lista, char* patente){

    for (int i = 0; i < numeroVehiculos; i++)
    {
        if(!strcmp(patente, lista[i]->patente)){
            printf("---Información vehiculo----\n");
            printf("Patente: %s\n", lista[i]->patente);
            printf("Modelo: %s\n", lista[i]->modelo);
            printf("Tipo: %s\n", lista[i]->tipo);
            printf("Marca: %s\n", lista[i]->marca);
            printf("Color: %s\n", lista[i]->color);
            printf("Comuna: %s\n", lista[i]->comuna);
            printf("Deuda: %d\n", lista[i]->deuda);
            printf("---------------------------\n");
        }
    }

}

void limpiarMemoriaLista(vehiculo ** lista){

    for (int i = 0; i < numeroVehiculos; i++)
    {
        free(lista[i]->patente);
        free(lista[i]->modelo);
        free(lista[i]->tipo);
        free(lista[i]->marca);
        free(lista[i]->color);
        free(lista[i]->comuna);

        free(lista[i]);
    }
    

}

int main(){

    vehiculo** lista = leerInformacionVehiculos();

    imprimirVehiculo(lista, "GGOU88");

    limpiarMemoriaLista(lista);

    return 0;
}