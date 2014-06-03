#include "RedeNeural.h"
#include "iostream"
#include <math.h>
#include <QString>

RedeNeural::RedeNeural(QList <Padrao> padroes, int epocas, double erro, double aprendizado) {
    entradas = padroes;

    qtdEpocas = epocas;
    maximoErro = erro;
    taxaAprendizado = aprendizado;
    ErroQuadratico = 0;
    somaErros = 0;

    qtdNeuroniosOculta = 10;
    qtdNeuroniosSaida = 36;

}

RedeNeural::~RedeNeural() {
    entradaCamadaSaida.clear();
    pesosCamadaOculta.clear();
    pesosCamadaSaida.clear();
    delete saidaCamadaOculta;
    delete saidaCamadaSaida;
    delete netCamadaSaida;
    delete netCamadaOculta;
    delete erroCamadaSaida;
    delete erroCamadaOculta;
}

double RedeNeural::saidaNeuronio(QList <double> pEntradas, double * pPesos, int qtdentradas, double * net, int indice ) {
    double netRetorno = 0;
    for (int i = 0; i < qtdentradas; i++) {
        netRetorno += pEntradas[i] * pPesos[i];
    }
    net[indice] = netRetorno;

    return (1.0 / (1.0 + exp(-netRetorno))); // Logística, 0 a 1
}

void  RedeNeural::treinarRede() {

    for(int j=0;j<10;j++){
        double * dialog = new double [49];
        for(int i=0;i<49;i++){
            double min = -0.5;
            double max = 0.5;
            double range = (max - min);
            double div = RAND_MAX / range;
            double tmp = (min + (rand() / div));
            dialog[i] = tmp;
        }
        pesosCamadaOculta.insert(j,dialog);
    }

    for(int j=0;j<36;j++){
        double * dialog = new double [10];
        for(int i=0;i<10;i++){
            double min = -0.5;
            double max = 0.5;
            double range = (max - min);
            double div = RAND_MAX / range;
            double tmp = (min + (rand() / div));
            dialog[i] = tmp;
        }
        pesosCamadaSaida.insert(j,dialog);
    }



    int controleEpocas = 0;
    do {

        somaErros = 0;
        ErroQuadratico = 0;

        for(int nPadrao = 0; nPadrao < entradas.size(); nPadrao++){
            saidaCamadaOculta = new double [qtdNeuroniosOculta];
            saidaCamadaSaida = new double [qtdNeuroniosSaida];
            netCamadaSaida = new double [qtdNeuroniosSaida];
            netCamadaOculta = new double [qtdNeuroniosOculta];
            erroCamadaSaida = new double [qtdNeuroniosSaida];
            erroCamadaOculta = new double [qtdNeuroniosOculta];


            // Calcula a saída dos neuronios da camada oculta
            for(int i=0;i<qtdNeuroniosOculta;i++) {
                saidaCamadaOculta[i]= saidaNeuronio(entradas[nPadrao].valores,pesosCamadaOculta[i],49,netCamadaOculta,i);
                entradaCamadaSaida.insert(i,saidaCamadaOculta[i]);
            }

            // Calcula a saída dos neuronios de saida com base no resultado dos neuronios da camada oculta
            for(int i=0;i<qtdNeuroniosSaida;i++) {
                saidaCamadaSaida[i] = saidaNeuronio(entradaCamadaSaida,pesosCamadaSaida[i],qtdNeuroniosOculta,netCamadaSaida,i);
            }

            // Calcula o erro da saída
            for(int i=0;i<qtdNeuroniosSaida;i++){
                erroCamadaSaida[i] = (entradas[nPadrao].resultados[i] - saidaCamadaSaida[i])*((1.0 / (1.0 + exp(-netCamadaSaida[i]))) * (1.0 - (1.0 / (1.0 + exp(-netCamadaSaida[i])))));
                for(int j=0;j<qtdNeuroniosOculta;j++){
                    pesosCamadaSaida[i][j] += taxaAprendizado * entradaCamadaSaida[j] * erroCamadaSaida[i];
                }
            }

            // Calcula o erro da camada oculta
            for(int i=0;i<10;i++){
                double net = 0;
                for(int a=0;a<36;a++){
                    net += pesosCamadaSaida[a][i] * erroCamadaSaida[a];
                }
                erroCamadaOculta[i] = (net)*((1.0 / (1.0 + exp(-netCamadaOculta[i]))) * (1.0 - (1.0 / (1.0 + exp(-netCamadaOculta[i])))));
                for(int j=0;j<49;j++){
                    pesosCamadaOculta[i][j] += taxaAprendizado * entradas[nPadrao].valores[j] * erroCamadaOculta[i];
                }
            }


            //std::cout << "for calcula erro oculta e redistribuição dos pesos" << std::endl;

            for(int i=0;i<36;i++) {
                somaErros += pow((entradas[nPadrao].resultados[i]-saidaCamadaSaida[i]),2);
            }

            entradaCamadaSaida.clear();
            delete saidaCamadaOculta;
            delete saidaCamadaSaida;
            delete netCamadaSaida;
            delete netCamadaOculta;
            delete erroCamadaSaida;
            delete erroCamadaOculta;
        }

        double x = 2*36;
        ErroQuadratico = somaErros / x;

        //std::cout << ErroQuadratico << std::endl;

        controleEpocas++;

        emit fimDeEpoca(controleEpocas,ErroQuadratico);
        emit atualizaLCDEpocas(controleEpocas);
        emit atualizaLCDErro(ErroQuadratico);

    } while((controleEpocas < qtdEpocas) && (ErroQuadratico > maximoErro));

}

QString  RedeNeural::reconhecer(QList <double> ent) {

    saidaCamadaOculta = new double [qtdNeuroniosOculta];
    saidaCamadaSaida = new double [qtdNeuroniosSaida];
    netCamadaSaida = new double [qtdNeuroniosSaida];
    netCamadaOculta = new double [qtdNeuroniosOculta];

    // Calcula a saída dos neuronios da camada oculta
    for(int i=0;i<qtdNeuroniosOculta;i++) {
        saidaCamadaOculta[i]= saidaNeuronio(ent,pesosCamadaOculta[i],49,netCamadaOculta,i);
        entradaCamadaSaida.insert(i,saidaCamadaOculta[i]);
    }

    // Calcula a saída dos neuronios de saida com base no resultado dos neuronios da camada oculta
    for(int i=0;i<qtdNeuroniosSaida;i++) {
        saidaCamadaSaida[i] = saidaNeuronio(entradaCamadaSaida,pesosCamadaSaida[i],qtdNeuroniosOculta,netCamadaSaida,i);
        //std::cout << saidaCamadaSaida[i] << std::endl;
    }

    double maior = 0;
    int indice = 0;
    for(int i=0; i<36; i++){
        if(saidaCamadaSaida[i] > maior){
            maior = saidaCamadaSaida[i];
            indice = i;
        }
    }

    char * alfabeto = "0987654321ZYXWVUTSRQPONMLKJIHGFEDCBA";

    QString retorno;

    //std::cout << alfabeto[indice] << std::endl;

    retorno = alfabeto[indice];

    entradaCamadaSaida.clear();
    delete saidaCamadaOculta;
    delete saidaCamadaSaida;
    delete netCamadaSaida;
    delete netCamadaOculta;

    return retorno;

}
