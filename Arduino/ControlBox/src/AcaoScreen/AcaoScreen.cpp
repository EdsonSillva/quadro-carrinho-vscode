

#include "AcaoScreen.h"

AcaoScreen::AcaoScreen() { }
AcaoScreen::AcaoScreen(byte PinoControle): _pinoControle(PinoControle) { }
AcaoScreen::~AcaoScreen() { }


/* 
    @brief Verifica se o pino de controle está em HIGH or LOW. Quando
          estiver em HIGH é porque existe uma ação para ser executada
    
    @return True quado o pino estiver em HIGH, False quando o pino estiver em LOW
*/
bool AcaoScreen::acaoAtiva(){
    return digitalRead(_pinoControle);
}
    
void AcaoScreen::setLeds(BoxDadosAcao *DadosAcao) {
    _box.boxLedsRGBB(DadosAcao);
}

void AcaoScreen::resetAcao(BoxDadosAcao *DadosAcao) {
   setLeds(DadosAcao);
}

void AcaoScreen::ledsAcesos(BoxDadosAcao *DadosAcao) {

    bool EmAcao  = true;

    Serial.print(F(" [Entrei na Funcao | "));

    setLeds(DadosAcao);
    while(EmAcao) {                     // Aguarda o cancelamento da ação 
        delayMicroseconds(50000);       // Aguarda 0,5 segundos antes de ler se a ação foi cancelada (otimizando energia)
        EmAcao = acaoAtiva();
    }

    Serial.print(F("Saindo da Funcao] "));

}

void AcaoScreen::ledsXadrezFade(BoxDadosAcao *DadosAcao) {

    bool  IniciarImpar = true;
    int   Percentual   = 100;
    int   Intervalo    = 10;

    _tmpWaitRotina = 11000;

    Serial.print(F(" [Entrei na Funcao | "));

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

    Serial.print(F("Saindo da Funcao] "));
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

void AcaoScreen::ledsTematico(BoxDadosAcao *DadosAcao, eBoxTematico Tema) {

    _box.iniciarMapaBox();
    _box.boxAcaoTematico(Tema, DadosAcao);
    while(acaoAtiva());

}

#pragma region Rotinas para a ação Cascata

void AcaoScreen::ledsAcaoCascata(BoxDadosAcao *DadosAcao) {

    _tmpWaitRotina                      = 11000;
    uint8_t sizeCascata                 = 15;
    uint8_t colunasFeitas               = 0;
    cascata_t cascata[sizeCascata];

    // Mantem a vitrine acesa
    _box.todosLedsAcesos(20, 20, 20);       // Luz de fundo bem fraca
    _box.vitrineLedsRGBB(DadosAcao);

    while(acaoAtiva()) {

        if(_tmpWaitRotina > 10000){

            inicializaCascata(cascata, sizeCascata);
            colunasFeitas = 0;

            delay(5000);
            if(!acaoAtiva()) return;

            // while(acaoAtiva() && colunasFeitas < 14) {
        
            //     for(uint8_t coluna = 0; coluna <= 14 && acaoAtiva(); coluna++) {

            //         if(cascata[coluna].Linha > 0 && (!cascata[coluna].Finalizado)) {
            //             _box.boxAcaoCascata(DadosAcao, cascata, coluna);
            //         }

            //         if((cascata[coluna].Linha - cascata[coluna].Arrasto) > 14) {
            //             colunasFeitas++;
            //             cascata[coluna].Finalizado = true;
            //         }

            //         cascata[coluna].Linha++;
            //     }

            // }
        
            _tmpWaitRotina = 0;
        
        } else { _tmpWaitRotina++; delayMicroseconds(100);}
    }
}

void AcaoScreen::inicializaCascata(cascata_t cascata[], uint8_t SizeCascata) {

    uint8_t qtdColunasShow          = SizeCascata - 1;
    uint8_t colunas[SizeCascata]    = {0};


    Serial.print(F("\n Inicializando CASCATA no objeto BoxAcao:: ........"));
    _box.inicializarCascata();

    cascata_t *pItemCascata = _box.getItemCascata(3);

    pItemCascata->Arrasto = 9;
    pItemCascata->Linha = 10;
    pItemCascata->Coluna = 3;
    pItemCascata->Percentual = .80F;
    pItemCascata->Finalizado = true;


        Serial.print(F("\n\n\nItemCascata->Arrasto: ")), Serial.print(pItemCascata->Arrasto);
        Serial.print(F("\n\n\n"));


    randomUnico(colunas, SizeCascata);

    for(int x = 0; x <= SizeCascata - 1; x++) {

        Serial.print(F("\nPosicao: ")), Serial.print(x);
        Serial.print(F("\t| Coluna: ")), Serial.print(colunas[x]);

    }

    Serial.print(F("\n Montando Dados CASCATA ........"));

delay(2000);

    for(uint8_t indice = 0; indice <= qtdColunasShow; indice++) {


        Serial.print(F("\n\n\nItemCascata->Arrasto:\t\t")), Serial.print(pItemCascata->Arrasto);
        Serial.print(F("\nnItemCascata->Linha:\t\t")), Serial.print(pItemCascata->Linha);
        Serial.print(F("\nnItemCascata->Coluna:\t\t")), Serial.print(pItemCascata->Coluna);
        Serial.print(F("\nnItemCascata->Percentual:\t")), Serial.print(pItemCascata->Percentual);
        Serial.print(F("\nnItemCascata->Finalizado:\t")), Serial.print(pItemCascata->Finalizado);
        Serial.print(F("\n\n\n"));

        // cascata[indice].Coluna       = colunas[indice];
        // cascata[indice].Linha        = random(-3, 2);
        // cascata[indice].Arrasto      = random(3,  6);
        // cascata[indice].Percentual   = 100 / cascata[indice].Arrasto;      // percentual usado para fazer o arrasto
        // cascata[indice].Finalizado   = false;

        delay(250);


        // Serial.print(F("\n"));

        // Serial.print(F("\n.......... [")), Serial.print(i), Serial.print(F("] ..........\n"));

        // Serial.print(F("\ncascata[")), Serial.print(i), Serial.print(F("].Coluna = "));
        // Serial.print(cascata[i].Coluna);

        // Serial.print(F("\ncascata[")), Serial.print(i), Serial.print(F("].Linha = "));
        // Serial.print(cascata[i].Linha);

        // Serial.print(F("\ncascata[")), Serial.print(i), Serial.print(F("].Arrasto = "));
        // Serial.print(cascata[i].Arrasto);

        // Serial.print(F("\ncascata[")), Serial.print(i), Serial.print(F("].Percentual = "));
        // Serial.print(cascata[i].Percentual);

        // Serial.print(F("\ncascata[")), Serial.print(i), Serial.print(F("].Finalizado = "));
        // Serial.print(cascata[i].Finalizado);



    }




}

void AcaoScreen::randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer) {

    bool      valorExiste   = false;
    uint8_t   coluna        = 0;
    uint8_t   minimo        = 1;
    uint8_t   maximo        = SizeBuffer + 1;
    uint8_t   valor         = 0;


    Serial.print(F("\nAcaoScreen::randomUnico:coluna = ")), Serial.print(coluna);
    Serial.print(F(" Qtde Colunas a processar = ")), Serial.print(SizeBuffer);
    valor = random();
    Serial.print(F(" | ponto de inicializacao = ")), Serial.print(valor);
    delay(100);

    // randomSeed(random());                               // Necessário para indicar um ponto de inicialização aleatório
    randomSeed(valor);                               // Necessário para indicar um ponto de inicialização aleatório

    while(coluna < SizeBuffer){

        valor = random(minimo, maximo);
        // Serial.print(F("\nValor randomico = ")), Serial.print(valor);
        // Serial.print(F(" \t( Min = ")), Serial.print(minimo);
        // Serial.print(F(" | Max = ")), Serial.print(maximo), Serial.print(F(" )"));

        valorExiste = false;
        for( int i = 0; i <= SizeBuffer; i++ ){
            if(valor == bufferValores[i]){
                valorExiste = true;
        
                    // Serial.print(F(" - Nao usado"));

                break;
            }
        }

        if(!valorExiste){

            // Serial.print(F(" - Usado como coluna"));
            // Serial.print(F(" | qtde coluna proc = ")), Serial.print(coluna);

            bufferValores[coluna] = valor;
            coluna++;
        }
    }
        Serial.print(F("\n "));

    for(int x = 0; x <= SizeBuffer; x++) {

        Serial.print(F("\nPosicao: ")), Serial.print(x);
        Serial.print(F("\t| Coluna: ")), Serial.print(bufferValores[x]);

    }

    Serial.print(F("\n\nAcaoScreen::randomUnico: [SAINDO] "));

}

#pragma endregion





