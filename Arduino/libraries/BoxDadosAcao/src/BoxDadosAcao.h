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

#ifndef EEPROM_h
#include <EEPROM.h>
#endif

#ifndef __BOXENUMACAO_H__
#include "BoxEnumAcao.h"
#endif

#define     _IDAcaoMsg_                     67              // ID Ação de mensagem. Mudar este código se houver mudanças no id de mensagem na tela Nextion Screen
#define     _BrilhoDefault_                 75              // Padrão para brilho do led
#define     _AddessInicioEEPROMIno_          1              // Endereço inicial da EEPROM interna do Arduino
#define     _sizeEEPROMIno_               1024              // Tamanho da EEPROM interna do Arduino
#define     _sizeBat_                       50              // Tamanho da tabela de alocação dos Boxes
#define     _sizeTemaBat_                   20              // Tamanho de cada tema na alocação dos Boxes


/*
    Classe de controle dos metodos de tratamento das ações e dados selecionados na tela Nextion.
*/
class BoxDadosAcao
{
private:

    bool    _Executando                 = false;
    byte    _IDAcaoMsg                  = _IDAcaoMsg_;
    byte    _CodeAcao                   = 0;
    byte    _R                          = 0;
    byte    _G                          = 0;
    byte    _B                          = 0;
    byte    _GammaR                     = 0;
    byte    _GammaG                     = 0;
    byte    _GammaB                     = 0;
    byte    _Brilho                     = _BrilhoDefault_;

    String  _ChaveAcaoAtual             = "";
    String  _ChaveAcaoAnterior          = "";

    // Controle dos acessos a memória EEPROM do Arduino
    int     _addressInicioEEPROMIno     = _AddessInicioEEPROMIno_;
    int     _sizeEEPROMIno              = _sizeEEPROMIno_;

    int     _batAddressIni              = _addressInicioEEPROMIno;          // Endereço inicial da Bat (Box Alocation Table)
    byte    _sizeBat                    = _sizeBat_;                        // Tamanho da Bat (Box Alocation Table)
    int     _addressIniBoxes            = _batAddressIni + _sizeBat;        // Endereço inicial da área de dados dos Boxes (Cada byte indica Linha e Coluna).
    byte    _sizeTemaBat                = _sizeTemaBat_;                    // Tamanho de cada segmento de dados para cada tema

     byte getPosicaoTemaBatByDado(byte const *DadoPesquisa);
    // int getDadoTemaBat(int Inicio, int Fim, byte DadoPesquisa);


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
    void setBrilho(byte Brilho);
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

    int posicaoInicialDadoTema(byte PosicaoTemaBat);
    int posicaoFinalDadoTema(byte PosicaoTemaBat);
    void setDadoEEPROMIno(int Inicio, int Fim, byte Dado = 0x00);
    void inicializaEEPROMIno();
    void inicializaTemaBat();
    void limpaDadosTemaBat(byte PosicaoTema);
    byte getSizeTemaBat();
    byte getPosicaoTemaBat(byte CodigoTema);
    byte getPosicaoLivreTemaBat();
    byte setPosicaoLivreTemaBat(byte CodigoTema);
    byte lerDadosTemaBat(byte Boxes[], byte PosicaoTema);

    byte converteLinhaColuna(byte Linha, byte Coluna);
    byte numLinha(byte LinhaColuna);
    byte numColuna(byte LinhaColuna);

};

#endif  // __BOXDADOSACAO_H__


