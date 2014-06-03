#include "Padrao.h"
#include <iostream>

using namespace std;

Padrao::Padrao (const char * _valores, const char * _resultados) {
    for(int i=0;i<49;i++) {
        valores.insert(i,_valores[i]);
        if(valores[i] == 48) {
            valores[i] = 0;
        } else if (valores[i] == 49) {
            valores[i] = 1;
        }
    }

    for(int i=0;i<36;i++){
        resultados.insert(i,_resultados[i]);
        if(resultados[i] == 48) {
            resultados[i] = 0;
        } else if (resultados[i] == 49) {
            resultados[i] = 1;
        }
    }
}

Padrao::~Padrao(){
    valores.clear();
    resultados.clear();
}

