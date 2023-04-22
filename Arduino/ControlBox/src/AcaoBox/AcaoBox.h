

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

#ifndef __ENUMSCREEN_H__
#include "../enum/enumScreen.h"
#endif

// #ifndef __ENUMBOXTEMATICO_H__
// #include "../enum/enumBoxTematico.h"
// #endif

// #ifndef __ENUMPOSICAOBOX_H__
// #include "../enum/enumPosicaoBox.h"
// #endif


/***********************************************
 * Declaração das variáveis Globais de controle
 ***********************************************/

// Porta default sendo usada para o Box e Vitrine
//***********************************************
#define   _pin_Led_         13
#ifndef _pin_Controle_
#define   _pin_Controle_    12
#endif

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
#define DeslocamentoColuna  16

class AcaoBox : public MascaraLetra
{
private:

    int                 _qtdColunas             = qtd_Colunas;
    int                 _qtdLinhas              = qtd_Linhas;
    int                 _qtdBoxes               = qtd_Boxes;
    int                 _startLedVitrine        = Start_Led_Vitrine;
    int                 _qtdLedsVitrine         = qtd_Leds_Vitrine;
    int                 _totalLeds              = Total_Leds;
    byte                _pinLed                 = _pin_Led_;
    byte                _pinoControle           = _pin_Controle_;
    byte                _intensidadeBrilho      = BrightnessDefault;
    int                 _startFadeUp            = 0;
    bool                _emSaudacao             = false;
    cascata_t           _cascata[qtd_Colunas];

    /* Definições do Objeto de controle dos Led */
    Adafruit_NeoPixel   _Leds;
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

    bool acaoAtiva();
    int PosicaoBoxTop(int PosicaoDada);
    int PosicaoBoxBotton(int PosicaoDada);
    int PosicaoBoxLeft(int PosicaoDada);
    int PosicaoBoxRight(int PosicaoDada);
    int PosicaoBox(int PosicaoDada, eBoxPosicao PosicaoSolicitada);
    int PosicaoBoxCell(int Linha, int Coluna);
    int PosicaoBoxCellInvertido(int Linha, int Coluna);
    void AcendeOuApagaLeds(uint8_t r, uint8_t g, uint8_t b);
    // void MontaMapaBoxTematico(eBoxTematico Tema);

    void showBox(byte Linha, byte Coluna, boxRGB_t RGB);


public:

    AcaoBox();
    AcaoBox(byte pinoControle);
    AcaoBox(byte pinoDados, byte pinoControle);
    ~AcaoBox();

    void inicializarCascata();

    cascata_t *getItemCascata(byte item);
    byte size_Cascata();

    void iniciarLeds(int IntensidadeBrilho);
    void setBrilho(uint8_t Intensidade);
    void iniciarMapaBox();
    void showSaudacaoBox(BoxDadosAcao *DadosAcao, byte LuzFundo, int Aguarda = 2000);
    void setCorBoxFade(int Inicio, int R, int G, int B);
    void setCorLedsRGBBB(byte Start, byte End, BoxDadosAcao *DadosAcao);
    void inline showLeds(int Wait);
    void vitrineLedsRGBB(BoxDadosAcao *DadosAcao);
    void boxLedsRGBB(BoxDadosAcao *DadosAcao);
    void boxAcaoXadrezFade(bool IniciarImpar, BoxDadosAcao *DadosAcao, int PercentualRecebido);
    void boxAcaoColuna(bool IniciarImpar, BoxDadosAcao *DadosAcao);
    void boxAcaoLinha(bool IniciarImpar, BoxDadosAcao *DadosAcao);
    // void boxAcaoTematico(eBoxTematico Tema, BoxDadosAcao *DadosAcao);

    void boxAcaoTematicoByItem(BoxDadosAcao *DadosAcao, byte Boxes[], byte sizeBoxes);

    // void boxAcaoCascata(BoxDadosAcao *DadosAcao, cascata_t cascata[], uint8_t coluna);
    void boxAcaoCascata(BoxDadosAcao *DadosAcao, cascata_t *itemCascata, byte luzFundo);
    
    void showMapaBoxes(BoxDadosAcao *DadosAcao, byte LuzFundo);
    void todosLedsAcesos(uint8_t r, uint8_t g, uint8_t b);
    void todosLedsApagados();
    void showMsgBox(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow);
    void showMsgBoxDebug(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow);
    void shifEsquerdaMapaBox(byte PrimeiraLinha, byte UltimaLinha, byte QtdeBit);
    
    #pragma region Snake Target

    boxRGB_t getBoxRGB(BoxDadosAcao *DadosAcao, linCol PosicaoBox);
    alvo_t getAlvoBox(BoxDadosAcao *DadosAcao, linCol PosicaoBox);
    eBoxPosicao deslocamentoBox(BoxDadosAcao *DadosAcao, linCol Alvo, linCol PosicaoBox);
    eBoxPosicao deslocamentoBox(BoxDadosAcao *DadosAcao, alvo_t *Alvo, snake_t *snake);
    eBoxPosicao deslocamentoBox(BoxDadosAcao *DadosAcao, alvo_t *Alvo, snake_t *snake, eBoxMovimentoSnake movimento);
    box_t getPosicaoBoxByAlvo(BoxDadosAcao *DadosAcao, box_t *Box, eBoxPosicao DeslocamentoAlvo);
    void showAlvo(BoxDadosAcao *DadosAcao, alvo_t Alvo, boxRGB_t RGB);
    void showCabecaSnake(BoxDadosAcao *DadosAcao, snake_t *Snake);
    void moveSnake(BoxDadosAcao *DadosAcao, snake_t snake);


    #pragma endregion

    // Ação Cobrinha
    /* Montar um arry de 16 posições
       
       fazer um loop ate a primeira posição
       a posição zero fica fora e reseta pa a aluz de fundo
       fazer o loop a primeira posição até o final
       colocar um controle de arrasto e acresentar um arrasto a mais quando a 
       cobrinha bater no ponto aleatório e se o ponto estiver com cor diferente da 
       cobrinha mudar para a cor da cobrinha com a cor do ponto  




    */

};

#endif  // __ACAOBOX_H__
