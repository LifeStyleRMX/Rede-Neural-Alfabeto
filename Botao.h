#ifndef BOTAO_H
#define BOTAO_H
#include <QtWidgets/QPushButton>

class Botao : public QPushButton{

    Q_OBJECT

private:
    int i,j;
    bool status;

public:
    Botao(bool status, int i, int j);
    ~Botao();
    void setStatus(bool estado);
    bool getStatus();

public slots:
    void emiteDados();

signals:
    void sClick(bool status, int i, int j);
};

#endif // BOTAO_H
