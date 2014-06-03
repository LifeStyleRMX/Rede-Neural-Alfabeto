#include <QList>
#include "Padrao.h"
#include <QWidget>
#include <QVector>

class RedeNeural : public QWidget {

    Q_OBJECT

public:

    QList <double> entradaCamadaSaida;
    QList <double *> pesosCamadaOculta;
    QList <double *> pesosCamadaSaida;
    double * saidaCamadaOculta;
    double * saidaCamadaSaida;
    double * netCamadaSaida;
    double * netCamadaOculta;
    double * erroCamadaSaida;
    double * erroCamadaOculta;


    QList <Padrao> entradas;

    int qtdEpocas, qtdNeuroniosOculta, qtdNeuroniosSaida;
    double maximoErro, taxaAprendizado, ErroQuadratico, somaErros;

    RedeNeural(QList <Padrao> padroes, int epocas, double erro, double aprendizado);
    ~RedeNeural();
    void treinarRede();
    QString reconhecer(QList<double> ent);
    double saidaNeuronio(QList <double> pEntradas, double * pPesos, int qtdentradas, double * net, int indice );

signals:
    void fimDeEpoca(double x, double y);
    void atualizaLCDEpocas(int epocas);
    void atualizaLCDErro(double erro);
};
