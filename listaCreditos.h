#include <stdio.h>
#include <stdlib.h>
#include "listaClientes.h"



typedef struct Credito{
    int id;
    double montoPrestado;
    double montoPagado;
    double montoAPagar;
    double interes;
    int cuotas;
    int cuotasPagas;
    int idCliente;
    struct Credito *siguiente;
} Credito;




int tamano_lista_creditos = 0;

static double calcularMontoAPagar(double montoPrestado, double interes){
    return montoPrestado + (montoPrestado * (interes / 100));
}


Credito* crearCredito(Cliente *cliente){

    Credito creditoNuevo;

    printf("Monto: ");
    scanf("%lf", &creditoNuevo.montoPrestado);

    printf("Interes: ");
    scanf("%lf", &creditoNuevo.interes);

    printf("Cuotas: ");
    scanf("%d", &creditoNuevo.cuotas);

    creditoNuevo.montoAPagar = calcularMontoAPagar(creditoNuevo.montoPrestado, creditoNuevo.interes);
    creditoNuevo.montoPagado = 0;
    creditoNuevo.id = 45;
    creditoNuevo.idCliente = cliente->id;

    printf("\nMonto Prestado: %lf\n", creditoNuevo.montoPrestado);
    printf("Interes: %lf\n", creditoNuevo.interes);
    printf("Cuotas: %d\n", creditoNuevo.cuotas);
    printf("Monto a pagar: %lf\n", creditoNuevo.montoAPagar);

    Credito *pcredito;
    pcredito = malloc(sizeof(Credito));
    pcredito = &creditoNuevo;
    return pcredito;
}


static void mostrarDatos(Credito *credito){
    printf("%d - %lf - %lf - %lf - %d - %lf - %d\n", credito->id, credito->montoPrestado, credito->interes, credito->montoAPagar, credito->cuotas, credito->montoPagado, credito->cuotasPagas);
}




Credito* agregar_credito(Credito *lista, Credito *nuevo){

    Credito *aux;
    aux = lista;

    if(lista == NULL){
        tamano_lista_creditos++;
        return nuevo;
    }else{
        if(nuevo->id < lista->id){
            nuevo->siguiente = lista;
            tamano_lista_creditos++;
            return nuevo;
        }else{
            while(aux->siguiente != NULL && aux->siguiente->id < nuevo->id){
                aux = aux->siguiente;
            }
            nuevo->siguiente = aux->siguiente;
            aux->siguiente = nuevo;
            tamano_lista_creditos++;
            return lista;
        }
    }
}

Credito* borrar_credito(Credito *lista, int idCredito){

    Credito *aux= lista;
    int encontro = 0;

    if(lista == NULL){
        printf("\n-LISTA VACIA- No hay elementos para borrar.");
    }else{
        if(aux->id == idCredito){
            lista = aux->siguiente;
            encontro = 1;
            tamano_lista_creditos--;
            return lista;
        }else if (aux->siguiente != NULL){
            while (aux->siguiente != NULL && aux->siguiente->id != idCredito){
                aux = aux->siguiente;
            }
            if(aux->siguiente != NULL && aux->siguiente->id == idCredito){
                aux->siguiente = aux->siguiente->siguiente;
                encontro = 1;
                tamano_lista_creditos--;
                return lista;
            }
        }
        if(encontro == 0){
            printf("No existe el elemento que desea borrar");
            return lista;
        }
    }
}



void imprimir_creditos(Credito *lista){

    Credito *aux = lista;
    int corte = 0;

    if(lista == NULL){
        printf("-LISTA VACIA- No hay elementos para mostrar.");
    } else{
        while (corte == 0) {
            mostrarDatos(aux);
            if(aux->siguiente != NULL) {
                aux = aux->siguiente;
            }else{
                corte = 1;
            }
        }
    }
}





void menu(Credito *lista){
    printf("\n-----------------------------");
    printf("\n1 - Agregar elemento\n");
    printf("2 - Borrar elemento\n");
    printf("3 - Cantidad de elementos\n");
    printf("4 - Imprimir\n");
    printf("5 - Salir\n\n");

    int opcion;
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            printf("\nAGREGAR ELEMENTO");
            crearCredito nodoNuevo = *crearnodo();
            lista = agregar_elemento(lista,&nodoNuevo);
            menu(lista);
            break;
        case 2:
            printf("\nELIMINAR ELEMENTO");
            printf("\nIntroduzca el valor a borrar: ");
            int valor_borrar;
            scanf("%d",&valor_borrar);
            lista = borrar_elemento(lista,valor_borrar);
            menu(lista);
            break;
        case 3:
            printf("\nCANTIDAD DE ELEMENTOS DE LA LISTA: %d\n", tamano_lista);
            menu(lista);
            break;
        case 4:
            printf("\nLISTAR ELEMENTOS\n");
            imprimir_elementos(lista);
            menu(lista);
            break;
        case 5:
            return;
        default:
            printf("Introduzca una opcion valida");
            menu(lista);
    }


}

int main(){

    printf("\n----LISTA ENLAZADA----");
    Credito *lista = NULL;
    //lista = malloc(sizeof(struct Nodo));
    menu(lista);
    return 0;
}