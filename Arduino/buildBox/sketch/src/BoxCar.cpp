#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\src\\BoxCar.cpp"

#include "BoxCar.h"

#ifndef __ENUMACAO_H__
#include "src/enum/enumAcao.h"
#endif


BoxCar::BoxCar() { }

BoxCar::~BoxCar() { }

void BoxCar::iniciarBoxCar() {

    pinMode(_pinoControle, INPUT);
    acaoBox.iniciarLeds(50),                    delay(100);         // inicializar os leds da fita com o brilho em default em 50
    acaoBox.todosLedsAcesos(255, 255, 255),     delay(100);         // Acender todos os Leds do quadro
    eeprom.inicializar(),                       delay(1000);        // Inicializar Wire para a comunicação com a EEPROM

}

void BoxCar::executarAcao() {

    eeprom.getDadosOnMemory(&dadosAcao);

    eAcao CodigoAcao = (eAcao)dadosAcao.getCodeAcao();

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

