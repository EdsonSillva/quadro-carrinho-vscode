
#include "BoxCar.h"

#ifndef __ENUMACAO_H__
#include "src/enum/enumAcao.h"
#endif


BoxCar::BoxCar() { }
BoxCar::~BoxCar() { }

void BoxCar::iniciarBoxCar(int BrilhoInicial = 50) {

    pinMode(_pinoControle, INPUT);
    acaoBox.iniciarLeds(BrilhoInicial),         delay(100);         // inicializar os leds da fita com o brilho em default em 50
    eeprom.inicializar(),                       delay(1000);        // Inicializar Wire para a comunicação com a EEPROM

}

void BoxCar::showSaudacao() {

    acaoBox.todosLedsAcesos(255, 255, 255),     delay(500);         // Acender todos os Leds do quadro
    dadosAcao.setRGBGamma(0, 0, 255);                               // Indica a cor Azul para a imagem da saudação
    acaoBox.showSaudacaoBox(&dadosAcao, 20, 10000);                 // Mostra saudação e aguarda 10 segunbdos

}

bool BoxCar::acaoSolicitada() {
    return acaoScreen.acaoAtiva();
}

/*
    @brief Metodo para identificar e executar uma ação no quadro de carrinho.
*/
void BoxCar::identificarExecutarAcao() {

    eeprom.getDadosOnMemory(&dadosAcao);

    Serial.print(F("\nCodeAcao: ")), Serial.print(dadosAcao.getCodeAcao());
    Serial.print(F(" R: [")), Serial.print(dadosAcao.getR());
    Serial.print(F("] G: [")), Serial.print(dadosAcao.getG());
    Serial.print(F("] B: [")), Serial.print(dadosAcao.getB());
    Serial.print(F("] Brilho: ")), Serial.print(dadosAcao.getBrilho());

    /* Busca o gamma correlacionado a cada cor do RGB e guarda dentro do objeto */
    dadosAcao.setRGBGamma(pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getR()]),
                          pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getG()]),
                          pgm_read_byte(&_NeoPixelGammaTable[dadosAcao.getB()]));


    Serial.print(F(" - Gama: "));
    Serial.print(F(" R: [")), Serial.print(dadosAcao.getGammaR());
    Serial.print(F("] G: [")), Serial.print(dadosAcao.getGammaG());
    Serial.print(F("] B: [")), Serial.print(dadosAcao.getGammaB());
    Serial.print(F("] "));

    executarAcao((eAcao)dadosAcao.getCodeAcao());

    // Efetuar o reset no quadro de carrinhos após a ação
    executarAcao(eAcao::semAcao);

}

void BoxCar::executarAcao(eAcao CodigoAcao) {

    switch (CodigoAcao)
    {
    case eAcao::semAcao:

        acaoBox.todosLedsApagados();
        break;

    case eAcao::acaoAceso:

        acaoScreen.ledsAcesos(&dadosAcao);
        break;

    case eAcao::acaoXadrez:

        acaoScreen.ledsXadrezFade(&dadosAcao);
        break;

    case eAcao::acaoLinha:

        acaoScreen.ledsAcaoLinhaColuna(&dadosAcao, eAcao::acaoLinha);
        break;

    case eAcao::acaoColuna:

        acaoScreen.ledsAcaoLinhaColuna(&dadosAcao, eAcao::acaoColuna);
        break;

    case eAcao::acaoCascata:

        acaoScreen.ledsAcaoCascata(&dadosAcao);
        break;

    case eAcao::acaoMsg:

        acaoScreen.mensagem(&dadosAcao, _Linha_Show_);
        break;




    case eAcao::acaoBatman:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBatman);
        break;

    case eAcao::acaoStarWar:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxStarWars);
        break;

    case eAcao::acaoVelozFurioso:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxVelozesFurosos);
        break;

    case eAcao::acaoMoto:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMotos);
        break;

    case eAcao::acaoPorche:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxPorche);
        break;

    case eAcao::acaoFerrari:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFerrari);
        break;

    case eAcao::acaoPagani:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxPagani);
        break;

    case eAcao::acaoMCLaren:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMacLaren);
        break;

    case eAcao::acaoChevrolet:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxChevolet);
        break;

    case eAcao::acaoAstomMart:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAstonMartin);
        break;

    case eAcao::acaoJaguar:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxJaguar);
        break;

    case eAcao::acaoAudi:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAudi);
        break;

    case eAcao::acaoBMW:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBMW);
        break;

    case eAcao::acaoMercedes:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMercedes);
        break;

    case eAcao::acaoTesla:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxTesla);
        break;

    case eAcao::acaoLamborghini:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxLamborghini);
        break;

    case eAcao::acaoNissan:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxNissan);
        break;

    case eAcao::acaoDodge:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxDodge);
        break;

    case eAcao::acaoBuick:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBuick);
        break;

    case eAcao::acaoVolks:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxVolks);
        break;

    case eAcao::acaoFord:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFord);
        break;

    case eAcao::acaoFiat:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFiat);
        break;

    case eAcao::acaoCadillac:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxCadiLac);
        break;

    case eAcao::acaoHonda:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxHonda);
        break;

    case eAcao::acaoAcura:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAcura);
        break;

    case eAcao::acaoBentley:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBentley);
        break;

    case eAcao::acaoMazda:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMazda);
        break;

    case eAcao::acaoBugatti:

        acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBugatti);
        break;

    default:
        break;
    }

}


