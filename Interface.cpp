#include "Interface.h"
#include <iostream>
#include <QFile>
#include <QFont>

Interface::Interface() {
    qtdNeuroniosOculta = 10;
    qtdNeuroniosSaida = 36;
    /*************************************************************************************/
    /**************** Cria os elementos da interface grafica *****************************/
    /*************************************************************************************/
    gridLayoutBotoesEntrada = new QGridLayout();
    for(int i=0;i<7;i++){
        QList <Botao *> dialogList;
        for(int j=0;j<7;j++){ 
            Botao * dialogButton = new Botao(true,i,j);
            dialogButton->setFixedHeight(50);
            dialogButton->setFixedWidth(50);
            dialogList.insert(j,dialogButton);
            gridLayoutBotoesEntrada->addWidget(dialogButton,i,j,1,1);
        }
        entrada.insert(i,dialogList);
        dialogList.clear();
    }
    resultadoRedeNeural = new QLabel("");
    labelEspaco = new QLabel(" ");
    QFont dialogFont = resultadoRedeNeural->font();
    dialogFont.setPointSize(220);
    resultadoRedeNeural->setFont(dialogFont);
    labelEspaco->setFont(dialogFont);
    boxLayoutHorizontal = new QHBoxLayout();
    boxLayoutEsquerda = new QVBoxLayout();
    boxLayoutVertical = new QVBoxLayout();

    buttonTreinarRede = new QPushButton("Treinar Rede");
    buttonTreinarRede->setFixedWidth(300);
    buttonReconhecerPadrao = new QPushButton("Reconhecer");
    buttonReconhecerPadrao->setFixedWidth(300);

    labelTaxaDeAprendizado = new QLabel("Taxa de Aprendizado");
    labelTaxaDeAprendizado->setFixedWidth(300);
    labelErroMaximo = new QLabel("Erro Mínimo");
    labelErroMaximo->setFixedWidth(300);
    labelQtdMaximoEpocas = new QLabel("Épocas");
    labelQtdMaximoEpocas->setFixedWidth(300);
    labelEpocas = new QLabel("0");
    labelEpocas->setFixedWidth(300);

    lineTaxaDeAprendizado = new QLineEdit("0.1");
    lineTaxaDeAprendizado->setFixedWidth(300);
    lineErroMaximo = new QLineEdit("0.01");
    lineErroMaximo->setFixedWidth(300);
    lineQtdMaximoEpocas = new QLineEdit("10000");
    lineQtdMaximoEpocas->setFixedWidth(300);

    labelEpocas = new QLabel("Épocas Treinadas");
    labelEpocas->setFixedWidth(300);
    labelErroMedio = new QLabel("Erro Médio");
    labelErroMedio->setFixedWidth(300);

    lcdEpocas = new QLCDNumber();
    lcdEpocas->setFixedWidth(300);
    lcdErroMedio = new QLCDNumber();
    lcdErroMedio->setFixedWidth(300);

    labelEntradaDefinida = new QLabel("Pré-Defina uma Letra/Número");
    labelEntradaDefinida->setFixedWidth(300);
    lineEntradaDefinida = new QLineEdit();
    lineEntradaDefinida->setFixedWidth(300);
    buttonEntradaDefinida = new QPushButton("Definir");
    buttonEntradaDefinida->setFixedWidth(300);

    customPlot = new QCustomPlot();
    customPlot->addGraph();

    boxLayoutEsquerda->addWidget(labelTaxaDeAprendizado);
    boxLayoutEsquerda->addWidget(lineTaxaDeAprendizado);
    boxLayoutEsquerda->addWidget(labelErroMaximo);
    boxLayoutEsquerda->addWidget(lineErroMaximo);
    boxLayoutEsquerda->addWidget(labelQtdMaximoEpocas);
    boxLayoutEsquerda->addWidget(lineQtdMaximoEpocas);
    boxLayoutEsquerda->addWidget(buttonTreinarRede);
    boxLayoutEsquerda->addWidget(labelEpocas);
    boxLayoutEsquerda->addWidget(lcdEpocas);
    boxLayoutEsquerda->addWidget(labelErroMedio);
    boxLayoutEsquerda->addWidget(lcdErroMedio);
    boxLayoutEsquerda->addWidget(labelEntradaDefinida);
    boxLayoutEsquerda->addWidget(lineEntradaDefinida);
    boxLayoutEsquerda->addWidget(buttonEntradaDefinida);
    boxLayoutEsquerda->addWidget(buttonReconhecerPadrao);

    boxLayoutHorizontal->addLayout(boxLayoutEsquerda);
    boxLayoutHorizontal->addWidget(labelEspaco);
    boxLayoutHorizontal->addLayout(gridLayoutBotoesEntrada);
    boxLayoutHorizontal->addWidget(labelEspaco);
    boxLayoutHorizontal->addWidget(resultadoRedeNeural);

    boxLayoutVertical->addLayout(boxLayoutHorizontal);
    boxLayoutVertical->addWidget(customPlot);
    setLayout(boxLayoutVertical);
    /*************************************************************************************/

    /*************************************************************************************/
    /****************** Importa Padrões de entrada e Valores Esperados *******************/
    /*************************************************************************************/
    QFile dialogFilePadroes("C:/Luan/UNOESC/IA II/Rede_Neural_Alfabeto-2014-06-03/Rede Neural Alfabeto/padroes.txt");
      if (!dialogFilePadroes.open(QIODevice::ReadOnly | QIODevice::Text))
          std::cout << "Não foi possível abrir o Arquivo de Padrões " << std::endl;

    QFile dialogFileEsperados("C:/Luan/UNOESC/IA II/Rede_Neural_Alfabeto-2014-06-03/Rede Neural Alfabeto/esperados.txt");
      if (!dialogFileEsperados.open(QIODevice::ReadOnly | QIODevice::Text))
          std::cout << "Não foi possível abrir o Arquivo de Padrões " << std::endl;

    int indicePadrao = 0;
    /**** Os arquivos de padroes e resultados devem ter a mesma quantidade de linhas ****/
    while ((!dialogFilePadroes.atEnd()) && (!dialogFileEsperados.atEnd())) {
          QByteArray linePadroes = dialogFilePadroes.readLine();
          const char * valoresPadroes = linePadroes.constData();
          QByteArray lineValoresEsperados = dialogFileEsperados.readLine();
          const char * valoresEsperados = lineValoresEsperados.constData();
          Padrao dialogPadrao(valoresPadroes,valoresEsperados);
          padroes.insert(indicePadrao,dialogPadrao);
    }
    /*************************************************************************************/

    /*************************************************************************************/
    /******** Realiza a conexão entre o evento de click do botão com o signal ************/
    /*************************************************************************************/
    for(int i=0;i<entrada.size();i++){
        for(int j=0;j<entrada[i].size();j++){
            connect(entrada[i][j],SIGNAL(sClick(bool,int,int)),this,SLOT(clickBotao(bool,int,int)));
            entrada[i][j]->setStyleSheet("background-color:white;");
        }
    }

    connect(buttonTreinarRede, SIGNAL(clicked()),this,SLOT(treinaRede()));
    connect(buttonReconhecerPadrao,SIGNAL(clicked()),this,SLOT(reconheceEntrada()));
    connect(buttonEntradaDefinida,SIGNAL(clicked()),this,SLOT(entradaDefinida()));

    /*************************************************************************************/

}

Interface::~Interface() {

}

void Interface::clickBotao(bool status, int i, int j){
    if (status){
        entrada[i][j]->setStyleSheet("background-color:black;");
        entrada[i][j]->setStatus(false);
    } else {
        entrada[i][j]->setStyleSheet("background-color:white;");
        entrada[i][j]->setStatus(true);
    }
}

void Interface::treinaRede(){
    /*************************************************************************************/
    /*********** Cria Rede Neural com base nos parametros da interface grafica ***********/
    /*************************************************************************************/

    xAxis.clear();
    yAxis.clear();

    qtdEpocas = lineQtdMaximoEpocas->text().toInt();
    erroMaximo = lineErroMaximo->text().toDouble();
    taxaAprendizado = lineTaxaDeAprendizado->text().toDouble();

    //std::cerr << qtdEpocas << " " << erroMaximo << " " << taxaAprendizado << std::endl;

    rede = NULL;
    rede = new RedeNeural(padroes,qtdEpocas,erroMaximo,taxaAprendizado);

    connect(rede,SIGNAL(atualizaLCDEpocas(int)),lcdEpocas,SLOT(display(int)));
    connect(rede,SIGNAL(atualizaLCDErro(double)),lcdErroMedio,SLOT(display(double)));
    connect(rede,SIGNAL(fimDeEpoca(double,double)),this,SLOT(atualizaGrafico(double,double)));

    rede->treinarRede();
}

void Interface::reconheceEntrada(){
    QList <double> reconhecer;
    int indice = 0;
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++) {
            double dialog = 0;
            if(!entrada[i][j]->getStatus())
                dialog = 1;
            else
                dialog = 0;
            reconhecer.insert(indice,dialog);
            //std::cout << reconhecer[indice] << std::endl;
            indice++;
        }
    }

    QString tmp = rede->reconhecer(reconhecer);

    this->resultadoRedeNeural->setText(tmp);

}

void Interface::entradaDefinida() {
    char * alfabetoMauisculo = "0987654321ZYXWVUTSRQPONMLKJIHGFEDCBA";
    char * alfabetoMinusculo = "0987654321zyxwvutsrqponmlkjihgfedcba";
    QByteArray dialogString = this->lineEntradaDefinida->text().toLatin1();
    char * dialogChar = dialogString.data();
    int indice = 0;
    for(int i=0;i<36;i++){
        if((dialogChar[0] == alfabetoMauisculo[i]) ||(dialogChar[0] == alfabetoMinusculo[i])){
            indice = i;
            break;
        }
    }

    QList <double> dialog = padroes[indice].valores;
    int indiceEntradas = 0;
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++) {
            if(dialog[indiceEntradas] == 0){
                entrada[i][j]->setStatus(false);
                entrada[i][j]->clicked();
            } else {
                entrada[i][j]->setStatus(true);
                entrada[i][j]->clicked();
            }
            indiceEntradas++;
        }
    }

}

void Interface::atualizaGrafico(double x, double y) {
    xAxis << x;
    yAxis << y;
    customPlot->graph(0)->setData(xAxis, yAxis);
    customPlot->xAxis->setLabel("Época");
    customPlot->yAxis->setLabel("Erro Médio");
    customPlot->yAxis->setRange(0, 2);
    customPlot->xAxis->setRange(0, xAxis.size());
    customPlot->replot();
}
