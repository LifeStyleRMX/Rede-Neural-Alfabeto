#include <QObject>
#include <QList>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLCDNumber>
#include <QVector>
#include "Padrao.h"
#include "Botao.h"
#include "RedeNeural.h"
#include "qcustomplot.h"

class Interface : public QWidget {
    Q_OBJECT

private:

    QList < QList < Botao *> > entrada;
    QGridLayout * gridLayoutBotoesEntrada;
    QHBoxLayout * boxLayoutHorizontal;
    QVBoxLayout * boxLayoutEsquerda;
    QVBoxLayout * boxLayoutVertical;
    QLabel * resultadoRedeNeural;
    QLabel * labelEspaco;
    QList <Padrao> padroes;
    RedeNeural * rede;
    QCustomPlot * customPlot;

    QPushButton * buttonTreinarRede;
    QPushButton * buttonReconhecerPadrao;

    QLabel * labelTaxaDeAprendizado;
    QLabel * labelErroMaximo;
    QLabel * labelQtdMaximoEpocas;
    QLabel * labelEpocas;
    QLCDNumber * lcdEpocas;
    QLabel * labelErroMedio;
    QLCDNumber * lcdErroMedio;

    QLineEdit * lineTaxaDeAprendizado;
    QLineEdit * lineErroMaximo;
    QLineEdit * lineQtdMaximoEpocas;

    QLabel * labelEntradaDefinida;
    QLineEdit * lineEntradaDefinida;
    QPushButton * buttonEntradaDefinida;

    QVector <double> xAxis;
    QVector <double> yAxis;

    int qtdNeuroniosOculta, qtdNeuroniosSaida, qtdEpocas;
    double taxaAprendizado, erroMaximo;

public:
    Interface();
    ~Interface();

public slots:
    void clickBotao(bool status, int i, int j);
    void treinaRede();
    void reconheceEntrada();
    void entradaDefinida();
    void atualizaGrafico(double x, double y);
};
