#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define Tamano 30
#define Lim_Sup 100
#define Lim_Inf -100
#define Variables 2

float Funcion_Optimizar(float *x){
    float Suma=0;
    for(int i=0;i<Variables;i++){
        Suma=Suma+x[i]*x[i]-10*cosf(2*M_PI*x[i]);
    }
    return 10*Variables+Suma;
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
    float Pos[Variables];
    float Gasto;
};

void Calcular_Gasto(struct Agente* *Tabla){
    for(int i=0;i<Tamano;i++){
        Tabla[i]->Gasto=Funcion_Optimizar(Tabla[i]->Pos);
    }
}

struct Agente * Crear_Agente(){
    struct Agente* Agen = (struct Agente*) malloc(sizeof(struct Agente));
    for(int i=0;i<Variables;i++){
        Agen->Pos[i] = Pos_Ini();
    }
    Agen->Gasto  = Funcion_Optimizar(Agen->Pos);
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
    float *Pos1,*Pos2;
    for(int j=0;j<Variables;j++){
        Aux1->Pos[j] = Padre2->Pos[j];
        Aux2->Pos[j] = Padre2->Pos[j];
        Pos1 = &Padre1->Pos[j],Pos2 = &Aux1->Pos[j];
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
        Pos1 = &Padre1->Pos[j],Pos2 = &Aux2->Pos[j];
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
        if( Funcion_Optimizar(Aux1->Pos) < Funcion_Optimizar(Padre2->Pos) ){
            Padre2->Pos[j] = Aux1->Pos[j];
        }
        if( Funcion_Optimizar(Aux2->Pos) < Funcion_Optimizar(Padre2->Pos) ){
            Padre2->Pos[j] = Aux1->Pos[j];
        }
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
    float *Pos1;
    for(int j=0;j<Variables;j++){
        Pos1 = &Padre1->Pos[j];
        memcpy(&bitsP1, &Pos1, sizeof(bitsP1));
        for(int i=0;i<32;i++){
            if(((*bitsP1 >> i) & 1) == 0){
                *bitsP1 |= (1 << i);
            }else{
                *bitsP1 &= ~(1 << i);
            }
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
    int Mejor,j;
    srand(time(NULL));
    struct Agente* Vec_Agentes[Tamano];
    Ini_Agentes(Vec_Agentes);
    Mejor = Calcular_Mejor(Vec_Agentes,Mejor);
    for(j=0;j<Variables;j++){
        printf("x%d:%f, ",j+1,Vec_Agentes[Mejor]->Pos[j]);
    }
    printf("Gasto:%f\n",Vec_Agentes[Mejor]->Gasto);


    for(int i=0;i<20;i++){
        Regenerar_Poblacion(Vec_Agentes);
        Mutar_Poblacion(Vec_Agentes);
        Calcular_Gasto(Vec_Agentes);
        Mejor = Calcular_Mejor(Vec_Agentes,Mejor);
        for(j=0;j<Variables;j++){
            printf("x%d:%f, ",j+1,Vec_Agentes[Mejor]->Pos[j]);
        }
        printf("Gasto:%f\n",Vec_Agentes[Mejor]->Gasto);

    }


    Liberar_Tabla(Vec_Agentes);


    return 0;
}
