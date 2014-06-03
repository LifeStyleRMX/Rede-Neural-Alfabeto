#include "Interface.h"
#include <QtGui>
#include <QApplication>

int main ( int argc, char * argv[]) {
    QApplication app(argc, argv);

    Interface * redeNeural = new Interface();

    redeNeural->show();

    return app.exec();
}
