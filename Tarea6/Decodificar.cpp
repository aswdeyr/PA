#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

void Decodificar(string Codigo,string Codificacion){
    int PosAct_Codigo,PosAct_Codificacion,PosUlt_Codificacion,PosUlt_Codigo;
    PosAct_Codigo=PosUlt_Codigo=1;
    PosAct_Codificacion=PosUlt_Codificacion=0;
    while(PosAct_Codificacion<Codificacion.length()){
        if(Codigo[PosAct_Codigo]==Codificacion[PosAct_Codificacion]){
            if(PosAct_Codigo>=Codigo.length()){
                cout << Codigo[PosUlt_Codigo-1];
                PosUlt_Codigo=1;
                PosAct_Codigo=0;
                PosUlt_Codificacion=PosAct_Codificacion+1;
            }
            if(Codigo[PosAct_Codigo+1]!= '0' && Codigo[PosAct_Codigo+1]!='1'){
                cout << Codigo[PosUlt_Codigo-1];
                PosUlt_Codigo=1;
                PosAct_Codigo=0;
                PosUlt_Codificacion=PosAct_Codificacion+1;
            }
        }
        if(Codigo[PosAct_Codigo]!=Codificacion[PosAct_Codificacion]){
            PosAct_Codificacion=PosUlt_Codificacion-1;
            while(Codigo[PosAct_Codigo]=='0' || Codigo[PosAct_Codigo]=='1'){
                PosAct_Codigo++;
            }
            PosUlt_Codigo=PosAct_Codigo+1;
        }
        PosAct_Codigo++;
        PosAct_Codificacion++;
    }
}


int main() {
    string Codigo,Linea_Act,Codificacion;
    int i;

    ifstream Texto_Entrada("Codificacion.txt");
    while (getline (Texto_Entrada, Linea_Act)) {
        if(Linea_Act.length()>20){
            Codificacion = Linea_Act;
            break;
        }
        Codigo=Codigo+Linea_Act[0];
        i=4;
        while(i<Linea_Act.length()){
            Codigo=Codigo+Linea_Act[i];
            i++;
        }
    }
    Decodificar(Codigo,Codificacion);
    //cout << Codigo << endl;
    //cout << Codificacion << endl;

    return 0;
}