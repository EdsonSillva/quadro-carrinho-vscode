

#include "AcaoBox.h"


AcaoBox::AcaoBox() {        // Construtor usando pinos default

    /* Inicialização do Objeto de controle dos Led */
    _Leds = Adafruit_NeoPixel(_totalLeds, 
                              _pinLed,
                              NEO_GRB + NEO_KHZ800);

}       

AcaoBox::AcaoBox(byte pinoControle) : _pinLed(_pin_Led_), _pinoControle(pinoControle) {
    AcaoBox();
 }

AcaoBox::AcaoBox(byte pinoDados, byte pinoControle) : _pinLed(pinoDados), _pinoControle(pinoControle) { 
    AcaoBox();
}

AcaoBox::~AcaoBox() { }

void AcaoBox::inicializarCascata() {

    for (int Posicao = 0; Posicao < _qtdColunas; Posicao++)
    {
        _cascata[Posicao].Linha = 0;
        _cascata[Posicao].Coluna = 0;
        _cascata[Posicao].Arrasto = 0;
        _cascata[Posicao].Percentual = 0;
        _cascata[Posicao].Finalizado = false;
    
    }

}

cascata_t *AcaoBox::getItemCascata(byte Item) {
    return &_cascata[Item];
}

byte AcaoBox::size_Cascata() {
    return _qtdColunas;
}

/* 
    @brief Verifica se o pino de controle está em HIGH or LOW. Quando
          estiver em HIGH é porque existe uma ação para ser executada
    
    @return True quado o pino estiver em HIGH, False quando o pino estiver em LOW
*/
bool AcaoBox::acaoAtiva(){
    if(_emSaudacao) return true;                // Usado para mostar saudação
    return digitalRead(_pinoControle);
}

void AcaoBox::iniciarLeds(int IntensidadeBrilho) {

    setBrilho(IntensidadeBrilho);
    _Leds.begin();
    _Leds.show();
    delay(500);                           // Aguardar um tempo para refletir o comando nos Leds

}

void AcaoBox::setBrilho(uint8_t Intensidade) {
    _intensidadeBrilho = Intensidade;
    _Leds.setBrightness(_intensidadeBrilho);
}

void AcaoBox::showSaudacaoBox(BoxDadosAcao *DadosAcao, byte LuzFundo, int Aguarda = 2000) {

    montarMascaraSaudacao(_MapaBox);            // Monta a imagem
    _emSaudacao = true;                         // Desliga a leitura do pino de controle de ação
    showMapaBoxes(DadosAcao, LuzFundo);         // Mostra a imagem
    _emSaudacao = false;                        // Liga a leitura do pino de controle de ação
    iniciarMapaBox();                           // Limpa o MapaBox
    delay(Aguarda);                             // Tempo que a imagem fica aparecendo
    todosLedsApagados();                        // Limpa a imagem 

}

void AcaoBox::iniciarMapaBox() {
    for(byte Indice = 0; Indice <= 14; Indice++){
        _MapaBox[Indice] = 0b0000000000000000;
    }
}

#pragma region Funções de controle da posição de cada box no quadro de carrinho

int AcaoBox::PosicaoBoxTop(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, eBoxPosicao::boxTop);
}

int AcaoBox::PosicaoBoxBotton(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, eBoxPosicao::boxBottom);
}

int AcaoBox::PosicaoBoxLeft(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, eBoxPosicao::boxLeft);
}

int AcaoBox::PosicaoBoxRight(int PosicaoDada) {
    return PosicaoBox(PosicaoDada, eBoxPosicao::boxRight);
}

int AcaoBox::PosicaoBox(int PosicaoDada, eBoxPosicao PosicaoSolicitada) {

    int LinhaCalculada                = PosicaoDada / (int)qtd_Colunas;
    int LinhaPosicao                  = LinhaCalculada + 1;
    int NumLeft                       = (LinhaPosicao % 2) == 0 ? -1 :  1;
    int NumRight                      = (LinhaPosicao % 2) == 0 ?  1 : -1;
    int DeslocamentoPosicaoCalculado  = (int)(PosicaoDada % (int)qtd_Colunas) + 1;
    int ColunaPosicao                 = (LinhaCalculada % 2) == 0 ? (int)qtd_Colunas - (DeslocamentoPosicaoCalculado - 1) : DeslocamentoPosicaoCalculado;
    int LinhaPosicaoBottom            = LinhaCalculada + 1;
    int DeslocamentoPosicaoBottom     = (LinhaPosicaoBottom % 2) == 0 ? (int)qtd_Colunas - DeslocamentoPosicaoCalculado : (int)ColunaPosicao - 1;
    int PosicaoTop                    = (LinhaCalculada * qtd_Colunas) - DeslocamentoPosicaoCalculado;
    int PosicaoBottom                 = ((LinhaCalculada + 1) * qtd_Colunas) + DeslocamentoPosicaoBottom;
    int PosicaoLeftCalculada          = (PosicaoDada + NumLeft);
    int PosicaoRightCalculada         = (PosicaoDada + NumRight);
    int PosicaoLeft                   = PosicaoLeftCalculada == PosicaoTop || PosicaoLeftCalculada == PosicaoBottom ? -1 : PosicaoLeftCalculada;
    int PosicaoRight                  = PosicaoRightCalculada == PosicaoTop || PosicaoRightCalculada == PosicaoBottom ? -1 : PosicaoRightCalculada;

    switch (PosicaoSolicitada)
    {
        case BoxTop: 
            return PosicaoTop;
            break;
        case BoxBottom:
            return PosicaoBottom;
            break;
        case BoxLeft:
            return PosicaoLeft;
            break;
        case BoxRight:
            return PosicaoRight;
            break;
        case LinhaPosicaoDada:
            return LinhaPosicao;
            break;
        case ColunaPosicaoDada:
            return ColunaPosicao;
            break;
    }
}

// ROTINA PARA RETORNAR A POSICAO DADO A LINHA E COLUNA
// ****************************************************
int AcaoBox::PosicaoBoxCell(int Linha, int Coluna) {
    return (int)(_qtdColunas * (Linha - 1)) + ((Linha % 2) == 0 ? 
                                                _qtdColunas - Coluna :
                                                Coluna - 1);
}

int AcaoBox::PosicaoBoxCellInvertido(int Linha, int Coluna) {
    return (int)(_qtdColunas * (Linha - 1)) + ( (Linha % 2) == 0 ? 
                                                 Coluna - 1   : 
                                                 _qtdColunas - Coluna);
}

#pragma endregion

void AcaoBox::setCorLedsRGBBB(byte Start, byte End, BoxDadosAcao *DadosAcao) {

    uint8_t Brilho  = (uint8_t)DadosAcao->getBrilho(),
            R       = (uint8_t)DadosAcao->getGammaR(),
            G       = (uint8_t)DadosAcao->getGammaG(),
            B       = (uint8_t)DadosAcao->getGammaB();

    if (_Leds.getBrightness() != Brilho) { setBrilho((int)Brilho); }
    
    for(int Led = Start; Led < End; Led++){
        _Leds.setPixelColor(Led, _Leds.Color(G, R, B));
    }
}

void AcaoBox::setCorBoxFade(int Inicio, int R, int G, int B) {
    for(int i = Inicio; i < _totalLeds; i++){
        //Configura a cor do Led
        _Leds.setPixelColor(i, _Leds.Color(R, G, B));
        i++; // Necessário para pular um Led e formar o efeito de grid
    }
    delay(5);
}

void inline AcaoBox::showLeds(int Wait) {
  _Leds.show();
  delay(Wait);
}

void AcaoBox::vitrineLedsRGBB(BoxDadosAcao *DadosAcao) {
    setCorLedsRGBBB(_startLedVitrine, _totalLeds, DadosAcao);
}

void AcaoBox::boxLedsRGBB(BoxDadosAcao *DadosAcao) {
    setCorLedsRGBBB(0, _totalLeds, DadosAcao);
    showLeds(500);
}

void AcaoBox::boxAcaoXadrezFade(bool IniciarImpar, BoxDadosAcao *DadosAcao, int PercentualRecebido) {

    byte  RLow, GLow, BLow, RHigh, GHigh, BHigh, RShow,  GShow,  BShow;

    float PercentualEntrada = (float)(PercentualRecebido / 100.0);
    float PercentualInverso = ((100 - PercentualRecebido) / 100.0);

    RHigh = (byte)(DadosAcao->getGammaR() * PercentualEntrada);
    GHigh = (byte)(DadosAcao->getGammaG() * PercentualEntrada);
    BHigh = (byte)(DadosAcao->getGammaB() * PercentualEntrada);

    RLow  = (byte)(DadosAcao->getGammaR() * PercentualInverso),    
    GLow  = (byte)(DadosAcao->getGammaG() * PercentualInverso),  
    BLow  = (byte)(DadosAcao->getGammaB() * PercentualInverso);

    if (_Leds.getBrightness() != (uint8_t)DadosAcao->getBrilho()) { setBrilho((int)DadosAcao->getBrilho()); }

    if(IniciarImpar){ RShow = RHigh,  GShow = GHigh,  BShow = BHigh; }
    else            { RShow = RLow,   GShow = GLow,   BShow = BLow; }
    
    for(int Led = 0; Led < _qtdBoxes; Led++){
      
        _Leds.setPixelColor(Led, _Leds.Color(GShow, RShow, BShow));
        
        RShow = RShow == RHigh  ?   RLow : RHigh;
        GShow = GShow == GHigh  ?   GLow : GHigh;
        BShow = BShow == BHigh  ?   BLow : BHigh;

    }
    
    vitrineLedsRGBB(DadosAcao);
    showLeds(500);
    
}

void AcaoBox::boxAcaoColuna(bool IniciarImpar, BoxDadosAcao *DadosAcao) {

    byte    Rb = 20,  
            Gb = 20,  
            Bb = 20;

    byte    Rd = 0,  
            Gd = 0,  
            Bd = 0;

    uint8_t Brilho  = (uint8_t)DadosAcao->getBrilho(),
            R       = (uint8_t)DadosAcao->getGammaR(),
            G       = (uint8_t)DadosAcao->getGammaG(),
            B       = (uint8_t)DadosAcao->getGammaB();

    if (_Leds.getBrightness() != (uint8_t)Brilho) { setBrilho((int)Brilho); }

    for(byte L = 1; L <= _qtdLinhas; L++){

      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
      else { Rd = Rb, Gd = Gb, Bd = Bb; }

      for(byte C = 1; C <= _qtdColunas; C++){
        _Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), _Leds.Color(Gd, Rd, Bd));
        Rd = Rd == R ? Rb : R;
        Gd = Gd == G ? Gb : G;
        Bd = Bd == B ? Bb : B;
      }
    }

    vitrineLedsRGBB(DadosAcao);
    showLeds(500);

}

void AcaoBox::boxAcaoLinha(bool IniciarImpar, BoxDadosAcao *DadosAcao) {

    byte    Rb = 20,
            Gb = 20,  
            Bb = 20;

    byte    Rd = 0,  
            Gd = 0,  
            Bd = 0;

    uint8_t Brilho  = (uint8_t)DadosAcao->getBrilho(),
            R       = (uint8_t)DadosAcao->getGammaR(),
            G       = (uint8_t)DadosAcao->getGammaG(),
            B       = (uint8_t)DadosAcao->getGammaB();

    if (_Leds.getBrightness() != (uint8_t)Brilho) { setBrilho((int)Brilho); }

    for(byte C = 1; C <= _qtdColunas; C++){

      if(IniciarImpar){ Rd = R, Gd = G, Bd = B; }
      else { Rd = Rb, Gd = Gb, Bd = Bb; }

      for(byte L = 1; L <= _qtdLinhas; L++){
        _Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), _Leds.Color(Gd, Rd, Bd));
        Rd = Rd == R ? Rb : R;
        Gd = Gd == G ? Gb : G;
        Bd = Bd == B ? Bb : B;
      }
    }

    vitrineLedsRGBB(DadosAcao);
    showLeds(500);

}

#pragma region Rotinas de posição fixa dos carros em cada box

void AcaoBox::boxAcaoTematico(eBoxTematico Tema, BoxDadosAcao *DadosAcao) {

    iniciarMapaBox();                   // Limpa

    MontaMapaBoxTematico(Tema);         // Carrega tema

    showMapaBoxes(DadosAcao, 50);       // Mostra Tema no quadro

}

void AcaoBox::MontaMapaBoxTematico(eBoxTematico Tema) {

    switch (Tema)
    {
    case eBoxTematico::boxBatman:
        _MapaBox[2] = 0b1110000000000001;      // Linha 03 do quadro
        _MapaBox[3] = 0b1110000000000001;      // Linha 04 do quadro
        _MapaBox[4] = 0b1110000000000001;      // Linha 05 do quadro
        break;

    case eBoxTematico::boxMotos:
        _MapaBox[2] = 0b0000000001111111;      // Linha 03 do quadro
        _MapaBox[3] = 0b0000000000000011;      // Linha 04 do quadro
        break;

    case eBoxTematico::boxStarWars:
        _MapaBox[5] = 0b1110000000000001;      // Linha 06 do quadro
        _MapaBox[6] = 0b1110000000000001;      // Linha 07 do quadro
        _MapaBox[7] = 0b1100000000000001;      // Linha 08 do quadro
        _MapaBox[8] = 0b1100000000000001;      // Linha 09 do quadro
        break;

    case eBoxTematico::boxLamborghini:
        _MapaBox[8] = 0b0000000000000111;      // Linha 09 do quadro
        _MapaBox[9] = 0b0000000000001111;      // Linha 10 do quadro
        break;

    case eBoxTematico::boxPorche:
        _MapaBox[10] = 0b0000000000001111;      // Linha 11 do quadro
        _MapaBox[11] = 0b0000000000001111;      // Linha 12 do quadro
        _MapaBox[12] = 0b0000000000001111;      // Linha 13 do quadro
        break;

    case eBoxTematico::boxTesla:
        _MapaBox[13] = 0b0000000000111001;      // Linha 14 do quadro
        break;

    case eBoxTematico::boxBMW:
        _MapaBox[13] = 0b0000000111000001;      // Linha 14 do quadro
        break;

    case eBoxTematico::boxFord:
        _MapaBox[8]  = 0b0000001110000001;      // Linha 09 do quadro
        _MapaBox[9]  = 0b0000111110000001;      // Linha 10 do quadro
        _MapaBox[10] = 0b0000111100000001;      // Linha 11 do quadro
        break;

    case eBoxTematico::boxAstonMartin:
        _MapaBox[10] = 0b0000000011110001;      // Linha 11 do quadro
        break;

    case eBoxTematico::boxPagani:
        _MapaBox[8]  = 0b0000000000011001;      // Linha 09 do quadro
        break;

    case eBoxTematico::boxMacLaren:
        _MapaBox[9]  = 0b0000000001110001;      // Linha 10 do quadro
        break;

    case eBoxTematico::boxAudi:
        _MapaBox[6]  = 0b0000000010000001;      // Linha 07 do quadro
        break;

    case eBoxTematico::boxCorvette:
        _MapaBox[11]  = 0b0000011111110001;      // Linha 12 do quadro
        _MapaBox[12]  = 0b0000011111110001;      // Linha 13 do quadro
        break;

    case eBoxTematico::boxNissan:
        _MapaBox[5]  = 0b0000000000011111;      // Linha 06 do quadro
        break;

    case eBoxTematico::boxFerrari:
        _MapaBox[4]  = 0b0000001000000001;      // Linha 05 do quadro
        _MapaBox[7]  = 0b0000000000001111;      // Linha 08 do quadro
        break;
    
    case eBoxTematico::boxMercedes:
        _MapaBox[6]  = 0b0000000000000111;      // Linha 07 do quadro
        break;

    case eBoxTematico::boxHonda:
        _MapaBox[6]   = 0b0000000000111001;      // Linha 07 do quadro
        break;

    case eBoxTematico::boxAcura:
        _MapaBox[13]  = 0b0000000000000111;      // Linha 14 do quadro
        break;

    case eBoxTematico::boxJaguar:
        _MapaBox[7]  = 0b0000000000110001;      // Linha 08 do quadro
        break;

    case eBoxTematico::boxVelozesFurosos:
        _MapaBox[2]  = 0b0000111100000001;      // Linha 03 do quadro
        _MapaBox[3]  = 0b0001110000000001;      // Linha 04 do quadro
        break;

    case eBoxTematico::boxDodge:
        _MapaBox[7]  = 0b0000000111000001;      // Linha 08 do quadro
        _MapaBox[8]  = 0b0000000001100001;      // Linha 09 do quadro
        break;

    case eBoxTematico::boxVolks:
        _MapaBox[6]  = 0b0000001000000001;      // Linha 07 do quadro
        _MapaBox[7]  = 0b0000111000000001;      // Linha 08 do quadro
        _MapaBox[8]  = 0b0000110000000001;      // Linha 09 do quadro
        _MapaBox[9]  = 0b0000100000000001;      // Linha 10 do quadro
        break;

    case eBoxTematico::boxFiat:
        _MapaBox[6]  = 0b0000000100000001;      // Linha 07 do quadro
        break;

    case eBoxTematico::boxCadiLac:
        _MapaBox[5]  = 0b0000000000100001;      // Linha 06 do quadro
        _MapaBox[8]  = 0b0010000000000001;      // Linha 09 do quadro
        break;

    case eBoxTematico::boxBentley:
        _MapaBox[3]  = 0b0000000000000101;      // Linha 04 do quadro
        break;

    case eBoxTematico::boxMazda:
        _MapaBox[4]  = 0b0000000001100001;      // Linha 05 do quadro
        break;

    case eBoxTematico::boxBugatti:
        _MapaBox[3]  = 0b0000000100000001;      // Linha 04 do quadro
        break;
    
    case eBoxTematico::boxBuick:
        _MapaBox[5]  = 0b0000000001000001;      // Linha 06 do quadro
        break;

    default:
        break;
    }

}

void AcaoBox::showMapaBoxes(BoxDadosAcao *DadosAcao, byte LuzFundo) {

    word        MapaBoxLinha = 0x00;

    byte        RF = LuzFundo,
                GF = LuzFundo,
                BF = LuzFundo;

    byte        Rd = 0,
                Gd = 0,
                Bd = 0;

    byte        RL = 156,   // Cor para Label
                GL = 0,
                BL = 0;

    uint8_t     Brilho  = (uint8_t)DadosAcao->getBrilho(),
                R       = (uint8_t)DadosAcao->getGammaR(),
                G       = (uint8_t)DadosAcao->getGammaG(),
                B       = (uint8_t)DadosAcao->getGammaB();
    
    
    if (_Leds.getBrightness() != Brilho) { setBrilho((int)Brilho); }

    for(byte L = 1; L <= _qtdLinhas; L++){

      MapaBoxLinha = _MapaBox[L - 1];
      
      for(byte C = 1; C <= _qtdColunas; C++){

        if(bitRead(MapaBoxLinha, 16 - C)){

            if(bitRead(_MapaBox[15], 16 - C)) {
                Rd = RL, Gd = GL, Bd = BL;   // É label usa a cor diferente
            } else { 
                Rd = R, Gd = G, Bd = B;     // É informação (dado) usa cor informado da tela
            }

        } else { Rd = RF, Gd = GF, Bd = BF; }

        _Leds.setPixelColor(PosicaoBoxCellInvertido(L, C), _Leds.Color(Gd, Rd, Bd));

      }

    if (!acaoAtiva()) return;
    
    }
    vitrineLedsRGBB(DadosAcao);
    showLeds(500);
}

#pragma endregion

#pragma region Rotinas para tratamento e display da mensagem

void AcaoBox::showMsgBox(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow) {

    bool Label          = false;
    LinhaShow           = LinhaShow - 1;      // Necessário porque os arrays começam na posição 0
    byte LinhaBox       = LinhaShow;

    uint8_t     Brilho  = (uint8_t)DadosAcao->getBrilho(),
                R       = (uint8_t)DadosAcao->getGammaR(),
                G       = (uint8_t)DadosAcao->getGammaG(),
                B       = (uint8_t)DadosAcao->getGammaB();

    iniciarMapaBox();

    for(byte Letra = 0; Letra <= TamanhoMsg; Letra++){
      
        byte FimBitMascara      = 0;
        char LetraMascarada[5]  = {0x00,      // 1º Linha
                                   0x00,      // 2º Linha
                                   0x00,      // 3º Linha
                                   0x00,      // 4º Linha
                                   0x00};     // 5º Linha

        montarMascara(Msg[Letra], LetraMascarada, &FimBitMascara);
        
        for(byte BitLetra = 7; BitLetra >= FimBitMascara; BitLetra--){

            for(byte PosicaoDaLetra = 0; PosicaoDaLetra <= 4; PosicaoDaLetra++){
                bitWrite(_MapaBox[LinhaBox], 0, bitRead(LetraMascarada[PosicaoDaLetra], BitLetra));      // Set o bit 0 da mascara com o bit da mascara da letra
                LinhaBox++;
            }

            if(Label) bitWrite(_MapaBox[15], 0, 1);    //Set o bit 0 da cor com 1 (para label)
            else      bitWrite(_MapaBox[15], 0, 0);    //Set o bit 0 da cor com 0 (para dado)
            
            showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
            shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);
            LinhaBox   = LinhaShow;
            delay(60);
        }

        if(Msg[Letra] != ' '){
            showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
            shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                   // Shift para espaço entre letras
            delay(60);
        }
        
        if (!acaoAtiva()) {Letra = TamanhoMsg + 1;}                                             // Abandona o Loop

    }

    for(byte ColunasBranco = 1; ColunasBranco <= 15; ColunasBranco++ ){
       shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                   // Shift para espaço entre letras
       showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
       delay(60);
    }
}

void AcaoBox::showMsgBoxDebug(char Msg[], byte TamanhoMsg, BoxDadosAcao *DadosAcao, byte LinhaShow) {

    bool Label      = false;
    LinhaShow       = LinhaShow - 1;    // Necessário porque os arrays começam na posição 0
    byte LinhaBox   = LinhaShow;

    uint8_t     Brilho  = (uint8_t)DadosAcao->getBrilho(),
                R       = (uint8_t)DadosAcao->getGammaR(),
                G       = (uint8_t)DadosAcao->getGammaG(),
                B       = (uint8_t)DadosAcao->getGammaB();

    iniciarMapaBox();

    for(byte Letra = 0; Letra <= TamanhoMsg; Letra++){

       if(Msg[Letra] == '<') {
          Label = true;
       } else if(Msg[Letra] == '>') {
          Label = false;
       } else { 

          byte FimBitMascara      = 0;
          char LetraMascarada[5]  = {0x00,    // 1º Linha
                                     0x00,    // 2º Linha
                                     0x00,    // 3º Linha
                                     0x00,    // 4º Linha
                                     0x00};   // 5º Linha
                                     
          montarMascara(Msg[Letra], LetraMascarada, &FimBitMascara);
          
          for(byte BitLetra = 7; BitLetra >= FimBitMascara; BitLetra--){

              for(byte PosicaoDaLetra = 0; PosicaoDaLetra <= 4; PosicaoDaLetra++){
                  bitWrite(_MapaBox[LinhaBox], 0, bitRead(LetraMascarada[PosicaoDaLetra], BitLetra));    //Set o bit 0 da mascara com o bit da mascara da letra
                  LinhaBox++;
              }

              if(Label) bitWrite(_MapaBox[15], 0, 1);    //Set o bit 0 da cor com 1 (para label)
              else      bitWrite(_MapaBox[15], 0, 0);    //Set o bit 0 da cor com 0 (para dado)
              
              showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
              shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                       
              LinhaBox   = LinhaShow;
              delay(60);
          }

          if(Msg[Letra] != ' '){
            showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
            shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
            delay(60);
          }
       }

        if (!acaoAtiva()) {Letra = TamanhoMsg + 1;}     //Abandona o Loop

    }

    for(byte ColunasBranco = 1; ColunasBranco <= 15; ColunasBranco++ ){
       shifEsquerdaMapaBox(LinhaShow, LinhaShow + 4, 1);                                         // Shift para espaço entre letras
       showMapaBoxes(DadosAcao, 40);                                                       // ShowMapaBoxes
       delay(60);
    }
}

void AcaoBox::shifEsquerdaMapaBox(byte PrimeiraLinha, byte UltimaLinha, byte QtdeBit) {

    for(byte PosicaoShift = PrimeiraLinha; PosicaoShift <= UltimaLinha; PosicaoShift++ ){   // Shift Mascarabox
      _MapaBox[PosicaoShift] = (_MapaBox[PosicaoShift] << QtdeBit);
    }
    _MapaBox[15] = (_MapaBox[15] << QtdeBit);       //Anda com a posição da Cor junto com a posição da letra
}

#pragma endregion

void AcaoBox::AcendeOuApagaLeds(uint8_t r, uint8_t g, uint8_t b) {
    for(int Led = 0; Led < Total_Leds; Led++){
      _Leds.setPixelColor(Led, _Leds.Color(r, g, b));
    }
    _Leds.show();
    delay(500);
}

void AcaoBox::todosLedsAcesos(uint8_t r, uint8_t g, uint8_t b) {
    AcendeOuApagaLeds(r, g, b);         // Acende na cor definida em RGB
}

void AcaoBox::todosLedsApagados(){
    AcendeOuApagaLeds(0, 0, 0);           // Apaga os Leds mandando o RGB para 0 (zero) boas práticas
    // _Leds.clear();       // não funcionou bem
}

/* @deprecated metodo antigo */
// void AcaoBox::boxAcaoCascata(BoxDadosAcao *DadosAcao, cascata_t cascata[], uint8_t coluna) {

//     const uint8_t       _MIN_LINHA      =  1;
//     const uint8_t       _MAX_LINHA      = 14;

//     byte                RShow           = 0,
//                         GShow           = 0,
//                         BShow           = 0;

//     uint8_t             Brilho          = (uint8_t)DadosAcao->getBrilho(),
//                         R               = (uint8_t)DadosAcao->getGammaR(),
//                         G               = (uint8_t)DadosAcao->getGammaG(),
//                         B               = (uint8_t)DadosAcao->getGammaB();


//     float               CabecaLinha    = 100.0;                        // 100% do brilho do led
//     int8_t              linhaBase      = cascata[coluna].Linha;
//     int8_t              fimArrasto     = cascata[coluna].Linha - cascata[coluna].Arrasto;
    
//     fimArrasto = fimArrasto > _MIN_LINHA ? fimArrasto : _MIN_LINHA;

//     if(linhaBase > _MAX_LINHA){

//         CabecaLinha = CabecaLinha - (cascata[coluna].Percentual * (linhaBase - _MAX_LINHA));
//         linhaBase = _MAX_LINHA;         // Estabelece no máximo de linhas

//     }

//     RShow = (byte)(R * CabecaLinha);
//     GShow = (byte)(G * CabecaLinha);
//     BShow = (byte)(B * CabecaLinha);

//     if (_Leds.getBrightness() != (uint8_t)Brilho) { setBrilho((int)Brilho); }

//     for(int8_t linha = linhaBase; linha >= fimArrasto; linha--){

//         _Leds.setPixelColor(PosicaoBoxCellInvertido(linha, (int)cascata[coluna].Coluna), _Leds.Color(GShow, RShow, BShow));

//         // Vai diminuindo o brilho
//         CabecaLinha = CabecaLinha - cascata[coluna].Percentual;
//         if (CabecaLinha < 8) {CabecaLinha = 8;}
//         RShow = (byte)(R * CabecaLinha);
//         GShow = (byte)(G * CabecaLinha);
//         BShow = (byte)(B * CabecaLinha);

//     }

//     showLeds(150);

// }

void AcaoBox::boxAcaoCascata(BoxDadosAcao *DadosAcao, cascata_t *itemCascata, byte luzFundo) {

    const uint8_t       MIN_LINHA      =  1;
    const uint8_t       MAX_LINHA      = 14;

    byte                RShow           = 0,
                        GShow           = 0,
                        BShow           = 0;

    uint8_t             Brilho          = (uint8_t)DadosAcao->getBrilho(),
                        R               = (uint8_t)DadosAcao->getGammaR(),
                        G               = (uint8_t)DadosAcao->getGammaG(),
                        B               = (uint8_t)DadosAcao->getGammaB();


    float               CabecaLinha    = 100.0;                        // 100% do brilho do led
    int8_t              linhaBase      = itemCascata->Linha;
    int8_t              fimArrasto     = itemCascata->Linha - itemCascata->Arrasto;
    
    fimArrasto = fimArrasto > MIN_LINHA ? fimArrasto : MIN_LINHA;

    // Serial.print(F("\n\n\tCabecaLinha\t")), Serial.print(CabecaLinha);

    if(linhaBase > MAX_LINHA){

        // Serial.print(F("\n\t--> LinhaBase > MAX_Linha ....."));
        // Serial.print(F("\n\tCabecaLinha\t")), Serial.print(CabecaLinha);

        // Serial.print(F("\tCabecaLinha - (itemCascata->Percentual * (linhaBase - MAX_LINHA))\t")), Serial.print(CabecaLinha - (itemCascata->Percentual * (linhaBase - MAX_LINHA)));

        CabecaLinha = CabecaLinha - (itemCascata->Percentual * (linhaBase - MAX_LINHA));

        // Serial.print(F("\n\n\tCabecaLinha\t")), Serial.print(CabecaLinha);
        // Serial.print(F("\n\titemCascata->Percentual\t")), Serial.print(itemCascata->Percentual);
        // Serial.print(F("\n\tlinhaBase\t")), Serial.print(linhaBase);
        // Serial.print(F("\n\t_MAX_LINHA\t")), Serial.print(MAX_LINHA);

        linhaBase = MAX_LINHA;         // Estabelece no máximo de linhas

    }

    // Serial.print(F("\n\n\tlinhaBase\t")), Serial.print(linhaBase);

    // Serial.print(F("\n\n\tR\t")), Serial.print(R);
    // Serial.print(F("\t(R * CabecaLinha)\t")), Serial.print(R * (float)(CabecaLinha / 100));

    // Serial.print(F("\n\tG\t")), Serial.print(G);
    // Serial.print(F("\t(G * CabecaLinha)\t")), Serial.print(G * (float)(CabecaLinha / 100));

    // Serial.print(F("\n\tB\t")), Serial.print(B);
    // Serial.print(F("\t(B * CabecaLinha)\t")), Serial.print(B * (float)(CabecaLinha / 100));

    if (_Leds.getBrightness() != (uint8_t)Brilho) { setBrilho((int)Brilho); }

    for(int8_t linha = linhaBase; linha >= fimArrasto; linha--){

        if (CabecaLinha > 4) {              // Usado 4 porque existe arrasto de até 6 linhas

            // Serial.print(F("\n\n\tR\t")), Serial.print(R);
            // Serial.print(F("\t(R * CabecaLinha)\t")), Serial.print(R * (float)(CabecaLinha / 100));

            // Serial.print(F("\n\tG\t")), Serial.print(G);
            // Serial.print(F("\t(G * CabecaLinha)\t")), Serial.print(G * (float)(CabecaLinha / 100));

            // Serial.print(F("\n\tB\t")), Serial.print(B);
            // Serial.print(F("\t(B * CabecaLinha)\t")), Serial.print(B * (float)(CabecaLinha / 100));

            RShow = (byte)(R * (float)(CabecaLinha / 100));
            GShow = (byte)(G * (float)(CabecaLinha / 100));
            BShow = (byte)(B * (float)(CabecaLinha / 100));

        } else {        // Arrasto finalizado

            RShow = luzFundo;
            GShow = luzFundo;
            BShow = luzFundo;

        }

        // Serial.print(F("\n\n\tRShow\t")), Serial.print(RShow);
        // Serial.print(F("\n\tGShow\t")), Serial.print(GShow);
        // Serial.print(F("\n\tBShow\t")), Serial.print(BShow);
        // Serial.print(F("\n"));

        // Serial.print(F("\n\n\t>>> Leds em\t")), Serial.print(CabecaLinha);
        // Serial.print(F("\t na linha\t")), Serial.print(linha);
        // Serial.print(F("\tfimArrasto\t")), Serial.print(fimArrasto);

        _Leds.setPixelColor(PosicaoBoxCellInvertido(linha, (int)itemCascata->Coluna), _Leds.Color(GShow, RShow, BShow));

        // Serial.print(F("\n\n\tlinhaBase\t")), Serial.print(linhaBase);
        // Serial.print(F("\tLinha\t")), Serial.print(linha);
        // Serial.print(F("\tCabecaLinha\t")), Serial.print(CabecaLinha);

        // Vai diminuindo o brilho
        CabecaLinha = CabecaLinha - itemCascata->Percentual;

        // Serial.print(F("\tNova CabecaLinha\t")), Serial.print(CabecaLinha);
        // Serial.print(F("\n\titemCascata->Percentual\t")), Serial.print(itemCascata->Percentual);
        // Serial.print(F("\titemCascata->Arrasto\t")), Serial.print(itemCascata->Arrasto);
        // Serial.print(F("\tfimArrasto\t")), Serial.print(fimArrasto);

    }

    showLeds(50);

}




