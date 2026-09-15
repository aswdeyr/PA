#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <immintrin.h>

// 1 bytes  = 8   bits
// 2 bytes  = 16  bits
// 4 bytes  = 32  bits
// 8 bytes  = 64  bits
// 16 bytes = 128 bits
// 32 bytes = 256 bits

void print_Binario_128(unsigned long long *Numero_Imp){
    int i,Cont;
    Cont = 1;
    printf("\n");
    for(i=127;i>-1;i--){
        if(i==63){
            Cont = 0;
        }
        printf("%d",(*(Numero_Imp+Cont) >> i) & 1);
    }
    printf("\n");
}
void print_Binario_16(unsigned short *Numero_Imp){
    int i;
    printf("\n");
    for(i=15;i>-1;i--){
        printf("%d",(*Numero_Imp >> i) & 1);
    }
    printf("\n");
}
void print_Binario_32(unsigned long *Numero_Imp){
    int i;
    printf("\n");
    for(i=31;i>-1;i--){
        printf("%d",(*Numero_Imp >> i) & 1);
    }
    printf("\n");
}
void print_Binario_64(unsigned long long *Numero_Imp){
    int i;
    printf("\n");
    for(i=63;i>-1;i--){
        printf("%d",(*Numero_Imp >> i) & 1);
    }
    printf("\n");
}
void Multiplicar_16(unsigned short *A,unsigned short *B,unsigned long *Resultado_short){
    int i,j,k;
    for(i=15;i>-1;i--){
        for(j=15;j>-1;j--){
            if (i==15){
                *Resultado_short |= (((*A>> 15-j) & 1)*((*B>> 15-i) & 1) << 31-(j+i+1));
            }else{
                if(((*A>> 15-j) & 1)*((*B>> 15-i) & 1) == 1){
                    if(((*Resultado_short >> 31-(j+i+1)) & 1) == 1){
                        *Resultado_short &= ~(1 << 31-(j+i+1));
                        for(k=(j+i+1);k>-1;k--){
                            if(((*Resultado_short >> 31-(k-1)) & 1) == 0){
                                *Resultado_short |= (1 << 31-(k-1));
                                break;
                            }else{
                                *Resultado_short &= ~(1 << 31-(k-1));
                            }
                        }
                    }else{
                        *Resultado_short |= (1 << 31-(j+i+1));
                    }
                }
            }
        }
    }
}
void Multiplicar_64(unsigned long long *A,unsigned long long *B,unsigned long long *Resultado_short){
    int i,j,k,Cont;
    for(i=63;i>-1;i--){
        Cont = 0;
        for(j=63;j>-1;j--){
            if((i+j+1)==63){
                Cont = 1;
            }
            if (i==63){
                *(Resultado_short + Cont) |= (((*A>> 63-j) & 1)*((*B>> 63-i) & 1) << 127-(j+i+1));
            }else{
                if(((*A>> 63-j) & 1)*((*B>> 63-i) & 1) == 1){
                    if(((*(Resultado_short + Cont) >> 127-(j+i+1)) & 1) == 1){
                        *(Resultado_short + Cont) &= ~(1 << 127-(j+i+1));
                        for(k=(j+i+1);k>-1;k--){
                            if(((*(Resultado_short + Cont) >> 127-(k-1)) & 1) == 0){
                                *(Resultado_short + Cont) |= (1 << 127-(k-1));
                                break;
                            }else{
                                *(Resultado_short + Cont) &= ~(1 << 127-(k-1));
                            }
                        }
                    }else{
                        *(Resultado_short + Cont) |= (1 << 127-(j+i+1));
                    }
                }
            }
        }
    }
}


union Numeros {
    unsigned char Bits8[32];
    unsigned short int Bitsp;
    unsigned long long Bits64[4];
};

int main()
{
    union Numeros Datos;
    int i,j,k;
    bool BitA,BitB;
    unsigned short A,B;
    unsigned long Resultado_short;
    unsigned short *A_ANum_16,*A_BNum_16;
    unsigned long long A64,B64,Resultado_128[2];
    unsigned long long *A_ANum_64,*A_BNum_64,*Res_128;
    unsigned long *Res;

    Res = &Resultado_short;
    A_ANum_16 = &A;
    A_BNum_16 = &B;

    Resultado_short=0;
    A=50;
    B=120;
    printf("Multiplicacion de dos numeros de 16 bits\n");
    print_Binario_16(A_ANum_16);
    print_Binario_16(A_BNum_16);
    Multiplicar_16(A_ANum_16,A_BNum_16,Res);
    print_Binario_32(Res);
    printf("%d\n\n",Resultado_short);



    Res_128 = &Resultado_128[0];
    A_ANum_64 = &A64;
    A_BNum_64 = &B64;

    Resultado_128[0]=0;
    Resultado_128[1]=0;
    A64=10000000000000000000000000000000;
    B64=2;
    printf("Multiplicacion de dos numeros de 64 bits\n");
    print_Binario_64(A_ANum_64);
    print_Binario_64(A_BNum_64);
    Multiplicar_64(A_ANum_64,A_BNum_64,Res_128);


    print_Binario_128(Res_128);




    return 0;
}
