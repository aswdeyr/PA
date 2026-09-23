#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Nota:Usar "_" y no " " en las cadenas de texto
struct Nodo{
    char Nombre[50];
    int Edad;
    char Puesto[30];
    int Salario;
    struct Nodo * Anterior;
};

struct Pila{
    struct Nodo * Base;
    struct Nodo * Techo;
};

struct Pila * CrearPila(){
    struct Pila * pila = (struct Pila *) malloc(sizeof(struct Pila));
    pila->Base = pila->Techo = NULL;
    return pila;
};

int Vacia(struct Pila * pila){
    return pila->Base == NULL;
}

void Agregar_APila(struct Pila * pila,char Nombre[50],int Edad,char Puesto[30],int Salario){
    struct Nodo * NuevoNodo = (struct Nodo *) malloc(sizeof(struct Nodo));
    strcpy(NuevoNodo->Nombre, Nombre);
    NuevoNodo->Edad=Edad;
    strcpy(NuevoNodo->Puesto, Puesto);
    NuevoNodo->Salario=Salario;
    NuevoNodo->Anterior = NULL;
    if(Vacia(pila)){
        pila->Base = pila->Techo = NuevoNodo;
    }
    else{
        NuevoNodo->Anterior = pila->Techo;
        pila->Techo = NuevoNodo;
    }
}

void Quitar_Pila(struct Pila * pila){
    if(Vacia(pila)){
        printf("La pila esta vacia\n");
    }
    else{
        struct Nodo * Temp = pila->Techo;

        pila->Techo = pila->Techo->Anterior;

        printf("%s\n",Temp->Nombre);
        printf("%d\n",Temp->Edad);
        printf("%s\n",Temp->Puesto);
        printf("%d\n",Temp->Salario);

        free(Temp);
    }
}

void Imprimir(struct Pila * pila){
    struct Nodo * Actual = pila->Techo;
    while(Actual != NULL){
        printf("%s\n",Actual->Nombre);
        printf("%d\n",Actual->Edad);
        printf("%s\n",Actual->Puesto);
        printf("%d\n",Actual->Salario);
        printf("\n");
        printf("\n");
        Actual = Actual->Anterior;
    }
}

int main()
{
    struct Pila * pila = CrearPila();
    int Opc=0,Edad,Salario;
    char Nombre[50],Puesto[30];

    while(Opc != 4){

        printf("\n");
        printf("1.-Añadir elemento a la pila\n");
        printf("2.-Eliminar elemento de la pila\n");
        printf("3.-Imprimir pila\n");
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
            Agregar_APila(pila,Nombre,Edad,Puesto,Salario);
            printf("La pila es:\n");
            Imprimir(pila);
        }
        if(Opc==2){
            printf("Se elimino a:\n");
            Quitar_Pila(pila);
        }
        if(Opc==3){
            printf("La pila es:\n");
            Imprimir(pila);
        }
        fflush(stdin);
        //system("cls");
    }

    return 0;
}
