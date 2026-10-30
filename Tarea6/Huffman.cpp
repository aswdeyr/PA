#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

// Estructura para los nodos del árbol de Huffman
struct MinNode {
    char caracter;
    unsigned frecuencia;
    MinNode *izquierda, *derecha;

    MinNode(char caracter, unsigned frecuencia) {
        izquierda = derecha = nullptr;
        this->caracter = caracter;
        this->frecuencia = frecuencia;
    }

    ~MinNode() {
        delete izquierda;
        delete derecha;
    }
};

// Objeto de comparación para la cola de prioridad (Min-Heap)
struct Comparar {
    bool operator()(MinNode* l, MinNode* r) {
        return (l->frecuencia > r->frecuencia);
    }
};

// Función para generar los códigos de Huffman a partir del árbol
void generarCodigos(MinNode* raiz, string str, unordered_map<char, string>& codigosHuffman) {
    if (!raiz) return;

    if (raiz->caracter != '\0') {
        codigosHuffman[raiz->caracter] = str;
    }

    generarCodigos(raiz->izquierda, str + "0", codigosHuffman);
    generarCodigos(raiz->derecha, str + "1", codigosHuffman);
}

// Función principal para construir el árbol de Huffman y codificar el texto
void codificarHuffman(string texto) {

    ofstream Codificacion;
    Codificacion.open("Codificacion.txt");

    // 1. Calcular la frecuencia de cada carácter
    unordered_map<char, int> frecuenciaMapa;
    for (char c : texto) {
        frecuenciaMapa[c]++;
    }

    // 2. Crear una cola de prioridad para almacenar los nodos del árbol
    priority_queue<MinNode*, vector<MinNode*>, Comparar> minHeap;

    for (auto par : frecuenciaMapa) {
        minHeap.push(new MinNode(par.first, par.second));
    }

    // 3. Construir el árbol de Huffman combinando los nodos con menor frecuencia
    while (minHeap.size() != 1) {
        MinNode* izq = minHeap.top();
        minHeap.pop();

        MinNode* der = minHeap.top();
        minHeap.pop();

        // El carácter '\0' indica un nodo interno (no es una hoja)
        MinNode* sumNode = new MinNode('\0', izq->frecuencia + der->frecuencia);
        sumNode->izquierda = izq;
        sumNode->derecha = der;

        minHeap.push(sumNode);
    }

    MinNode* raiz = minHeap.top();

    // 4. Generar la tabla de códigos
    unordered_map<char, string> codigosHuffman;
    generarCodigos(raiz, "", codigosHuffman);

    cout << "=== TABLA DE CODIGOS DE HUFFMAN ===" << endl;
    for (auto par : codigosHuffman) {
        cout << par.first << " : " << par.second << endl;
        Codificacion << par.first << " : " << par.second << endl;
    }

    // 5. Mostrar el texto codificado
    string strCodificado = "";
    for (char c : texto) {
        strCodificado += codigosHuffman[c];
    }

    cout << "\nTexto original: " << texto << endl;
    cout << "Texto codificado: " << strCodificado << endl;


    Codificacion << strCodificado << endl;
    Codificacion.close();

    // Liberar memoria del árbol
    delete raiz;
}

int main() {
    string Texto,Linea_Act;

    ifstream Texto_Entrada("Texto_Prueba.txt");
    while (getline (Texto_Entrada, Linea_Act)) {
        Texto = Texto + " " + Linea_Act;
    }

    codificarHuffman(Texto);

    return 0;
}
