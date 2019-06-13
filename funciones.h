Cliente* listaClientesPorApellido[27];
Credito* listaCreditos = NULL;
char letrasApellidos[] = "ABDEFGHIJKLMNÑOPQRSTUVWXYZ";


int calcularPosicionConApellido(char apellido[]){
    for (int i = 0; i < 27; ++i) {
        if(letrasApellidos[i] == apellido[0]){
            return i;
        }
    }
}

Cliente* buscarClientePorNombre(){

    char nombreCliente[50];
    char apellidoCliente[50];

    printf("Apellido: ");
    scanf("%s", apellidoCliente);
    printf("Nombre: ");
    scanf("%s", nombreCliente);

    Cliente *aux;
    aux = listaClientesPorApellido[calcularPosicionConApellido(apellidoCliente)];

    if(aux == NULL){
        return NULL;
    }else{
        if(aux->apellido == apellidoCliente && aux->nombre == nombreCliente){
            return aux;
        }else{
            while(aux->siguiente != NULL && aux->siguiente->apellido != apellidoCliente){
                aux = aux->siguiente;
            }
            while(aux->siguiente != NULL  && aux->siguiente->apellido == apellidoCliente && aux->siguiente->nombre != nombreCliente){
                aux = aux->siguiente;
            }
            if(aux->siguiente != NULL && aux->siguiente->apellido == apellidoCliente && aux->siguiente->nombre == nombreCliente){
                return aux->siguiente;
            }else{
                return NULL;
            }

        }
    }
}


void mostrarClientesPorEdad(int edadInicial, int edadFinal) {

    Cliente *listaAuxClientesPorEdad = NULL;
    Cliente *aux = NULL;

    for (int i = 0; i < 27; ++i) {
        aux = listaClientesPorApellido[i];
        if (aux != NULL && aux->edad >= edadInicial && aux->edad <= edadFinal) {
            listaAuxClientesPorEdad = agregar_cliente(listaAuxClientesPorEdad, aux);
        }
        while (aux != NULL && aux->siguiente != NULL) {
            aux = aux->siguiente;
            if (aux->edad >= edadInicial && aux->edad <= edadFinal) {
                listaAuxClientesPorEdad = agregar_cliente(listaAuxClientesPorEdad, aux);
            }
        }
    }
    if(listaAuxClientesPorEdad != NULL){
        imprimir_clientes(listaAuxClientesPorEdad);
    }else{
        printf("No hay clientes para ese rango de Edad");
    }
}



void conexionEntreClientes(Cliente *cliente1, Cliente *cliente2){
    cliente1->clienteConocido = cliente2;
    cliente1->idClienteConocido = cliente2->id;

    cliente2->clienteConocido = cliente1;
    cliente2->idClienteConocido = cliente1->id;
}


void altaCliente(){
    Cliente nuevoCliente;

    char nombreCliente[50];
    char apellidoCliente[50];
    int dni;
    int edad;

    printf("Nombre: ");
    scanf("%s", nombreCliente);
    printf("Apellido: ");
    scanf("%s", apellidoCliente);
    printf("DNI: ");
    scanf("%d", &dni);
    printf("Edad: ");
    scanf("%d", &edad);

    printf("Alguna persona que conozcas ya es cliente y te recomendo nuestro Banco?\n*1 - SI\n*2 - NO\n");
    int decision;
    scanf("%d", &decision);
    if(decision == 1){
        Cliente *conocido = buscarClientePorNombre();
        nuevoCliente = crearCliente(nombreCliente, apellidoCliente, dni, edad, conocido);
        agregar_cliente(listaClientesPorApellido[calcularPosicionConApellido(nuevoCliente.apellido)], &nuevoCliente);
    }else if(decision == 2){
        nuevoCliente = crearCliente(nombreCliente, apellidoCliente, dni, edad, NULL);
        agregar_cliente(listaClientesPorApellido[calcularPosicionConApellido(nuevoCliente.apellido)], &nuevoCliente);
    }else{
        printf("Ingrese una opcion valida\n");
        altaCliente();
    }
}


void altaCredito(Cliente *cliente){
    Credito credito = *crearCredito(cliente);
    agregar_credito(listaCreditos, &credito);
    cliente->credito = &credito;
    cliente->idCredito = credito.id;
}

void listarClientes(){
    for (int i = 0; i < 27; ++i) {
        imprimir_clientes(listaClientesPorApellido[i]):
    }
}

void listarCreditos(){
    imprimir_creditos(listaCreditos);
}

void pagarCuotaCredito(Credito *credito){
    credito->cuotasPagas = credito->cuotasPagas + 1;
    credito->montoPagado = credito->montoPagado + (credito->montoAPagar/credito->cuotas);
}

void pagarCredito(Credito *credito){
    credito->cuotasPagas = credito->cuotas;
    credito->montoPagado = credito->montoAPagar;
}

void cancelarCredito(Cliente* cliente){
    borrar_credito(listaCreditos,cliente->idCredito);
    cliente->idCredito = -1;
    cliente->credito = NULL;
}