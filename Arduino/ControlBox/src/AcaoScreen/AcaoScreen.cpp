

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

void AcaoScreen::ledsAcaoLinhaColuna(BoxDadosAcao *DadosAcao, eAcaoBox Acao = eAcaoBox::acaoLinha) {

    bool IniciarImpar = true;
    _tmpWaitRotina = 11000;

    while(acaoAtiva()) {

        if(_tmpWaitRotina > 10000) {
        
            switch (Acao)
            {
            case eAcaoBox::acaoLinha:
                _box.boxAcaoLinha(IniciarImpar, DadosAcao);
                break;
            case eAcaoBox::acaoColuna:
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

/* @deprecated modo antigo */
void AcaoScreen::ledsTematico(BoxDadosAcao *DadosAcao, eBoxTematico Tema) {

    _box.iniciarMapaBox();
    _box.boxAcaoTematico(Tema, DadosAcao);
    while(acaoAtiva());

}

void AcaoScreen::ledsTematicoByItem(BoxDadosAcao *DadosAcao, byte Boxes[], byte sizeBoxes) {

    _box.boxAcaoTematicoByItem(DadosAcao, Boxes, sizeBoxes);

    while(acaoAtiva());

}


#pragma region Rotinas para a ação Cascata

void AcaoScreen::ledsAcaoCascata(BoxDadosAcao *DadosAcao) {

    _tmpWaitRotina                      = 11000;
    uint8_t colunasFeitas               = 0;
    cascata_t *itemCascata              = NULL;
    byte luzFundo                       = 20;

    // Mantem a vitrine acesa
    _box.todosLedsAcesos(luzFundo, luzFundo, luzFundo);       // Luz de fundo bem fraca
    _box.vitrineLedsRGBB(DadosAcao);

    inicializaCascata();                    // Inicializa uma única vez e depois somente reset a linha

    while(acaoAtiva()) {

        if(_tmpWaitRotina > 3000){

            colunasFeitas = 0;

            // if(!acaoAtiva()) return;

            // Serial.print(F("\n Inicializando While da CASCATA no objeto AcaoScreen:: ........"));

            while(acaoAtiva() && colunasFeitas < 14) {
        
                for(uint8_t item = 0; item <= 14 && acaoAtiva(); item++) {

                    // Serial.print(F("\nColunaFeita:\t")), Serial.print(colunasFeitas);

                    itemCascata = _box.getItemCascata(item);

                    if(itemCascata->Linha > 0 && (!itemCascata->Finalizado)) {

                        // if (itemCascata->Coluna == 7)
                        // {
                            
                            // Serial.print(F("\tExec (boxAcaoCascata) do Item (")), Serial.print(item);
                            // Serial.print(F(") Coluna:\t")), Serial.print(itemCascata->Coluna);
                            // Serial.print(F("\t Linha:\t")), Serial.print(itemCascata->Linha);

                            _box.boxAcaoCascata(DadosAcao, itemCascata, luzFundo);

                        // }

                    }

                    if((itemCascata->Linha - itemCascata->Arrasto) > 14 && !itemCascata->Finalizado) {

                        // Serial.print(F("\nColunaFeita:\t")), Serial.print(colunasFeitas);
                        // Serial.print(F(" - Ok"));

                        colunasFeitas++;
                        itemCascata->Finalizado = true;
                    }

                    itemCascata->Linha++;           // Anda com a linha da coluna

                    // if( item == 14) Serial.print(F("\n"));

                }

            }
        
            // Serial.print(F("\n\n >>> ------------------------ <<<"));
            // Serial.print(F("\n >>> Finalizado Ciclo Cascata <<<"));
            // Serial.print(F("\n >>> ------------------------ <<<\n\n"));

            if (acaoAtiva()) { 
                _tmpWaitRotina = 0;
                // inicializaCascata();                    // Inicializa uma única vez e depois somente reset a linha
                resetCascata(); 
            }
        
        } else { _tmpWaitRotina++; delayMicroseconds(100);}
    }
}

void AcaoScreen::inicializaCascata() {

    uint8_t     sizeCascata                         = _box.size_Cascata();
    uint8_t     colunas[sizeCascata]                = {0};
    cascata_t   *pItemCascata                       = NULL;

    // Serial.print(F("\n Inicializando CASCATA no objeto BoxAcao:: ........"));
    _box.inicializarCascata();

    randomUnico(colunas, sizeCascata);

    // for(int x = 0; x < sizeCascata; x++) {
    //     Serial.print(F("\nPosicao: ")), Serial.print(x);
    //     Serial.print(F("\t| Coluna: ")), Serial.print(colunas[x]);
    // }

    // Serial.print(F("\n Montando Dados CASCATA ........"));

    // delay(2000);

    for(uint8_t item = 0; item < sizeCascata && acaoAtiva(); item++) {

        pItemCascata = _box.getItemCascata(item);

        pItemCascata->Coluna        = colunas[item];
        pItemCascata->Linha         = random(-3, 2);
        pItemCascata->LinhaInicial  = pItemCascata->Linha;
        pItemCascata->Arrasto       = random(7,  10);
        pItemCascata->Percentual    = 100 / pItemCascata->Arrasto;      // percentual usado para fazer o arrasto
        pItemCascata->Finalizado    = false;

        // Serial.print(F("\n\n\nItemCascata->Linha:\t\t")), Serial.print(pItemCascata->Linha);
        // Serial.print(F("\nItemCascata->Coluna:\t\t")), Serial.print(pItemCascata->Coluna);
        // Serial.print(F("\nItemCascata->Arrasto:\t\t")), Serial.print(pItemCascata->Arrasto);
        // Serial.print(F("\nItemCascata->Percentual:\t")), Serial.print(pItemCascata->Percentual);
        // Serial.print(F("\nItemCascata->Finalizado:\t")), Serial.print(pItemCascata->Finalizado);
        // Serial.print(F("\n\n\n"));

        // delay(250);

    }

}

void AcaoScreen::resetCascata() {

    uint8_t     sizeCascata                         = _box.size_Cascata();
    cascata_t   *pItemCascata                       = NULL;

    // Serial.print(F("\n Resetando CASCATA no objeto BoxAcao:: ........"));

    for(uint8_t item = 0; item < sizeCascata && acaoAtiva(); item++) {

        pItemCascata = _box.getItemCascata(item);

        // Serial.print(F("\n\n\nAntes-ItemCascata->Linha:\t\t")), Serial.print(pItemCascata->Linha);

        pItemCascata->Linha         = pItemCascata->LinhaInicial;
        pItemCascata->Finalizado    = false;

        // Serial.print(F("\n\nDepois-ItemCascata->Linha:\t\t")), Serial.print(pItemCascata->Linha);
        // Serial.print(F("\nItemCascata->Coluna:\t\t")), Serial.print(pItemCascata->Coluna);
        // Serial.print(F("\nItemCascata->Arrasto:\t\t")), Serial.print(pItemCascata->Arrasto);
        // Serial.print(F("\nItemCascata->Percentual:\t")), Serial.print(pItemCascata->Percentual);
        // Serial.print(F("\nItemCascata->Finalizado:\t")), Serial.print(pItemCascata->Finalizado);
        // Serial.print(F("\n\n\n"));

        // delay(250);

    }

}

void AcaoScreen::randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer) {

    bool      valorExiste   = false;
    uint8_t   coluna        = 0;
    uint8_t   minimo        = 1;
    uint8_t   maximo        = SizeBuffer + 1;
    uint8_t   valor         = 0;


    // Necessário inicializar os valores porque estava dando problema intermitente com sujeira
    // for (int posicao = 0; posicao < SizeBuffer; posicao++)
    // {
    //     bufferValores[posicao] = 0;
    // }
    

    // Serial.print(F("\nAcaoScreen::randomUnico:coluna = ")), Serial.print(coluna);
    // Serial.print(F(" Qtde Colunas a processar = ")), Serial.print(SizeBuffer);
    valor = random();
    // Serial.print(F(" | ponto de inicializacao = ")), Serial.print(valor);
    // delay(100);

    // randomSeed(random());                               // Necessário para indicar um ponto de inicialização aleatório
    randomSeed(valor);                               // Necessário para indicar um ponto de inicialização aleatório

    while(coluna < SizeBuffer && acaoAtiva()){

        valor = random(minimo, maximo);

        // Serial.print(F("\nValor randomico = ")), Serial.print(valor);
        // Serial.print(F(" \t( Min = ")), Serial.print(minimo);
        // Serial.print(F(" | Max = ")), Serial.print(maximo), Serial.print(F(" )"));

        valorExiste = false;
        for( int i = 0; i < SizeBuffer; i++ ){
            if(valor == bufferValores[i]){
                valorExiste = true;
        
                    // Serial.print(F(" - ja usado"));

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

    // Serial.print(F("\n"));

    // for(int x = 0; x < SizeBuffer; x++) {

    //     Serial.print(F("\nPosicao: ")), Serial.print(x);
    //     Serial.print(F("\t| Coluna: ")), Serial.print(bufferValores[x]);

    // }

    // Serial.print(F("\n\nAcaoScreen::randomUnico: [SAINDO] "));

}

#pragma endregion

void AcaoScreen::ledsHunter(BoxDadosAcao *DadosAcao) {

    byte    CorpoSnakeMax   = _CorpoSnakeMax_;

    alvo_t  alvo            = {0, {0,0,0}};
    snake_t snake;
    box_t   BoxNovo         = {0, {0,0,0}};

    snake.Arrasto                       = 1;
    snake.Corpo[snake.Arrasto].Posicao  = DadosAcao->converteLinhaColuna(7, 8);
    snake.Corpo[snake.Arrasto].RGB.R    = DadosAcao->getGammaR();
    snake.Corpo[snake.Arrasto].RGB.G    = DadosAcao->getGammaG();
    snake.Corpo[snake.Arrasto].RGB.B    = DadosAcao->getGammaB();

    alvo = _box.getAlvoBox(DadosAcao, snake.Corpo[snake.Arrasto].Posicao);

    while (acaoAtiva())
    {

        _box.moveSnake(DadosAcao, snake);
    
        BoxNovo = _box.getPosicaoBoxByAlvo(DadosAcao, 
                                           snake.Corpo[snake.Arrasto], 
                                           _box.deslocamentoBox(DadosAcao, 
                                                                alvo.Posicao,
                                                                snake.Corpo[snake.Arrasto].Posicao
                                            )
                   );


        if(BoxNovo.Posicao == alvo.Posicao) {
            // Acertou o alvo
            // Gerara novo alvo
            alvo = _box.getAlvoBox(DadosAcao, snake.Corpo[snake.Arrasto].Posicao);
            
            // Aumenta o arrasto
            if(snake.Arrasto <= CorpoSnakeMax) {
                snake.Arrasto++;
            } else {
                // Shift posicao -1 no Snake
                descerPosicaoSnake(&snake);
            }

        } else {
            // Não acertou o alvo

            descerPosicaoSnake(&snake);
        }

        snake.Corpo[snake.Arrasto] = BoxNovo;

    }

}

void AcaoScreen::descerPosicaoSnake(snake_t *snake) {

    // Posição anterior recebe posição acima
    for (int posicao = 0; posicao < snake->Arrasto; posicao++)
    {
        snake->Corpo[posicao].Posicao   = snake->Corpo[posicao + 1].Posicao;
        snake->Corpo[posicao].RGB       = snake->Corpo[posicao + 1].RGB;

        // snake->Corpo[posicao].RGB.R     = snake->Corpo[posicao + 1].RGB.R;
        // snake->Corpo[posicao].RGB.G     = snake->Corpo[posicao + 1].RGB.G;
        // snake->Corpo[posicao].RGB.B     = snake->Corpo[posicao + 1].RGB.B;
    }

    // Limpa a posição cabeça
    snake->Corpo[snake->Arrasto].Posicao    = 0;
    snake->Corpo[snake->Arrasto].RGB        = {0, 0, 0};


    // snake->Corpo[snake->Arrasto].RGB.R     = 0;
    // snake->Corpo[snake->Arrasto].RGB.G     = 0;
    // snake->Corpo[snake->Arrasto].RGB.B     = 0;


}


