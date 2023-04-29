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

int compararDeuda(const void *a, const void *b){

    vehiculo *vehiculoA = *(vehiculo **)a;
    vehiculo *vehiculoB = *(vehiculo **)b;

    int deudaA = vehiculoB->deuda;
    int deudaB = vehiculoA->deuda;

    return (deudaA - deudaB);

}

void ordenarPorDeuda(vehiculo** lista){

    qsort(lista, numeroVehiculos, sizeof(vehiculo *), compararDeuda);

}

void deudaN(vehiculo** listaOrdenadaDeudas, int n){
    for (int i = 0; i < n; i++){
        printf("%s: %d\n", listaOrdenadaDeudas[i]->patente, listaOrdenadaDeudas[i]->deuda);
    }
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

void deudoresPatente(vehiculo** listaOrdenadaPatente, char* simbolo){
    char * copia = malloc(6*sizeof(char));
    int iguales = 0;
    for (int i = 0; i < numeroVehiculos; i++){
        strcpy(copia, listaOrdenadaPatente[i]->patente);
        if (copia[0] > simbolo[0]) break;
        else{
            if (strstr(listaOrdenadaPatente[i]->patente, simbolo) != NULL){
                if (simbolo[0] == copia[0]){
                    printf("%s: %d\n", listaOrdenadaPatente[i]->patente, listaOrdenadaPatente[i]->deuda);
                }
            }
        }
    }
    free(copia);
}

void deudoresComuna(vehiculo** lista, char* comuna){
    printf("Aqui va la funcion de las comunas");
}

void menu(void){
    printf("Elige un numero\n");
    printf("1. Conocer la deuda de un vehiculo\n");
    printf("2. Conocer la deuda de los n vehiculos con mas deudas y sus deudas\n");
    printf("3. Conocer los deudores de una comuna\n");
    printf("4. Conocer la deuda de las patentes que comiencen con cierto string\n");
    printf("5. Salir\n");
}

int main(){

    vehiculo** listaOrdenadaPatente = leerInformacionVehiculos();
    agregarDeuda(listaOrdenadaPatente);
    ordenarAlfabeticamente(listaOrdenadaPatente);

    vehiculo** listaOrdenadaDeudas = leerInformacionVehiculos();
    agregarDeuda(listaOrdenadaDeudas);
    ordenarPorDeuda(listaOrdenadaDeudas);

    void (*funcionListaChar[]) (vehiculo**, char*) = {imprimirVehiculo, deudoresComuna, deudoresPatente};
    void (*funcionListaInt) (vehiculo**, int) = deudaN;

    int opcion;
    menu();
    scanf("%d", &opcion);

    while (opcion != 5){
        if (opcion == 1){
            char* patente = malloc(6*sizeof(char));
            printf("Ingresa la patente del vehiculo: ");
            scanf("%s", patente);
            funcionListaChar[0](listaOrdenadaDeudas, patente);
            free(patente);
        }
        else if(opcion == 2){
            int n;
            printf("Ingresa un valor para n: ");
            scanf("%d", &n);
            funcionListaInt(listaOrdenadaDeudas, n);
        }
        else if(opcion == 3){
            char* comuna = malloc(40*sizeof(char));
            printf("Ingresa el nombre de la comuna: ");
            scanf("%s", comuna);
            comuna = realloc(comuna, sizeof(comuna)*sizeof(char));
            funcionListaChar[1](listaOrdenadaDeudas, comuna);
            free(comuna);
        }
        else if(opcion == 4){
            char* simbolo = malloc(6*sizeof(char));
            printf("Ingresa el string de comienzo de patentes: ");
            scanf("%s", simbolo);
            simbolo = realloc(simbolo, sizeof(simbolo)*sizeof(char));
            funcionListaChar[2](listaOrdenadaPatente, simbolo);
            free(simbolo);
        }
        else{
            printf("Ingresa un numero valido");
        }
        printf("\n");
        menu();
        scanf("%d", &opcion);
    }

    limpiarMemoriaLista(listaOrdenadaPatente);
    limpiarMemoriaLista(listaOrdenadaDeudas);

    return 0;
}