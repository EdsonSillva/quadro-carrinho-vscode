
#include "BoxCar.h"

BoxCar::BoxCar() { }
BoxCar::~BoxCar() { }

void BoxCar::iniciarBoxCar(int BrilhoInicial = 50) {

    pinMode(_pinoControle, INPUT);
    acaoBox.iniciarLeds(BrilhoInicial),         delay(100);         // inicializar os leds da fita com o brilho em default em 50
    eeprom.inicializar(),                       delay(1000);        // Inicializar Wire para a comunicação com a EEPROM

}

void BoxCar::showSaudacao(int Duracao = 10000) {

    acaoBox.todosLedsAcesos(255, 255, 255),     delay(500);         // Acender todos os Leds do quadro
    dadosAcao.setRGBGamma(0, 0, 255);                               // Indica a cor Azul para a imagem da saudação
    acaoBox.showSaudacaoBox(&dadosAcao, 20, Duracao);               // Mostra saudação e aguarda o tempo da Duração

}

bool BoxCar::acaoSolicitada() {
    return acaoScreen.acaoAtiva();
}

/*
    @brief Metodo para identificar e executar uma ação no quadro de carrinho.
*/
void BoxCar::identificarExecutarAcao() {

    eeprom.getDadosOnMemory(&dadosAcao);

    /* Busca o gamma correlacionado a cada cor do RGB e guarda dentro do objeto */
    dadosAcao.setRGBGamma(pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getR()]),
                          pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getG()]),
                          pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getB()]));

    executarAcao((eAcaoBox)dadosAcao.getCodeAcao());

    // Efetuar o reset no quadro de carrinhos após a ação
    executarAcao(eAcaoBox::semAcaoBox);

}

void BoxCar::executarAcao(eAcaoBox CodigoAcao) {

    switch (CodigoAcao)
    {

    case eAcaoBox::semAcaoBox:

        acaoBox.todosLedsApagados();
        break;

    case eAcaoBox::acaoAceso:

        acaoScreen.ledsAcesos(&dadosAcao);
        break;

    case eAcaoBox::acaoXadrez:

        acaoScreen.ledsXadrezFade(&dadosAcao);
        break;

    case eAcaoBox::acaoLinha:

        acaoScreen.ledsAcaoLinhaColuna(&dadosAcao, eAcaoBox::acaoLinha);
        break;

    case eAcaoBox::acaoColuna:

        acaoScreen.ledsAcaoLinhaColuna(&dadosAcao, eAcaoBox::acaoColuna);
        break;

    case eAcaoBox::acaoCascata:

        acaoScreen.ledsAcaoCascata(&dadosAcao);
        break;

    case eAcaoBox::acaoSnake:

        acaoScreen.ledsAcaoSnake(&dadosAcao);
        break;

    case eAcaoBox::acaoMsg:

        acaoScreen.mensagem(&dadosAcao, _Linha_Show_);
        break;

    default:

        // Ações temáticas

        byte sizeBoxes          = dadosAcao.getSizeTemaBat();
        byte Boxes[sizeBoxes];

        byte QtdeItens = eeprom.getTemaOnMemory(Boxes, sizeBoxes);

        acaoScreen.ledsTematicoByItem(&dadosAcao, Boxes, QtdeItens);

        break;

    }

}


