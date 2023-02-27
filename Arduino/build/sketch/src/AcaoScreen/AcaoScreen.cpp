#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\src\\AcaoScreen\\AcaoScreen.cpp"


#include "AcaoScreen.h"

AcaoScreen::AcaoScreen(byte PinoControle): _pinoControle(PinoControle) { }
AcaoScreen::~AcaoScreen() { }


/* 
    @brief Verifica se o pino de controle está em HIGH or LOW. Quando
          estiver em HIGH é porque existe uma ação para ser executada
    
    @return True quado o pino estiver em HIGH, False quando o pino estiver em LOW
*/
bool inline AcaoScreen::acaoAtiva(){
    return digitalRead(_pinoControle);
}
    
void AcaoScreen::setLeds(BoxDadosAcao *DadosAcao) {

    if(!DadosAcao->chaveAcaoAnteriorAtualIgual()) {
        _box.boxLedsRGBB(DadosAcao);
    }

}

void AcaoScreen::resetAcao(BoxDadosAcao *DadosAcao) {
   setLeds(DadosAcao);
}

void AcaoScreen::ledsAcesos(BoxDadosAcao *DadosAcao) {

    bool EmAcao  = true;

    setLeds(DadosAcao);
    while(EmAcao) {                     // Aguarda o cancelamento da ação 
        delayMicroseconds(50000);       // Aguarda 0,5 segundos antes de ler se a ação foi cancelada (otimizando energia)
        EmAcao = acaoAtiva();
    }
}

void AcaoScreen::ledsXadrezFade(BoxDadosAcao *DadosAcao) {

    if(!DadosAcao->chaveAcaoAnteriorAtualIgual()) {

        bool  IniciarImpar = true;
        int   Percentual   = 100;
        int   Intervalo    = 10;

        _tmpWaitRotina = 11000;

        while(acaoAtiva()) {                     // Aguarda o cancelamento da ação 

            if(_tmpWaitRotina > 5000) {
                
                _box.boxAcaoXadrezFade(IniciarImpar, DadosAcao, Percentual);

                Percentual -= Intervalo;

                if((Percentual < 0) || (Percentual > 100)) {
                    Intervalo *=-1;
                    Percentual -= Intervalo;
                }

                _tmpWaitRotina = 0;

            } else { _tmpWaitRotina++; delayMicroseconds(100); }

        }

    }

}

void AcaoScreen::mensagem(BoxDadosAcao *DadosAcao, byte LinhaShow) {

    char Msg[50]  = {0};
    byte QtdeChar = 0;

    _eeprom.getTextoOnMemory(Msg, &QtdeChar);

    while(acaoAtiva()) {
        _box.showMsgBox(Msg, QtdeChar - 1, DadosAcao, LinhaShow);
    }
    
}

void AcaoScreen::ledsAcaoLinhaColuna(BoxDadosAcao *DadosAcao, eAcao Acao = eAcao::acaoLinha) {

    if(!DadosAcao->chaveAcaoAnteriorAtualIgual()) { 

        bool IniciarImpar = true;
        _tmpWaitRotina = 11000;

        while(acaoAtiva()) {

            if(_tmpWaitRotina > 10000) {
            
                switch (Acao)
                {
                case eAcao::acaoLinha:
                    _box.boxAcaoLinha(IniciarImpar, DadosAcao);
                    break;
                case eAcao::acaoColuna:
                    _box.boxAcaoColuna(IniciarImpar, DadosAcao);
                    break;
                }

                IniciarImpar = !IniciarImpar;
                _tmpWaitRotina = 0;
            
            } else {
                 _tmpWaitRotina++; delayMicroseconds(100);
            }

        }

    }
}

/* @deprecated Antigo*/
void AcaoScreen::ledsShowBoxFixoAcao(BoxDadosAcao *DadosAcao, eBoxTematico Tema) {

    _box.iniciarMapaBox();
    _box.boxAcaoTematico(Tema, DadosAcao);
    while(acaoAtiva());

}

void AcaoScreen::ledsTematico(BoxDadosAcao *DadosAcao, eBoxTematico Tema) {

    _box.iniciarMapaBox();
    _box.boxAcaoTematico(Tema, DadosAcao);
    while(acaoAtiva());

}

#pragma region Rotinas para a ação Cascata

void AcaoScreen::ledsAcaoCascata(BoxDadosAcao *DadosAcao) {

    if(!DadosAcao->chaveAcaoAnteriorAtualIgual()) {

        _tmpWaitRotina                     = 11000;
        uint8_t sizeCascata               = 15;
        uint8_t colunasFeitas             = 0;
        cascata_t cascata[sizeCascata];

        // Mantem a vitrine acesa
        _box.vitrineLedsRGBB(DadosAcao);

        while(acaoAtiva()) {

            if(_tmpWaitRotina > 10000){

                inicializaCascata(cascata, sizeCascata);
                colunasFeitas = 0;

                while(acaoAtiva() && colunasFeitas < 14) {
            
                    for(uint8_t coluna = 0; coluna <= 14 && acaoAtiva(); coluna++) {

                        if(cascata[coluna].Linha > 0 && (!cascata[coluna].Finalizado)) {
                           _box.boxAcaoCascata(DadosAcao, cascata, coluna);
                        }

                        if((cascata[coluna].Linha - cascata[coluna].Arrasto) > 14) {
                            colunasFeitas++;
                            cascata[coluna].Finalizado = true;
                        }

                        cascata[coluna].Linha++;
                    }
                }
            
                _tmpWaitRotina = 0;
            
            } else { _tmpWaitRotina++; delayMicroseconds(100);}

        }

    }

}

void AcaoScreen::inicializaCascata(cascata_t cascata[], uint8_t SizeCascata) {

//  uint8_t qtdColunas            = SizeCascata;
    uint8_t colunas[SizeCascata]   = {0};

    randomUnico(colunas, SizeCascata);

    for(uint8_t i = 0; i < (SizeCascata - 1); i++){

        cascata[i].Coluna       = colunas[i];
        cascata[i].Linha        = random(-3, 2);
        cascata[i].Arrasto      = random(3,  6);
        cascata[i].Percentual   = 100 / cascata[i].Arrasto;      // percentual usado para fazer o arrasto
        cascata[i].Finalizado   = false;

        delay(250);

    }
}

void AcaoScreen::randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer) {

    bool      valorExiste   = false;
    uint8_t   coluna        = 0;
    uint8_t   minimo        = 1;
    uint8_t   maximo        = SizeBuffer + 1;
    uint8_t   valor         = 0;

    randomSeed(random());

    while(coluna < SizeBuffer){

        valor = random(minimo, maximo);

        valorExiste = false;
        for(int i = 0; i <= SizeBuffer; i++ ){
            if(valor == bufferValores[i]){
                valorExiste = true;
                break;
            }
        }
        if(!valorExiste){
            bufferValores[coluna] = valor;
            coluna++;
        }
    }
}

#pragma endregion





