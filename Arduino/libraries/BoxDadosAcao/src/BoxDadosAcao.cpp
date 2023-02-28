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

void BoxDadosAcao::setExecutando(bool valor){
    _Executando = valor;
}

bool BoxDadosAcao::getExecutando() {
    return _Executando;
}

void BoxDadosAcao::limpaDados() {
    _R      = 0, _G      = 0, _B      = 0, _Brilho = 0;
    _GammaR = 0, _GammaG = 0, _GammaB = 0;
}

void BoxDadosAcao::setRGBB(byte R, byte G, byte B, byte Brilho) {
    _R = R;
    _G = G;
    _B = B;
    _Brilho = Brilho;
}

void BoxDadosAcao::setRGBGamma(byte GammaR, byte GammaG, byte GammaB) {
    _GammaR = GammaR;
    _GammaG = GammaG;
    _GammaB = GammaB;
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

byte BoxDadosAcao::getGammaR() {
    return _GammaR;
}

byte BoxDadosAcao::getGammaG() {
    return _GammaG;
}

byte BoxDadosAcao::getGammaB() {
    return _GammaB;
}

byte BoxDadosAcao::getBrilho() {
    return _Brilho;
}

