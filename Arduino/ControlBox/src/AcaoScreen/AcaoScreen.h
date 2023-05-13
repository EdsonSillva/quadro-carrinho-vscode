/*
 * Gerenciador das Rotinas das Ações recebidas pela tela Nextion
 * Desenvolvido por Edson Silva
 * 
 * Date: 07/07/19
 * Alteração: jul/22
*/

#ifndef __ACAOSCREEN_H__
#define __ACAOSCREEN_H__

#ifndef __TYPEDEFBOX_H__
#include "../typedef/typedefBox.h"
#endif

#ifndef __BOXEEPROM_H__
#include <BoxEEPROM.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __ACAOBOX_H__
#include "../AcaoBox/AcaoBox.h"
#endif

#ifndef __ENUMSCREEN_H__
#include "../enum/enumScreen.h"
#endif

#define     _pin_Controle_              12
#ifdef _CorpoSnake_ 
#define     _CorpoSnakeMax_             _CorpoSnake_ - 2
#else
#define     _CorpoSnakeMax_             10
#endif

class AcaoScreen
{
private:

    byte                    _pinoControle           = _pin_Controle_;
    AcaoBox                 _box                    = AcaoBox();
    BoxEEPROM               _eeprom                 = BoxEEPROM();    // Usando pinagem pré definida
    long                    _tmpWaitRotina          = 0x00;

    void setLeds(BoxDadosAcao *DadosAcao);
    void inicializaCascata();
    void resetCascata();
    void randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer);

public:

    AcaoScreen();                       // Usa o pino de controle default
    AcaoScreen(byte PinoControle);
    ~AcaoScreen();

    bool acaoAtiva();
    void resetAcao(BoxDadosAcao *DadosAcao);
    void ledsAcesos(BoxDadosAcao *DadosAcao);
    void ledsXadrezFade(BoxDadosAcao *DadosAcao);
    void mensagem(BoxDadosAcao *DadosAcao, byte LinhaShow);
    void ledsAcaoLinhaColuna(BoxDadosAcao *DadosAcao, eAcaoBox Acao);
    void ledsTematicoByItem(BoxDadosAcao *DadosAcao, byte Boxes[], byte sizeBoxes);
    void ledsAcaoCascata(BoxDadosAcao *DadosAcao);

    void inicializarSnake(BoxDadosAcao *DadosAcao, snake_t *snake);
    void ledsAcaoSnake(BoxDadosAcao *DadosAcao);
    void descerPosicaoSnake(snake_t *snake);

    box_t buscarNovaPosicao(BoxDadosAcao *DadosAcao, snake_t *snake, alvo_t *alvo);
    alvo_t buscarNovoAlvo(BoxDadosAcao *DadosAcao, snake_t *snake);
    byte procurarCorpoSnake(box_t *Box, snake_t *snake);
    void entrarNaToca(BoxDadosAcao *DadosAcao, snake_t *snake);

};

#endif  // __ACAOSCREEN_H__

