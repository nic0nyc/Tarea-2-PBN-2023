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
    int patenteEncontrada = 0;
    for (int i = 0; i < numeroVehiculos; i++)
    {
        if(!strcmp(patente, lista[i]->patente)){
            patenteEncontrada++;
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
    if (patenteEncontrada ==0){
        printf("Patente no encontrada\n");
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
    int stringEncontrado = 0;
    for (int i = 0; i < numeroVehiculos; i++){
        strcpy(copia, listaOrdenadaPatente[i]->patente);
        if (copia[0] > simbolo[0]) break;
        else{
            if (strstr(listaOrdenadaPatente[i]->patente, simbolo) != NULL){
                if (simbolo[0] == copia[0]){
                    stringEncontrado++;
                    printf("%s: %d\n", listaOrdenadaPatente[i]->patente, listaOrdenadaPatente[i]->deuda);
                }
            }
        }
    }
    if (stringEncontrado == 0){
        printf("No hay ninguna patente que comience con el string indicado (el string debe estar en mayuscula)\n");
    }
    free(copia);
}

int compararComunas(const void *a, const void *b){

    vehiculo *vehiculoA = *(vehiculo **)a;
    vehiculo *vehiculoB = *(vehiculo **)b;

    char* comunaA = vehiculoB->comuna;
    char* comunaB = vehiculoA->comuna;

    return strcmp(comunaB, comunaA);

}

void ordenarPorComuna(vehiculo** lista){

    qsort(lista, numeroVehiculos, sizeof(vehiculo *), compararComunas);

}

void deudoresComuna(vehiculo** lista, char* comuna){
    
    int encontrado = 0;
    int stopSearching = 0;

    for (int i = 0; i < numeroVehiculos; i++)
    {
        if(stopSearching) break;

        if(!strcmp(lista[i]->comuna, comuna)){

            imprimirVehiculo(lista, lista[i]->patente);
            encontrado = 1;
        }else if(encontrado == 1){
            stopSearching = 1;
        }

        printf("Buscando %s de %s\n", lista[i]->patente, lista[i]->comuna);
    }
    
    if(!encontrado){
        printf("No hay ningun vehiculo registrado en esa comuna");
    }

}

void menu(void){
    printf("deuda [patente]\n");
    printf("deuda [n]\n");
    printf("deudores comuna [comuna]\n");
    printf("deudores patente [string]\n");
    printf("salir\n");
    printf("Ingresa un comando: ");
}

int main(){

    vehiculo** listaOrdenadaPatente = leerInformacionVehiculos();
    agregarDeuda(listaOrdenadaPatente);
    ordenarAlfabeticamente(listaOrdenadaPatente);

    vehiculo** listaOrdenadaDeudas = leerInformacionVehiculos();
    agregarDeuda(listaOrdenadaDeudas);
    ordenarPorDeuda(listaOrdenadaDeudas);

    vehiculo** listaOrdenadaComunas = leerInformacionVehiculos();
    agregarDeuda(listaOrdenadaComunas);
    ordenarPorComuna(listaOrdenadaComunas);

    void (*funcionListaChar[]) (vehiculo**, char*) = {imprimirVehiculo, deudoresComuna, deudoresPatente};
    void (*funcionListaInt) (vehiculo**, int) = deudaN;

    
    char opcion[40];
    menu();
    fgets(opcion, 40, stdin);
    opcion[strcspn(opcion, "\n")] = 0;
    int l = strlen(opcion);

    char* split;
    while(strcmp(opcion, "salir") != 0){
        if (opcion[l-1] == 32) printf("Comando invalido porque el comando termina con un espacio\n");
        else{
            int n = 0;
            for (int i = 0; i < l; i++){
                if (opcion[i] == 32) n++;
            }
            if (n == 0){
                printf("Comando invalido\n");
            }
            else if (n == 1){
                split = strtok(opcion, " ");
                if (strcmp(split, "deuda") == 0){
                    split = strtok(NULL, " ");
                    if (split[0] >= 48 && split[0] <= 57){
                        int contador = 0;
                        for (int i = 0; i < strlen(split); i++){
                            if (split[i] < 48 || split[i] > 57){
                                contador++;
                            }
                        }
                        if (contador == 0){
                            int num = atoi(split);
                            if (num == 0) printf("EL numero debe ser mayor a 0\n");
                            else if (num > numeroVehiculos) printf("El numero maximo de vehiculos es: %d\n", numeroVehiculos);
                            else funcionListaInt(listaOrdenadaDeudas, num);
                        }
                        else {
                            printf("Comando invalido porque no es un numero\n");
                        }
                    }
                    else if (split[0] >= 65 && split[0] <= 90 || split[0] >= 97 && split[0] <= 122){
                        if (strlen(split) != 6){
                            printf("La petente no tiene 6 caracteres\n");
                        }
                        else{
                            int letras = 0;
                            for (int i = 0; i < 4; i++){
                                if (split[i] >= 65 && split[i] <= 90) letras++;
                            }
                            int digitos = 0;
                            for (int i = 4; i < 6; i++){
                                if (split[i] >= 48 && split[i] <= 57) digitos++;
                            }
                            if (letras == 4 && digitos == 2){
                                funcionListaChar[0](listaOrdenadaDeudas, split);
                            }
                            else{
                                printf("Formato de patente invalido, debe tener 4 letras mayusculas primero y 2 digitos al final\n");
                            }
                        }
                    }
                    else{
                        printf("Comando invalido porque la siguiente palabra a deuda no es un numero o una palabra existente\n");
                    }
                }
                else{
                    printf("Comando invalido porque la primera palabra no es el string deuda (tiene que ser en minuscula)\n");
                }

            }
            else if (n >= 2){
                split = strtok(opcion, " ");
                if (strcmp(split, "deudores") == 0){
                    split = strtok(NULL, " ");
                    if (strcmp(split, "comuna") == 0){
                        split = &opcion[16];
                        funcionListaChar[1](listaOrdenadaComunas, split);
                    }
                    else if(strcmp(split, "patente") == 0){
                        split = strtok(NULL, " ");
                        if (strlen(split) == 0 || strlen(split) > 6){
                            printf("El string debe tener una longitud entre 1 y 6\n");
                        }
                        else{
                            funcionListaChar[2](listaOrdenadaPatente, split);    
                        }
                    }
                    else{
                        printf("Comando invalido porque la siguiente palabra a deudores no es comuna o patente\n");    
                    }
                }
                else{
                    printf("Comando invalido porque la primera palabra no es el string deudores (tiene que ser en minuscula)\n");
                }
            }
            else{
                printf("Comando invalido porque hay mas palabras de las necesarias\n");
            }
        }
        printf("\n");
        menu();
        split = strtok(opcion, " ");
        fgets(opcion, 40, stdin);
        opcion[strcspn(opcion, "\n")] = 0;
        l = strlen(opcion);
    }

    limpiarMemoriaLista(listaOrdenadaPatente);
    limpiarMemoriaLista(listaOrdenadaDeudas);
    limpiarMemoriaLista(listaOrdenadaComunas);

    return 0;
}