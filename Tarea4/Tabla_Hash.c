#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Tamano 30

struct Registro{
    char *Nombre;
    int Clave;
    struct Registro * Siguiente;
};

struct Registro * Crear_Registro(int Indice,struct Registro * *Tabla,char *Nombre,int Clave){
    struct Registro * Regis = (struct Registro *) malloc(sizeof(struct Registro));
    Tabla[Indice] = Regis;
    Regis->Nombre = Nombre;
    Regis->Clave  = Clave;
    Regis->Siguiente = NULL;
    printf("Nuevo registro creado:\n");
    printf("Indice: %d\n",Indice);
    printf("Nombre: %s\n",Regis->Nombre);
    printf("Clave:  %d\n",Regis->Clave);
    printf("\n\n");
};

struct Registro * Agregar_Registro(int Indice,struct Registro * Regis_Act,char *Nombre,int Clave){
    struct Registro * Nuevo_Registro = (struct Registro *) malloc(sizeof(struct Registro));
    Regis_Act->Siguiente = Nuevo_Registro;
    Nuevo_Registro->Nombre = Nombre;
    Nuevo_Registro->Clave  = Clave;
    Nuevo_Registro->Siguiente = NULL;
    printf("Nuevo registro creado:\n");
    printf("Indice: %d\n",Indice);
    printf("Nombre: %s\n",Nuevo_Registro->Nombre);
    printf("Clave:  %d\n",Nuevo_Registro->Clave);
    printf("\n\n");
};

int Cal_Indice(char *Cadena){
    int i=0;
    int Indice=0;
    while (*(Cadena+i) != '\0') {
        Indice = Indice + (int)(*(Cadena+i))*i;
        i++;
    }
    Indice=Indice%30;
    return Indice;
}

void  Recibir_Registro(char *Nombre,int Clave,struct Registro * *Tabla){
    int Indice = Cal_Indice(Nombre);
    if(Tabla[Indice]==NULL){
        Crear_Registro(Indice,Tabla,Nombre,Clave);
    }
    else{
        struct Registro * Aux;
        Aux = NULL;
        Aux = Tabla[Indice];
        if(Clave==Aux->Clave){
            printf("Ya existe esta clave en este indice.\n\n");
            return;
        }
        while(Aux->Siguiente!=NULL){
            if(Clave==Aux->Clave){
                printf("Ya existe esta clave en este indice.\n\n");
                return;
            }
            Aux = Aux->Siguiente;
        }
        Agregar_Registro(Indice,Aux,Nombre,Clave);
        free(Aux);
    }
}

void  Ini_Tab(struct Registro * *Tabla){
    for(int i=0;i<Tamano;i++){
        Tabla[i]=NULL;
    }
}

void main()
{

    struct Registro* Tabla_Hash[Tamano];
    Ini_Tab(Tabla_Hash);


    Recibir_Registro("Angel",25,Tabla_Hash);
    Recibir_Registro("Ernesto",13,Tabla_Hash);
    Recibir_Registro("Francisco",20,Tabla_Hash);
    Recibir_Registro("Angel",8,Tabla_Hash);
    Recibir_Registro("Julian",32,Tabla_Hash);
    Recibir_Registro("Angel",25,Tabla_Hash);


    return;
}
