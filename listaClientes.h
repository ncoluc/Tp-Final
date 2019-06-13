#include <stdio.h>
#include <stdlib.h>




typedef struct Cliente{
    int id;
    char[50] nombre;
    char[50] apellido;
    int dni;
    int edad;
    int idCredito;
    int idClienteConocido;
    struct Cliente *clienteConocido;
    struct Credito *credito;
    struct Cliente *siguiente;
} Cliente;



int tamano_lista_clientes = 0;


static void mostrarDatosCliente(Cliente *cliente){
    printf("%d - %s - %s - %d - %d - %d\n", cliente->id, cliente->apellido, cliente->nombre, cliente->dni, cliente->edad, cliente->idCredito);
}


Cliente* crearCliente(char nombre[], char apellido[], int dni, int edad,Cliente *conocido){

    Cliente clienteNuevo;

    strcpy(clienteNuevo.apellido, nombre);
    strcpy(clienteNuevo.apellido, apellido);
    clienteNuevo.dni = dni;
    clienteNuevo.edad = edad;
    clienteNuevo.idCredito = -1;
    clienteNuevo.credito = NULL;
    clienteNuevo.siguiente = NULL;

    if(conocido != NULL){
        clienteNuevo.idClienteConocido = conocido->id;
        clienteNuevo.clienteConocido = conocido;
    }else{
        clienteNuevo.idClienteConocido = -1;
        clienteNuevo.clienteConocido = NULL;
    }

    printf("\nNombre: %s\n", clienteNuevo.nombre);
    printf("Apellido: %s\n", clienteNuevo.apellido);
    printf("DNI: %d\n", clienteNuevo.dni);
    printf("Edad: %d\n", clienteNuevo.edad);

    Cliente *pcliente;
    pcliente = malloc(sizeof(Cliente));
    pcliente = &clienteNuevo;
    return pcliente;
}


Cliente* agregar_cliente(Cliente *lista, Cliente *nuevo){

    Cliente *aux;
    aux = lista;

    if(lista == NULL){
        tamano_lista_clientes++;
        return nuevo;
    }else{
        if(nuevo->apellido < lista->apellido){
            nuevo->siguiente = lista;
            tamano_lista_clientes++;
            return nuevo;
        }else{
            while(aux->siguiente != NULL && strcmp(aux->siguiente->apellido,nuevo->apellido) < 0){
                aux = aux->siguiente;
            }
            if(strcmp(aux->siguiente->apellido,nuevo->apellido) == 0){
                while(aux->siguiente != NULL  && strcmp(aux->siguiente->apellido,nuevo->apellido) == 0 && strcmp(aux->siguiente->nombre,nuevo->nombre) < 0){
                    aux = aux->siguiente;
                }
            }
            nuevo->siguiente = aux->siguiente;
            aux->siguiente = nuevo;
            tamano_lista_clientes++;
            return lista;
        }
    }
}



void imprimir_clientes(Cliente *lista){

    Cliente *aux = lista;
    int corte = 0;

    if(lista == NULL){
        printf("-LISTA VACIA- No hay elementos para mostrar.");
    } else{
        while (corte == 0) {
            mostrarDatosCliente(aux);
            if(aux->siguiente) {
                aux = aux->siguiente;
            }else{
                corte = 1;
            }
        }
    }
}





