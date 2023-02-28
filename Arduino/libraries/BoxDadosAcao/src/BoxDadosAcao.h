/*
    Classe para controle das ações entre arduino e Nextion Screen

    Data: 27/05/18
    Autor: Edson Silva

*/

#ifndef __BOXDADOSACAO_H__
#define __BOXDADOSACAO_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define   _IDAcaoMsg_             64            // ID Ação de mensagem. Mudar este código se houver mudanças no id de mensagem na tela Nextion Screen

/*
    Classe de controle dos metodos de tratamento das ações e dados selecionados na tela Nextion.
*/
class BoxDadosAcao
{
private:

    bool    _Executando             = false;
    byte    _IDAcaoMsg              = _IDAcaoMsg_;
    byte    _CodeAcao               = 0;
    byte    _R                      = 0;
    byte    _G                      = 0;
    byte    _B                      = 0;
    byte    _GammaR                 = 0;
    byte    _GammaG                 = 0;
    byte    _GammaB                 = 0;
    byte    _Brilho                 = 0;
    String  _ChaveAcaoAtual         = "";
    String  _ChaveAcaoAnterior      = "";

public:
    BoxDadosAcao();
    ~BoxDadosAcao();

    void setCodeAcao(byte CodeAcao);
    void setExecutando(bool valor);
    bool getExecutando();
    void limpaDados();
    void setRGBB(byte R, byte G, byte B, byte Brilho);
    void setRGBGamma(byte GammaR, byte GammaG, byte GammaB);
    void setCodeAcaoRGBB(byte CodeAcao, byte R, byte G, byte B, byte Brilho);
    String gerarChaveAcao();
    String getChaveAcao();
    String getChaveAcaoAnterior();
    byte getR();
    byte getG();
    byte getB();
    byte getGammaR();
    byte getGammaG();
    byte getGammaB();
    byte getBrilho();
    byte getCodeAcao();
    byte getIDAcaoMsg();
    bool chaveAcaoAnteriorAtualIgual();
    bool chaveAcaoAtualIsMsg();

};

#endif  // __BOXDADOSACAO_H__


