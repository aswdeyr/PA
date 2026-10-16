#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Tamano 30
#define Lim_Sup 100
#define Lim_Inf -100

float X_Cuadrada(float x){
    return x*x;
}

float Numero_0_1(){
    return ((float)(rand()%100)/100)+0.01;
}

float Pos_Ini(){
    return (float)(rand()%(Lim_Sup*1000-Lim_Inf*1000+1*1000)+Lim_Inf*1000)/1000;
}

int Agente_Aleatorio(){
    return rand()%(Tamano);
}

struct Agente{
    float Pos;
    float Gasto;
};

void Calcular_Gasto(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        Tabla[i]->Gasto=X_Cuadrada(Tabla[i]->Pos);
    }
}

struct Agente * Crear_Agente(){
    struct Agente* Agen = (struct Agente*) malloc(sizeof(struct Agente));
    Agen->Pos = Pos_Ini();
    Agen->Gasto  = X_Cuadrada(Agen->Pos);
    return Agen;
};

void print_Binario_32(float *Numero_Imp){
    unsigned long *bits;
    int i;
    memcpy(&bits, &Numero_Imp, sizeof(bits));
    printf("\n");
    for(i=31;i>-1;i--){
        printf("%d",(*bits >> i) & 1);
    }
    printf("\n");
}
void Combinar_Padres(struct Agente* Padre1,struct Agente* Padre2){
    unsigned long *bitsP1,*bitsP2;
    struct Agente* Aux1 = (struct Agente*) malloc(sizeof(struct Agente));
    struct Agente* Aux2 = (struct Agente*) malloc(sizeof(struct Agente));
    Aux1->Pos = Padre2->Pos;
    Aux2->Pos = Padre2->Pos;
    float *Pos1 = &Padre1->Pos,*Pos2 = &Aux1->Pos;
    memcpy(&bitsP1, &Pos1, sizeof(bitsP1));
    memcpy(&bitsP2, &Pos2, sizeof(bitsP2));
    for(int i=0;i<12;i++){
        if(((*bitsP1>> i) & 1) ^ ((*bitsP2>> i) & 1) == 1){
            if(((*bitsP2 >> i) & 1) == 0){
                *bitsP2 |= (1 << i);
            }else{
                *bitsP2 &= ~(1 << i);
            }
        }
    }
    for(int i=24;i<28;i++){
        if(((*bitsP1>> i) & 1) ^ ((*bitsP2>> i) & 1) == 1){
            if(((*bitsP2 >> i) & 1) == 0){
                *bitsP2 |= (1 << i);
            }else{
                *bitsP2 &= ~(1 << i);
            }
        }
    }
    Pos1 = &Padre1->Pos,Pos2 = &Aux2->Pos;
    memcpy(&bitsP1, &Pos1, sizeof(bitsP1));
    memcpy(&bitsP2, &Pos2, sizeof(bitsP2));
    for(int i=12;i<24;i++){
        if(((*bitsP1>> i) & 1) ^ ((*bitsP2>> i) & 1) == 1){
            if(((*bitsP2 >> i) & 1) == 0){
                *bitsP2 |= (1 << i);
            }else{
                *bitsP2 &= ~(1 << i);
            }
        }
    }
    for(int i=28;i<32;i++){
        if(((*bitsP1>> i) & 1) ^ ((*bitsP2>> i) & 1) == 1){
            if(((*bitsP2 >> i) & 1) == 0){
                *bitsP2 |= (1 << i);
            }else{
                *bitsP2 &= ~(1 << i);
            }
        }
    }
    if( X_Cuadrada(Aux1->Pos) < X_Cuadrada(Padre2->Pos) ){
        Padre2->Pos = Aux1->Pos;
    }
    if( X_Cuadrada(Aux2->Pos) < X_Cuadrada(Padre2->Pos) ){
        Padre2->Pos = Aux1->Pos;
    }
    free(Aux1);
    free(Aux2);
}


void  Ini_Agentes(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        Tabla[i]=Crear_Agente();
    }
}

void  Liberar_Tabla(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        free(Tabla[i]);
    }
}

int Calcular_Mejor(struct Agente* *Tabla,int Mejor){
    for(int i=0;i<Tamano;i++){
        if(Tabla[i]->Gasto<Tabla[Mejor]->Gasto){
            Mejor = i;
        }
    }
    return Mejor;
}

void Regenerar_Poblacion(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        if(Numero_0_1() <= 0.9){
            Combinar_Padres(Tabla[Agente_Aleatorio()],Tabla[Agente_Aleatorio()]);
        }
    }
}

void Mutacion(struct Agente* Padre1){
    unsigned long *bitsP1;
    float *Pos1 = &Padre1->Pos;
    memcpy(&bitsP1, &Pos1, sizeof(bitsP1));
    for(int j=0;j<32;j++){
        if(((*bitsP1 >> j) & 1) == 0){
            *bitsP1 |= (1 << j);
        }else{
            *bitsP1 &= ~(1 << j);
        }
    }
}

void Mutar_Poblacion(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        if(Numero_0_1() <= 0.1){
            Mutacion(Tabla[i]);
        }
    }
}

int main()
{
    int Mejor;
    srand(time(NULL));
    struct Agente* Vec_Agentes[Tamano];
    Ini_Agentes(Vec_Agentes);
    Mejor = Calcular_Mejor(Vec_Agentes,Mejor);
    printf("Posicion:%f , Gasto:%f\n",Vec_Agentes[Mejor]->Pos,Vec_Agentes[Mejor]->Gasto);

    for(int i=0;i<20;i++){
        Regenerar_Poblacion(Vec_Agentes);
        Mutar_Poblacion(Vec_Agentes);
        Calcular_Gasto(Vec_Agentes);
        Mejor = Calcular_Mejor(Vec_Agentes,Mejor);
        printf("Posicion:%f , Gasto:%f\n",Vec_Agentes[Mejor]->Pos,Vec_Agentes[Mejor]->Gasto);

    }


    Liberar_Tabla(Vec_Agentes);


    return 0;
}
