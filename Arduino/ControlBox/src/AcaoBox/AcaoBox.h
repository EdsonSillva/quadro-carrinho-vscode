

#ifndef __ACAOBOX_H__
#define __ACAOBOX_H__


#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __TYPEDEFBOX_H__
#include "../typedef/typedefBox.h"
#endif

#ifndef __BOXEEPROM_H__
#include <BoxEEPROM.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __BOXBUZZERCAR_H__
#include <BoxBuzzerCar.h>
#endif

#ifndef __MASCARALETRA_H__
#include "../MascaraLetra/MascaraLetra.h"
#endif

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#ifndef __ENUMBOXTEMATICO_H__
#include "../enum/enumBoxTematico.h"
#endif


/***********************************************
 * Declaração das variáveis Globais de controle
 ***********************************************/

// Porta sendo usada para o Box e Vitrine
//****************************************
#define pin_Led             13

// Definições para controle do Box
//*********************************
#define qtd_Colunas         15
#define qtd_Linhas          14
#define qtd_Boxes           qtd_Colunas * qtd_Linhas

// Definições para o controle da Vitrine
//***************************************
#define Start_Led_Vitrine   qtd_Boxes                           // Seta para a posição inicial dos Leds da Vitrine
#define qtd_Leds_Vitrine    20

// Definições para o controle geral
//**********************************
#define Total_Leds          qtd_Boxes + qtd_Leds_Vitrine        // O Valor é 230 (levando em conta 15 colunas, 14 linhas e 20 leds da vitrine)
#define BrightnessDefault   75                                  // Guarda o valor default de Brilho
#define BoxTop              01
#define BoxBottom           02
#define BoxLeft             03
#define BoxRight            04
#define LinhaPosicaoDada    05
#define ColunaPosicaoDada   06

class AcaoBox : public MascaraLetra
{
private:

    BoxDadosAcao acao       = BoxDadosAcao();

    /* Definições do Objeto de controle dos Led */
    Adafruit_NeoPixel _Leds = Adafruit_NeoPixel(
                                Total_Leds, 
                                pin_Led,
                                NEO_GRB + NEO_KHZ800);

    int _StartFadeUp        = 0;

    /*
        @brief Representação de cada box no quadro de carrinho
    */
    word _MapaBox[qtd_Linhas + 1] = {    0b0000000000000000      // Linha 01 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 02 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 03 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 04 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 05 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 06 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 07 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 08 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 09 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 10 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 11 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 12 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 13 do quadro e cada bit representa a coluna
                                        ,0b0000000000000000      // Linha 14 do quadro e cada bit representa a coluna
                                    };

    int PosicaoBoxTop(int PosicaoDada);
    int PosicaoBoxBotton(int PosicaoDada);
    int PosicaoBoxLeft(int PosicaoDada);
    int PosicaoBoxRight(int PosicaoDada);
    int PosicaoBox(int PosicaoDada, int PosicaoSolicitada);
    int PosicaoBoxCell(int Linha, int Coluna);
    int PosicaoBoxCellInvertido(int Linha, int Coluna);
    void AcendeOuApagaLeds(uint8_t r, uint8_t g, uint8_t b);

public:
    AcaoBox();
    ~AcaoBox();
    
    void iniciarLeds(int IntensidadeBrilho);
    void setBrilho(uint8_t Intensidade);
    void iniciarMapaBox();
    void setCorBoxFade(int Inicio, int R, int G, int B);
    void setCorLedsRGBBB(byte Start, byte End, BoxDadosAcao *DadosAcao);
    void inline showLeds(int Wait);
    void vitrineLedsRGBB(BoxDadosAcao *DadosAcao);
    void boxLedsRGBB(BoxDadosAcao *DadosAcao);
    void boxAcaoXadrezFade(bool IniciarImpar, BoxDadosAcao *DadosAcao, int PercentualRecebido);
    void boxAcaoColuna(bool IniciarImpar, BoxDadosAcao *DadosAcao);
    void boxAcaoLinha(bool IniciarImpar, BoxDadosAcao *DadosAcao);
    void boxAcaoTematico(eBoxTematico Tema, BoxDadosAcao *DadosAcao);
    void boxAcaoCascata(BoxDadosAcao *DadosAcao, cascata_t cascata[], uint8_t coluna);
    void showMapaBoxes(BoxDadosAcao *DadosAcao, byte LuzFundo);
    void todosLedsAcesos(uint8_t r, uint8_t g, uint8_t b);
    void todosLedsApagados();
    void showMsgBox(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow);
    void showMsgBoxDebug(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow);
    void shifEsquerdaMapaBox(byte PrimeiraLinha, byte UltimaLinha, byte QtdeBit);

};

#endif  // __ACAOBOX_H__
