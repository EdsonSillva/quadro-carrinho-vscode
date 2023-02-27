/*
    Metodos da classe BoxDdosAcao para controle das ações entre arduino e Nextion Screen

    Data: 27/05/18
    Autor: Edson Silva

*/

#include "BoxDadosAcao.h"


BoxDadosAcao::BoxDadosAcao() { }

BoxDadosAcao::~BoxDadosAcao() { }


void BoxDadosAcao::setCodeAcao(byte CodeAcao) {
    _CodeAcao = CodeAcao;
}

void BoxDadosAcao::setRGBB(byte R, byte G, byte B, byte Brilho) {
    _R = R;
    _G = G;
    _B = B;
    _Brilho = Brilho;
}

void BoxDadosAcao::setCodeAcaoRGBB(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {
    setCodeAcao(CodeAcao);
    setRGBB(R, G, B, Brilho);
}

String BoxDadosAcao::gerarChaveAcao() {
    _ChaveAcaoAnterior = _ChaveAcaoAtual;
    _ChaveAcaoAtual = ((String)(String(_CodeAcao) + String(_R) + String(_G) + String(_B) + String(_Brilho)));
}

String BoxDadosAcao::getChaveAcao() {
    return _ChaveAcaoAtual;
}

String BoxDadosAcao::getChaveAcaoAnterior() {
    return _ChaveAcaoAnterior;
}

byte BoxDadosAcao::getCodeAcao() {
    return _CodeAcao;
}

byte BoxDadosAcao::getIDAcaoMsg() {
    return _IDAcaoMsg;
}

bool BoxDadosAcao::chaveAcaoAnteriorAtualIgual() {
    return _ChaveAcaoAnterior == _ChaveAcaoAtual ?  true : 
                                                    false;
}

bool BoxDadosAcao::chaveAcaoAtualIsMsg() {
    return _CodeAcao == _IDAcaoMsg ?    true : 
                                        false;
}

byte BoxDadosAcao::getR() {
    return _R;
}

byte BoxDadosAcao::getG() {
    return _G;
}

byte BoxDadosAcao::getB() {
    return _B;
}

byte BoxDadosAcao::getBrilho() {
    return _Brilho;
}
