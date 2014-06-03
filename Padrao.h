#ifndef PADRAO_H
#define PADRAO_H

#include <QList>

class Padrao {

public:
    QList <double> valores;
    QList <double> resultados;



    Padrao(const char * _valores, const char * _resultados);
    ~Padrao();

};

#endif // PADRAO_H
