#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Nota:Usar "_" y no " " en las cadenas de texto
struct Nodo{
    char Nombre[50];
    int Edad;
    char Puesto[30];
    int Salario;
    struct Nodo * Siguiente;
};

struct Cola{
    struct Nodo * Frente;
    struct Nodo * Fin;
};

struct Cola * CrearCola(){
    struct Cola * cola = (struct Cola *) malloc(sizeof(struct Cola));
    cola->Frente = cola->Fin = NULL;
    return cola;
};

int Vacia(struct Cola * cola){
    return cola->Frente == NULL;
}

void Agregar_ACola(struct Cola * cola,char Nombre[50],int Edad,char Puesto[30],int Salario){
    struct Nodo * NuevoNodo = (struct Nodo *) malloc(sizeof(struct Nodo));
    strcpy(NuevoNodo->Nombre, Nombre);
    NuevoNodo->Edad=Edad;
    strcpy(NuevoNodo->Puesto, Puesto);
    NuevoNodo->Salario=Salario;
    NuevoNodo->Siguiente = NULL;
    if(Vacia(cola)){
        cola->Frente = cola->Fin = NuevoNodo;
    }
    else{
        cola->Fin->Siguiente = NuevoNodo;
        cola->Fin = NuevoNodo;
    }
}

void Quitar_Cola(struct Cola * cola){
    if(Vacia(cola)){
        printf("La cola esta vacia\n");
    }
    else{
        struct Nodo * Temp = cola->Frente;

        cola->Frente = cola->Frente->Siguiente;

        printf("%s\n",Temp->Nombre);
        printf("%d\n",Temp->Edad);
        printf("%s\n",Temp->Puesto);
        printf("%d\n",Temp->Salario);

        free(Temp);
    }
}

void Imprimir(struct Cola * cola){
    struct Nodo * Actual = cola->Frente;
    int i = 0;
    while(Actual != NULL){
        i++;
        printf("N: %d\n",i);
        printf("%s\n",Actual->Nombre);
        printf("%d\n",Actual->Edad);
        printf("%s\n",Actual->Puesto);
        printf("%d\n",Actual->Salario);
        printf("\n");
        printf("\n");
        Actual = Actual->Siguiente;
    }
}

int main()
{
    struct Cola * cola = CrearCola();
    int Opc=0,Edad,Salario;
    char Nombre[50],Puesto[30];

    while(Opc != 4){

        printf("\n");
        printf("1.-A adir elemento a la cola\n");
        printf("2.-Eliminar elemento de la cola\n");
        printf("3.-Imprimir cola\n");
        printf("4.-Salir\n");
        printf("\n");

        printf("Escoga una opcion\n");
        scanf("%d",&Opc);
        printf("\n");

        if(Opc==1){
            printf("Ingrese Nombre: \n");
            scanf("%s",Nombre);
            printf("\n");
            printf("Ingrese Edad: \n");
            scanf("%d",&Edad);
            printf("\n");
            printf("Ingrese Puesto: \n");
            scanf("%s",Puesto);
            printf("\n");
            printf("Ingrese Salario: \n");
            scanf("%d",Salario);
            printf("\n");
            Agregar_ACola(cola,Nombre,Edad,Puesto,Salario);
            printf("La cola es:\n");
            Imprimir(cola);
        }
        if(Opc==2){
            printf("Se elimino a:\n");
            Quitar_Cola(cola);
        }
        if(Opc==3){
            printf("La cola es:\n");
            Imprimir(cola);
        }
        fflush(stdin);
        //system("cls");
    }

    return 0;
}
