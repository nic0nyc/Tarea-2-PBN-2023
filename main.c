#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void agregarDeuda(vehiculo** lista){
    FILE* deudasFile;
    deudasFile = fopen("deudas.txt", "r");

    char line[200];
    while(fgets(line, 199, deudasFile)){
        char* patente;
        patente = strtok(line, ",");
        int deudaTemporal = atoi(strtok(NULL, ","));
        char* pago;
        pago = strtok(NULL, ",");
        pago[strcspn(pago, "\n")] = 0;

        for (int i = 0; i < numeroVehiculos; i++){
            if(strcmp(patente, lista[i]->patente) == 0){
                if(*pago == 78){
                    lista[i]->deuda += deudaTemporal;
                }
            }
        }
    }
    fclose(deudasFile); 
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
    free(lista);

}

void ordenarAlfabeticamente(vehiculo** lista){
    vehiculo** listaOrdenada = leerInformacionVehiculos();
    agregarDeuda(listaOrdenada);
    char* patenteMenor = malloc(6*sizeof(char));
    for (int i = 0; i < 6; i++) patenteMenor[i] = 123;

    int indexMenor = 0;
    for (int k = 0; k < numeroVehiculos; k++){ 
        for (int i = 0; i < numeroVehiculos; i++){
            if (strcmp(patenteMenor, listaOrdenada[i]->patente) > 0){
                strcpy(patenteMenor,listaOrdenada[i]->patente);
                indexMenor = i;
            }
        }
        strcpy(lista[k]->patente, patenteMenor);
        strcpy(lista[k]->modelo, listaOrdenada[indexMenor]->modelo);
        strcpy(lista[k]->tipo, listaOrdenada[indexMenor]->tipo);
        strcpy(lista[k]->marca, listaOrdenada[indexMenor]->marca);
        strcpy(lista[k]->color, listaOrdenada[indexMenor]->color);
        strcpy(lista[k]->comuna, listaOrdenada[indexMenor]->comuna);
        lista[k]->deuda = listaOrdenada[indexMenor]->deuda;
        strcpy(listaOrdenada[indexMenor]->patente, "{{{{{{");
        for (int i = 0; i < 6; i++) patenteMenor[i] = 123;
    }
    
    free(patenteMenor);
    limpiarMemoriaLista(listaOrdenada);
}

int main(){

    vehiculo** lista = leerInformacionVehiculos();
    
    agregarDeuda(lista);

    ordenarAlfabeticamente(lista);
    
    for (int i = 0; i < numeroVehiculos; i++) printf("%s\n", lista[i]->patente);

    imprimirVehiculo(lista, "AMLK30");

    limpiarMemoriaLista(lista);

    return 0;
}