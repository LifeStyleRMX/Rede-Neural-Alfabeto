#include "Botao.h"

Botao::Botao(bool status, int i, int j) {
    this->status = status;
    this->i = i;
    this->j = j;
    connect(this,SIGNAL(clicked()),this,SLOT(emiteDados()));
}

Botao::~Botao(){

}

void Botao::setStatus(bool estado) {
    this->status = estado;
}

bool Botao::getStatus() {
    return status;
}

void Botao::emiteDados(){
    sClick(this->status,this->i,this->j);
}

