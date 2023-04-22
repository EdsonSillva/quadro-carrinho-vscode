
#include "BoxCar.h"

// #ifndef __ENUMACAO_H__
// #include "src/enum/enumAcao.h"
// #endif


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

    executarAcao((eAcaoBox)dadosAcao.getCodeAcao());

    // Efetuar o reset no quadro de carrinhos após a ação
    executarAcao(eAcaoBox::semAcao);

}

void BoxCar::executarAcao(eAcaoBox CodigoAcao) {

    switch (CodigoAcao)
    {

    case 154:

        acaoScreen.ledsHunter(&dadosAcao);
        break;

    case eAcaoBox::semAcao:

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

    case eAcaoBox::acaoMsg:

        acaoScreen.mensagem(&dadosAcao, _Linha_Show_);
        break;

    default:

        //acaoScreen.ledsTematicoByItem();

        byte sizeBoxes          = dadosAcao.getSizeTemaBat();
        byte Boxes[sizeBoxes];

        byte QtdeItens = eeprom.getTemaOnMemory(Boxes, sizeBoxes);

        acaoScreen.ledsTematicoByItem(&dadosAcao, Boxes, QtdeItens);

        break;

    // case eAcaoBox::acaoBatman:

        
    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBatman);
    //     break;

    // case eAcaoBox::acaoStarWar:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxStarWars);
    //     break;

    // case eAcaoBox::acaoVelozFurioso:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxVelozesFurosos);
    //     break;

    // case eAcaoBox::acaoMoto:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMotos);
    //     break;

    // case eAcaoBox::acaoPorche:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxPorche);
    //     break;

    // case eAcaoBox::acaoFerrari:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFerrari);
    //     break;

    // case eAcaoBox::acaoPagani:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxPagani);
    //     break;

    // case eAcaoBox::acaoMCLaren:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMacLaren);
    //     break;

    // case eAcaoBox::acaoChevrolet:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxChevolet);
    //     break;

    // case eAcaoBox::acaoAstomMart:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAstonMartin);
    //     break;

    // case eAcaoBox::acaoJaguar:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxJaguar);
    //     break;

    // case eAcaoBox::acaoAudi:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAudi);
    //     break;

    // case eAcaoBox::acaoBMW:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBMW);
    //     break;

    // case eAcaoBox::acaoMercedes:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMercedes);
    //     break;

    // case eAcaoBox::acaoTesla:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxTesla);
    //     break;

    // case eAcaoBox::acaoLamborghini:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxLamborghini);
    //     break;

    // case eAcaoBox::acaoNissan:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxNissan);
    //     break;

    // case eAcaoBox::acaoDodge:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxDodge);
    //     break;

    // case eAcaoBox::acaoBuick:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBuick);
    //     break;

    // case eAcaoBox::acaoVolks:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxVolks);
    //     break;

    // case eAcaoBox::acaoFord:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFord);
    //     break;

    // case eAcaoBox::acaoFiat:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxFiat);
    //     break;

    // case eAcaoBox::acaoCadillac:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxCadiLac);
    //     break;

    // case eAcaoBox::acaoHonda:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxHonda);
    //     break;

    // case eAcaoBox::acaoAcura:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxAcura);
    //     break;

    // case eAcaoBox::acaoBentley:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBentley);
    //     break;

    // case eAcaoBox::acaoMazda:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxMazda);
    //     break;

    // case eAcaoBox::acaoBugatti:

    //     acaoScreen.ledsTematico(&dadosAcao, eBoxTematico::boxBugatti);
    //     break;

    // default:
    //     break;
    }

}


