

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

// TODO: Ajustado o final do loop para 16, por ter 16 posições o MapaBox
void AcaoBox::iniciarMapaBox() {
    for(byte Indice = 0; Indice <= 15; Indice++){
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


boxRGB_t AcaoBox::getBoxRGB(BoxDadosAcao *DadosAcao, linCol PosicaoBox) {

    byte        Linha           = DadosAcao->numLinha(PosicaoBox);
    byte        Coluna          = DadosAcao->numColuna(PosicaoBox);
    boxRGB_t    RGBBox          = {0, 0, 0};

    int BoxAddress = PosicaoBoxCellInvertido(Linha, Coluna);

    uint32_t RGB32 = _Leds.getPixelColor(BoxAddress);

    RGBBox.R = (byte)(RGB32 >> 16);
    RGBBox.G = (byte)(RGB32 >> 8);
    RGBBox.B = (byte)RGB32;

    return RGBBox;

}

#pragma region Rotinas de posição fixa dos carros em cada box

void AcaoBox::boxAcaoTematicoByItem(BoxDadosAcao *DadosAcao, byte Boxes[], byte sizeBoxes) {

    byte Linha                      = 0;
    byte Coluna                     = 0;

    iniciarMapaBox();                                           // Limpa

    for (byte item = 0; item < sizeBoxes; item++)
    {
        Linha = DadosAcao->numLinha(Boxes[item]);
        Coluna = DadosAcao->numColuna(Boxes[item]);

        Linha--;                                                // Adequando por conta do array do _MapaBox
        Coluna = (byte)((Coluna - DeslocamentoColuna) * -1);    // Invertendo a posiçao para posição do bit

        bitSet(_MapaBox[Linha], Coluna);
        bitSet(_MapaBox[Linha], 16 );                           // Necessário manter 1 na 16* posição do bit

    }

    showMapaBoxes(DadosAcao, 50);                               // Mostra Tema no quadro

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


    if(linhaBase > MAX_LINHA){

        CabecaLinha = CabecaLinha - (itemCascata->Percentual * (linhaBase - MAX_LINHA));

        linhaBase = MAX_LINHA;         // Estabelece no máximo de linhas

    }

    if (_Leds.getBrightness() != (uint8_t)Brilho) { setBrilho((int)Brilho); }

    for(int8_t linha = linhaBase; linha >= fimArrasto; linha--){

        if (CabecaLinha > 4) {              // Usado 4 porque existe arrasto de até 6 linhas

            RShow = (byte)(R * (float)(CabecaLinha / 100));
            GShow = (byte)(G * (float)(CabecaLinha / 100));
            BShow = (byte)(B * (float)(CabecaLinha / 100));

        } else {        // Arrasto finalizado

            RShow = (byte)(R * 0.15);
            GShow = (byte)(G * 0.15);
            BShow = (byte)(B * 0.15);

        }

        _Leds.setPixelColor(PosicaoBoxCellInvertido(linha, (int)itemCascata->Coluna), _Leds.Color(GShow, RShow, BShow));

        // Vai diminuindo o brilho
        CabecaLinha = CabecaLinha - itemCascata->Percentual;

    }

    showLeds(50);

}

void AcaoBox::showBox(byte Linha, byte Coluna, boxRGB_t RGB) {

    _Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), 
                        _Leds.Color(RGB.R, RGB.G, RGB.B)
    );

    showLeds(150);

}

#pragma region Snake Target

void AcaoBox::showAlvo(BoxDadosAcao *DadosAcao, alvo_t Alvo, boxRGB_t RGB) {

    byte    Linha       = DadosAcao->numLinha(Alvo.Posicao);
    byte    Coluna      = DadosAcao->numColuna(Alvo.Posicao);

    showBox(Linha, Coluna, RGB);

}

void AcaoBox::showCabecaSnake(BoxDadosAcao *DadosAcao, snake_t *Snake) {

    byte    Linha       = DadosAcao->numLinha(Snake->Corpo[Snake->Arrasto].Posicao);
    byte    Coluna      = DadosAcao->numColuna(Snake->Corpo[Snake->Arrasto].Posicao);

    showBox(Linha, Coluna, Snake->Corpo[Snake->Arrasto].RGB);

}

alvo_t AcaoBox::getAlvoBox(BoxDadosAcao *DadosAcao, linCol PosicaoBox) {

    long        valor       = random();

    byte        AlvoLinha       = 1;
    byte        AlvoColuna      = 1;
    linCol      AlvoLinCol      = PosicaoBox;
    alvo_t      BoxAlvo         = {0, {0, 0, 0}};

    randomSeed(valor);                               // Necessário para indicar um ponto de inicialização aleatório

    while (AlvoLinCol == PosicaoBox)
    {
        AlvoLinha   = (byte)random(1, _qtdLinhas + 1);
        AlvoColuna  = (byte)random(1, _qtdColunas + 1);

        AlvoLinha   = AlvoLinha  > 14 ? 14 : AlvoLinha;
        AlvoColuna  = AlvoColuna > 15 ? 15 : AlvoColuna;

        AlvoLinCol = DadosAcao->converteLinhaColuna(AlvoLinha, AlvoColuna);

    }

    BoxAlvo.Posicao = AlvoLinCol;
    BoxAlvo.RGB = getBoxRGB(DadosAcao, AlvoLinCol);

    return BoxAlvo;
}

eBoxPosicao AcaoBox::deslocamentoBox(BoxDadosAcao *DadosAcao, linCol Alvo, linCol PosicaoBox) {

    if(Alvo == PosicaoBox) {

        return eBoxPosicao::boxNoAlvo;

    } else {

        byte AlvoLinha      = DadosAcao->numLinha(Alvo);
        byte AlvoColuna     = DadosAcao->numColuna(Alvo);

        byte BoxLinha       = DadosAcao->numLinha(PosicaoBox);
        byte BoxColuna      = DadosAcao->numColuna(PosicaoBox);

        if( AlvoColuna < BoxColuna ) {
            //Alvo a esquerda
            return eBoxPosicao::boxLeft;
        } else if( AlvoColuna > BoxColuna ) {
            // Alvo a Direita
            return eBoxPosicao::boxRight;
        } else if( AlvoLinha  < BoxLinha ) {
            // Alvo a Baixo
            return eBoxPosicao::boxTop;
        } 

        return eBoxPosicao::boxBottom;

    }

}

/* @deprecated metodo antigo */
eBoxPosicao AcaoBox::deslocamentoBox(BoxDadosAcao *DadosAcao, alvo_t *Alvo, snake_t *snake) {

    if(Alvo->Posicao == snake->Corpo[snake->Arrasto].Posicao) {

        return eBoxPosicao::boxNoAlvo;

    } else {

        byte AlvoLinha      = DadosAcao->numLinha(Alvo->Posicao);
        byte AlvoColuna     = DadosAcao->numColuna(Alvo->Posicao);

        byte BoxLinha       = DadosAcao->numLinha(snake->Corpo[snake->Arrasto].Posicao);
        byte BoxColuna      = DadosAcao->numColuna(snake->Corpo[snake->Arrasto].Posicao);

        if( AlvoColuna < BoxColuna ) {
            //Alvo a esquerda

            if(DadosAcao->numColuna(snake->Corpo[snake->Arrasto - 1].Posicao) == (BoxColuna  - 1)) {

                if(AlvoLinha < BoxLinha) {
                    return eBoxPosicao::boxTop;
                } 
                return eBoxPosicao::boxBottom;
            }

            return eBoxPosicao::boxLeft;

        } else if( AlvoColuna > BoxColuna ) {
            // Alvo a Direita

            if(DadosAcao->numColuna(snake->Corpo[snake->Arrasto - 1].Posicao) == (BoxColuna + 1)) {

                if(AlvoLinha < BoxLinha) {
                    return eBoxPosicao::boxTop;
                } 
                return eBoxPosicao::boxBottom;
            }

            return eBoxPosicao::boxRight;


        } else if( AlvoLinha  < BoxLinha ) {
            // Alvo a Baixo
            return eBoxPosicao::boxTop;
        } 

        return eBoxPosicao::boxBottom;

    }

}

eBoxPosicao AcaoBox::deslocamentoBox(BoxDadosAcao *DadosAcao, alvo_t *Alvo, snake_t *snake, eBoxMovimentoSnake movimento) {

    if(Alvo->Posicao == snake->Corpo[snake->Arrasto].Posicao) {

        return eBoxPosicao::boxNoAlvo;

    } else {

        byte AlvoLinha      = DadosAcao->numLinha(Alvo->Posicao);
        byte AlvoColuna     = DadosAcao->numColuna(Alvo->Posicao);

        byte BoxLinha       = DadosAcao->numLinha(snake->Corpo[snake->Arrasto].Posicao);
        byte BoxColuna      = DadosAcao->numColuna(snake->Corpo[snake->Arrasto].Posicao);

        if(movimento == eBoxMovimentoSnake::boxColuna) {

            // Movimentação baseado em Coluna

            if( AlvoColuna < BoxColuna ) {

                //Alvo a esquerda
                return eBoxPosicao::boxLeft;

            } else if( AlvoColuna > BoxColuna ) {

                // Alvo a Direita
                return eBoxPosicao::boxRight;

            } else if( AlvoLinha  < BoxLinha ) {
                // Alvo a Baixo
                return eBoxPosicao::boxTop;
            } 

            return eBoxPosicao::boxBottom;

        } else {

            // Movimentação baseado em linha

            if( AlvoLinha < BoxLinha ) {

                //Alvo acima
                return eBoxPosicao::boxTop;

            } else if( AlvoLinha > BoxLinha ) {

                // Alvo abaixo
                return eBoxPosicao::boxBottom;

            } else if( AlvoColuna < BoxColuna ) {

                // Alvo a esquerda
                return eBoxPosicao::boxLeft;
            } 

            return eBoxPosicao::boxRight;

        }

    }

}

box_t AcaoBox::getPosicaoBoxByAlvo(BoxDadosAcao *DadosAcao, box_t *BoxAtual, eBoxPosicao DeslocamentoAlvo) {

    switch (DeslocamentoAlvo)
    {
    case eBoxPosicao::boxNoAlvo:

        return *BoxAtual;
        break;

    default:

        byte    BoxLinha        = DadosAcao->numLinha(BoxAtual->Posicao);
        byte    BoxColuna       = DadosAcao->numColuna(BoxAtual->Posicao);
        box_t   BoxNovo         = {0, {0, 0, 0}};

        switch (DeslocamentoAlvo)
        {
        case eBoxPosicao::boxLeft:

            BoxColuna--;
            break;

        case eBoxPosicao::boxRight:

            BoxColuna++;
            break;

        case eBoxPosicao::boxBottom:

            BoxLinha++;
            break;

        default:        //Top

            BoxLinha--;
            break;
        }

        BoxNovo.Posicao =   (linCol)DadosAcao->converteLinhaColuna(BoxLinha, BoxColuna);
        BoxNovo.RGB     =   getBoxRGB(DadosAcao, BoxNovo.Posicao);

        return BoxNovo;

        break;
    }

}

void AcaoBox::moveSnake(BoxDadosAcao *DadosAcao, snake_t snake)  {

    byte    Linha                   = 0;
    byte    Coluna                  = 0;
    byte    R                       = DadosAcao->getGammaR();
    byte    G                       = DadosAcao->getGammaG();
    byte    B                       = DadosAcao->getGammaB();

    float   PercentualCalibrador    = ((float)(100.0 / (snake.Arrasto + 1)) / 100.0);
    float   Percentual              = 0.05L;

    float  RShow           = snake.CorFundo.R;
    float  GShow           = snake.CorFundo.G;
    float  BShow           = snake.CorFundo.B;

    //Efeito lesma deixa rastro
    // float  RShow           = R * Percentual;
    // float  GShow           = G * Percentual;
    // float  BShow           = B * Percentual;

    for (byte posicao = 0; posicao < snake.Arrasto; posicao++)
    {

        Linha = DadosAcao->numLinha(snake.Corpo[posicao].Posicao);
        Coluna = DadosAcao->numColuna(snake.Corpo[posicao].Posicao);

        _Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), _Leds.Color(GShow, RShow, BShow));


        RShow = R * Percentual;
        GShow = G * Percentual;
        BShow = B * Percentual;

        Percentual = Percentual + PercentualCalibrador;

    }
    
    Linha = DadosAcao->numLinha(snake.Corpo[snake.Arrasto].Posicao);
    Coluna = DadosAcao->numColuna(snake.Corpo[snake.Arrasto].Posicao);

    _Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), _Leds.Color(G, R, B));
    
    showLeds(150);

}

void AcaoBox::moveSnakeToca(BoxDadosAcao *DadosAcao, snake_t *snake, byte FimArrasto) {

    byte    Linha                   = 0;
    byte    Coluna                  = 0;

    float   PercentualCalibrador    = ((float)(100.0 / (snake->Arrasto + 1)) / 100.0);
    float   Percentual              = 100.0L - PercentualCalibrador * FimArrasto;

    byte    R                       = DadosAcao->getGammaR();
    byte    G                       = DadosAcao->getGammaG();
    byte    B                       = DadosAcao->getGammaB();

    float  RShow                    = R;
    float  GShow                    = G;
    float  BShow                    = B;

    for (byte posicao = snake->Arrasto; posicao <= FimArrasto + 1; posicao++)
    {

        RShow = R * Percentual;
        GShow = G * Percentual;
        BShow = B * Percentual;

        Linha = DadosAcao->numLinha(snake->Corpo[posicao].Posicao);
        Coluna = DadosAcao->numColuna(snake->Corpo[posicao].Posicao);

        _Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), _Leds.Color(GShow, RShow, BShow));

        Percentual = Percentual - PercentualCalibrador;

    }

    Linha = DadosAcao->numLinha(snake->Corpo[FimArrasto].Posicao);
    Coluna = DadosAcao->numColuna(snake->Corpo[FimArrasto].Posicao);

    _Leds.setPixelColor(PosicaoBoxCellInvertido(Linha, Coluna), _Leds.Color(snake->CorFundo.G, snake->CorFundo.R, snake->CorFundo.B));
    
    showLeds(150);

}

#pragma endregion


