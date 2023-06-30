

#include "AcaoScreen.h"

AcaoScreen::AcaoScreen() { }
AcaoScreen::AcaoScreen(byte PinoControle): _pinoControle(PinoControle) { }
AcaoScreen::~AcaoScreen() { }

/* 
    @brief Verifica se o pino de controle está em HIGH ou LOW. Quando
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

    setLeds(DadosAcao);

    while(EmAcao) {                     // Aguarda o cancelamento da ação 
        delayMicroseconds(50000);       // Aguarda 0,5 segundos antes de ler se a ação foi cancelada (otimizando energia)
        EmAcao = acaoAtiva();
    }

}

void AcaoScreen::ledsXadrezFade(BoxDadosAcao *DadosAcao) {

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

void AcaoScreen::ledsTematicoByItem(BoxDadosAcao *DadosAcao, byte Boxes[], byte sizeBoxes) {

    if (sizeBoxes > 0) {
        _box.boxAcaoTematicoByItem(DadosAcao, Boxes, sizeBoxes);
    }

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

            while(acaoAtiva() && colunasFeitas < 14) {
        
                for(uint8_t item = 0; item <= 14 && acaoAtiva(); item++) {

                    itemCascata = _box.getItemCascata(item);

                    if(itemCascata->Linha > 0 && (!itemCascata->Finalizado)) {

                        _box.boxAcaoCascata(DadosAcao, itemCascata, luzFundo);

                    }

                    if((itemCascata->Linha - itemCascata->Arrasto) > 14 && !itemCascata->Finalizado) {

                        colunasFeitas++;
                        itemCascata->Finalizado = true;

                    }

                    itemCascata->Linha++;           // Anda com a linha da coluna

                }

            }
        
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

    _box.inicializarCascata();

    randomUnico(colunas, sizeCascata);

    for(uint8_t item = 0; item < sizeCascata && acaoAtiva(); item++) {

        pItemCascata = _box.getItemCascata(item);

        pItemCascata->Coluna        = colunas[item];
        pItemCascata->Linha         = random(-3, 2);
        pItemCascata->LinhaInicial  = pItemCascata->Linha;
        pItemCascata->Arrasto       = random(7,  14);
        pItemCascata->Percentual    = 100 / pItemCascata->Arrasto;      // percentual usado para fazer o arrasto
        pItemCascata->Finalizado    = false;

    }

}

void AcaoScreen::resetCascata() {

    uint8_t     sizeCascata                         = _box.size_Cascata();
    cascata_t   *pItemCascata                       = NULL;

    for(uint8_t item = 0; item < sizeCascata && acaoAtiva(); item++) {

        pItemCascata                = _box.getItemCascata(item);
        pItemCascata->Linha         = pItemCascata->LinhaInicial;
        pItemCascata->Finalizado    = false;

    }

}

void AcaoScreen::randomUnico(uint8_t bufferValores[], uint8_t SizeBuffer) {

    bool      valorExiste   = false;
    uint8_t   coluna        = 0;
    uint8_t   minimo        = 1;
    uint8_t   maximo        = SizeBuffer + 1;
    uint8_t   valor         = 0;

    valor = random();

    randomSeed(valor);                               // Necessário para indicar um ponto de inicialização aleatório

    while(coluna < SizeBuffer && acaoAtiva()){

        valor = random(minimo, maximo);

        valorExiste = false;

        for( int i = 0; i < SizeBuffer; i++ ){
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

#pragma region Rotinas para ação Snake

void AcaoScreen::inicializarSnake(BoxDadosAcao *DadosAcao, snake_t *snake) {

    byte incremento     = 0;

    // boxRGB_t BoxRGB     = _box.getBoxRGB(DadosAcao, DadosAcao->converteLinhaColuna(6, 8));
    boxRGB_t BoxRGB     = snake->CorFundo;

    snake->Arrasto      = 1;

    for (byte posicao = 0; posicao < 2; posicao++)
    {
        snake->Corpo[posicao].Posicao  = DadosAcao->converteLinhaColuna(6 + incremento, 8);
        snake->Corpo[posicao].RGB = BoxRGB;    
        incremento++;
    }

}

void AcaoScreen::ledsAcaoSnake(BoxDadosAcao *DadosAcao) {

    byte        CorpoSnakeMax   = _CorpoSnakeMax_;
    alvo_t      alvo            = {0, {0,0,0}};
    box_t       BoxNovo         = {0, {0,0,0}};
    boxRGB_t    RGBAlvo         = {255, 20, 50};
    snake_t     snake;
    bool        deslocaArrasto  = true;
    snake.CorFundo              = {20, 20, 20};

    _box.todosLedsAcesos(snake.CorFundo.R, snake.CorFundo.G, snake.CorFundo.B);

    inicializarSnake(DadosAcao, &snake);

    // alvo = _box.getAlvoBox(DadosAcao, snake.Corpo[snake.Arrasto].Posicao);
    alvo = buscarNovoAlvo(DadosAcao, &snake);

    _box.showAlvo(DadosAcao, alvo, RGBAlvo);
    // _box.showCabecaSnake(DadosAcao, &snake);

    while (acaoAtiva())
    {
  
        BoxNovo = buscarNovaPosicao(DadosAcao, &snake, &alvo);

        if(deslocaArrasto) descerPosicaoSnake(&snake);

        snake.Corpo[snake.Arrasto] = BoxNovo;

        _box.moveSnake(DadosAcao, snake);

        deslocaArrasto = true;          // Desloca sempre que não acertar o alvo

        if(BoxNovo.Posicao == alvo.Posicao) {

            // Acertou o alvo, onde sera gerado novo alvo

            // Antes de gerar um novo alvo, o alvo deve passar o RGB original
            // Guarda o RGB original do quadro
            snake.Corpo[snake.Arrasto].RGB = alvo.RGB;

            // alvo = _box.getAlvoBox(DadosAcao, snake.Corpo[snake.Arrasto].Posicao);
            alvo = buscarNovoAlvo(DadosAcao, &snake);

            _box.showAlvo(DadosAcao, alvo, RGBAlvo);

            // Aumenta o arrasto
            if(snake.Arrasto <= CorpoSnakeMax) {
                
                deslocaArrasto = false;
                snake.Arrasto++;
                snake.Corpo[snake.Arrasto] = BoxNovo;       // Garantir q a nova posição tenha o valor do último box

            }

        } 

    }

}

void AcaoScreen::descerPosicaoSnake(snake_t *snake) {

    // Posição anterior recebe posição acima
    for (int posicao = 0; posicao < snake->Arrasto; posicao++)
    {
        snake->Corpo[posicao].Posicao   = snake->Corpo[posicao + 1].Posicao;
        snake->Corpo[posicao].RGB       = snake->Corpo[posicao + 1].RGB;
    }

    // Limpa a posição cabeça
    snake->Corpo[snake->Arrasto].Posicao    = 0;
    snake->Corpo[snake->Arrasto].RGB        = {0, 0, 0};

}

box_t AcaoScreen::buscarNovaPosicao(BoxDadosAcao *DadosAcao, snake_t *snake, alvo_t *alvo) {

    box_t                       BoxNovo         = {0, {0,0,0}};
    static eBoxMovimentoSnake   movimento;

    if(movimento == eBoxMovimentoSnake::semMovimento) {

        movimento = eBoxMovimentoSnake::boxColuna;

    }

    BoxNovo = _box.getPosicaoBoxByAlvo(DadosAcao, 
                                        &snake->Corpo[snake->Arrasto], 
                                        _box.deslocamentoBox(DadosAcao, 
                                                            alvo,
                                                            snake,
                                                            movimento
                                        )
                );
    
    if(BoxNovo.Posicao == snake->Corpo[snake->Arrasto - 2].Posicao) {

        if(movimento == eBoxMovimentoSnake::boxColuna)
            movimento = eBoxMovimentoSnake::boxLinha;
        else
            movimento = eBoxMovimentoSnake::boxColuna;

    }

    byte parteDoCorpo = procurarCorpoSnake(&BoxNovo, snake);

    if(parteDoCorpo > 0) 
        BoxNovo.RGB = snake->Corpo[parteDoCorpo].RGB;

    return BoxNovo;

}

alvo_t AcaoScreen::buscarNovoAlvo(BoxDadosAcao *DadosAcao, snake_t *snake) {

    alvo_t  alvo            = {0, {0,0,0}};
    byte    LinhaSnake      = DadosAcao->numLinha(snake->Corpo[snake->Arrasto].Posicao);
    byte    ColunaSnake     = DadosAcao->numColuna(snake->Corpo[snake->Arrasto].Posicao);

    alvo                    = _box.getAlvoBox(DadosAcao, snake->Corpo[snake->Arrasto].Posicao);

    byte    LinhaAlvo       = DadosAcao->numLinha(alvo.Posicao);
    byte    ColunaAlvo      = DadosAcao->numColuna(alvo.Posicao);
    byte    alvoNoCorpo     = procurarCorpoSnake(&alvo, snake);

    if(alvoNoCorpo || LinhaAlvo == LinhaSnake || ColunaAlvo == ColunaSnake) 

        alvo = buscarNovoAlvo(DadosAcao, snake);

    return alvo;

}

byte AcaoScreen::procurarCorpoSnake(box_t *Box, snake_t *snake) {

    for (byte posicao = 1; posicao < snake->Arrasto; posicao++)
    {
        if(Box->Posicao == snake->Corpo[posicao].Posicao)
            return posicao;
    }
    return 0;

}

void AcaoScreen::entrarNaToca(BoxDadosAcao *DadosAcao, snake_t *snake) {

    for (byte fimArrasto = 0; fimArrasto > snake->Arrasto; fimArrasto++)
    {
        // Em construção
        _box.moveSnakeToca(DadosAcao, snake, fimArrasto);
        
    }

}

#pragma endregion

