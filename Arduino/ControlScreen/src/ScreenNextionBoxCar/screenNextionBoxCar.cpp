
#include "screenNextionBoxCar.h"


screenNextionBoxCar::screenNextionBoxCar() { }

screenNextionBoxCar::~screenNextionBoxCar() { }

bool screenNextionBoxCar::iniciarNextion() {

    bool Ok = false;
    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
    delay(500);
    return Ok;

}

bool screenNextionBoxCar::existeDadoNoNextion() {
    return nexSerial.available() > 0 ? true : false;
}

void screenNextionBoxCar::DataHoraOnScreen(byte *pDH, byte *pMM, byte *pAS) {

    uint32_t    value =   -1;

    NexSlider   sDH   =   NexSlider(_tela.ConfigDataHora, _objeto.IDDH, "sDH");
    NexSlider   sMM   =   NexSlider(_tela.ConfigDataHora, _objeto.IDMM, "sMM");
    NexSlider   sAS   =   NexSlider(_tela.ConfigDataHora, _objeto.IDAS, "sAS");

    sDH.getValue(&value),   *pDH = (byte)value;
    sMM.getValue(&value),   *pMM = (byte)value;
    sAS.getValue(&value);

    if (value < 60) {           // Tela no Screen em Configuração de Hora
        *pAS = (byte)value;
    } else {                    // Tela no Screen em Configuração de Data
        if (value < 2000) 
            _Milenio = 1900;
        else 
            _Milenio = 2000;

        *pAS = (byte)(value - _Milenio);
    }
}

int screenNextionBoxCar::getMilenio() {
    return _Milenio;
}

void screenNextionBoxCar::setVarNextion(char VarGlobal[], int TextoLength, String NomeVar) {

    for(int i=0;i<=TextoLength;i++) {
        VarGlobal[i] = NomeVar.charAt(i);
    }
    VarGlobal[TextoLength] = '\0';    // Indica fim do array de char
}

byte screenNextionBoxCar::getAcaoOnScreen() {

    uint32_t    value       = 0;
    NexVariable AcaoArduino = NexVariable(_tela.Global, _objeto.IDAcaoArduino, "");

    AcaoArduino.getValueByID(&value);
    
    return (byte)value;
}

byte screenNextionBoxCar::getEstadoAcaoOnScreen() {

    uint32_t    value       = 0;
    NexVariable AcaoArduino = NexVariable(_tela.Global, _objeto.IDAcaoOn, "");

    AcaoArduino.getValueByID(&value);
    
    return (byte)value;
}


byte screenNextionBoxCar::getAcaoTemaOnScreen() {

    uint32_t    value           = 0;
    NexVariable AcaoTemaArduino = NexVariable(_tela.ConfigBoxFixo, _objeto.IDAcaoTema, "");

    AcaoTemaArduino.getValueByID(&value);
    
    return (byte)value;
}

byte screenNextionBoxCar::getStandByOnScreen() {

    uint32_t    value   = 0;     //Se não retorna nada informa que teve problemas em obter o valor da variável stand by na tela
    NexVariable StandBy = NexVariable(_tela.Global, _objeto.IDStandBy, "");

    if ((bool)StandBy.getValueByID(&value) == true) {
        return (byte)value;    
    }

    return (byte)255;    
}

void screenNextionBoxCar::setAcaoOnScreen(uint32_t Acao) {

  NexVariable AcaoArduino = NexVariable(_tela.Global, _objeto.IDAcaoArduino, "");
  AcaoArduino.setValueByID(Acao);

}

void screenNextionBoxCar::setExecArduinoOnScreen(eCodeExec CodeExec) {

    uint32_t Code = (uint32_t)CodeExec;
        
    NexVariable ArduinoExec = NexVariable(_tela.Global, _objeto.IDArduinoExec, ""); 
    ArduinoExec.setValueByID(Code);

}

void screenNextionBoxCar::getRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao) {

    uint32_t    value       = -1;
    byte        R           =  0;
    byte        G           =  0;
    byte        B           =  0;
    byte        Brilho      =  0;

    NexVariable nR          = NexVariable(_tela.Global,  _objeto.IDR,       "");
    NexVariable nG          = NexVariable(_tela.Global,  _objeto.IDG,       "");
    NexVariable nB          = NexVariable(_tela.Global,  _objeto.IDB,       "");
    NexVariable nBrilho     = NexVariable(_tela.Global,  _objeto.IDBrilho,  "");

    nR.getValueByID(&value),        R      = (byte)value;
    nG.getValueByID(&value),        G      = (byte)value;
    nB.getValueByID(&value),        B      = (byte)value;
    nBrilho.getValueByID(&value),   Brilho = (byte)value;

    DadosAcao->setRGBB(R, G, B, Brilho);

}

void screenNextionBoxCar::setDadosRGBBOnScreen(BoxDadosAcao *DadosAcao, bool EEPROMDisp) {

    byte R      = DadosAcao->getR();
    byte G      = DadosAcao->getG();
    byte B      = DadosAcao->getB();
    byte Disp   = EEPROMDisp = true ? 1 : 0;

    NexVariable eepromDisp = NexVariable(_tela.Global, _objeto.IDEEPROMDisp, "");
    eepromDisp.setValueByID((uint32_t)Disp);

    NexVariable vaR = NexVariable(_tela.Global, _objeto.IDR, "");
    vaR.setValueByID((uint32_t)R);

    NexVariable vaG = NexVariable(_tela.Global, _objeto.IDG, "");
    vaG.setValueByID((uint32_t)G);

    NexVariable vaB = NexVariable(_tela.Global, _objeto.IDB, "");
    vaB.setValueByID((uint32_t)B);

    NexVariable vaBrilho = NexVariable(_tela.Global, _objeto.IDBrilho, "");
    vaBrilho.setValueByID((uint32_t)DadosAcao->getBrilho());

    NexVariable vaRGBNextion = NexVariable(_tela.Global, _objeto.IDCorRGB, "");

    uint32_t RGBNextion = (R / 8 * 2048) + (G / 4 *32) + (B / 8);   // Cálculo necessário porque o Nextion trata a cor RGB diferente
    vaRGBNextion.setValueByID(RGBNextion);

}

byte screenNextionBoxCar::getDoWOnScreen(){

    uint32_t    value   = 0;
    NexSlider   sDoW    = NexSlider(_tela.ConfigDataHora, _objeto.IDDoW, "sDoW");

    sDoW.getValue(&value);
    return (byte)value;

}

void screenNextionBoxCar::getDataOnScreen(byte *pDia, byte *pMes, byte *pAno, byte *DoW) {

    byte  bDH,  bMM,  bAS, bDoW;

    DataHoraOnScreen(&bDH, &bMM, &bAS);
    bDoW    = getDoWOnScreen();
    *pDia   = bDH;
    *pMes   = bMM;
    *pAno   = bAS;
    *DoW    = bDoW;

}

void screenNextionBoxCar::getHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {

    byte  bDH,  bMM,  bAS;

    DataHoraOnScreen(&bDH, &bMM, &bAS);
    *Hora      = bDH;
    *Minuto    = bMM;
    *Segundo   = bAS;

}

void screenNextionBoxCar::getTextoOnScreen(char Texto[], byte *pQtdeChar) {

  uint32_t    value         = -1;
  NexVariable txtTexto      = NexVariable(_tela.Global, _objeto.IDTexto,      "");
  NexVariable txtTextoQtde  = NexVariable(_tela.Global, _objeto.IDTextoQtde,  "");

  txtTextoQtde.getValueByID(&value);
  *pQtdeChar = (byte)value;

  memset(Texto, 0, sizeof(Texto));      // Inicializa o array de char
  txtTexto.getTextByID(Texto, value);

}

#pragma region Show informações de data

/* @brief deprecated @deprecated */
void screenNextionBoxCar::showDataOnScreen(byte *Dia, byte *Mes, byte *Ano, byte *DoW) {

    NexVariable nDia    = NexVariable(_tela.Global,  _objeto.IDDia,         "");
    NexVariable nMes    = NexVariable(_tela.Global,  _objeto.IDMes,         "");
    NexVariable nAno    = NexVariable(_tela.Global,  _objeto.IDAno,         "");
    NexVariable nDoW    = NexVariable(_tela.Global,  _objeto.IDDoWGlobal,   "");
    
    nDia.setValueByID((uint32_t)*Dia);
    nMes.setValueByID((uint32_t)*Mes);
    nAno.setValueByID((uint32_t)(_Milenio + *Ano));  
    
    nDoW.setValueByID((uint32_t)*DoW);

}

void screenNextionBoxCar::showDataOnScreen(eTipoDataInfo tipoInfo, byte *valor) {

    byte    idScreen        = _tela.Global;
    byte    idObjeto        = 0;
    byte    valorRecebido   = *valor;

    switch (tipoInfo) {

        case eTipoDataInfo::DiaInfo:
            idObjeto = _objeto.IDDia;
        break;

        case eTipoDataInfo::MesInfo:
            idObjeto = _objeto.IDMes;
        break;

        case eTipoDataInfo::AnoInfo:
            idObjeto = _objeto.IDAno;
            valorRecebido = (_Milenio + valorRecebido);
        break;

        case eTipoDataInfo::DoWorkInfo:
            idObjeto = _objeto.IDDoWGlobal;
        break;

    }

    showInfoOnScreen(&idScreen, &idObjeto, &valorRecebido);

    // NexVariable nDia    = NexVariable(_tela.Global,  _objeto.IDDia,         "");
    // NexVariable nMes    = NexVariable(_tela.Global,  _objeto.IDMes,         "");
    // NexVariable nAno    = NexVariable(_tela.Global,  _objeto.IDAno,         "");
    // NexVariable nDoW    = NexVariable(_tela.Global,  _objeto.IDDoWGlobal,   "");
    // nDia.setValueByID((uint32_t)*Dia);
    // nMes.setValueByID((uint32_t)*Mes);
    // nAno.setValueByID((uint32_t)(_Milenio + *Ano));  
    // nDoW.setValueByID((uint32_t)*DoW);

}

#pragma endregion Show informações de data

#pragma region Show informações de hora

/* @brief deprecated @deprecated */
void screenNextionBoxCar::showHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {
  
  NexVariable nHora    = NexVariable(_tela.Global, _objeto.IDHora, "");
  NexVariable nMinuto  = NexVariable(_tela.Global, _objeto.IDMin, "");
  NexVariable nSegundo = NexVariable(_tela.Global, _objeto.IDSeg, "");

  nHora.setValueByID((uint32_t)*Hora);
  nMinuto.setValueByID((uint32_t)*Minuto);
  nSegundo.setValueByID((uint32_t)*Segundo);

}

void screenNextionBoxCar::showHoraOnScreen(eTipoTempoInfo tipoInfo, byte *valor) {

    byte    idScreen    = _tela.Global;
    byte    idObjeto    = 0;

    switch (tipoInfo) {

        case eTipoTempoInfo::HoraInfo:
            idObjeto = _objeto.IDHora;
        break;

        case eTipoTempoInfo::MinutoInfo:
            idObjeto = _objeto.IDMin;
        break;

        case eTipoTempoInfo::SegundoInfo:
            idObjeto = _objeto.IDSeg;
        break;

    }

    showInfoOnScreen(&idScreen, &idObjeto, valor);

//   NexVariable nHora    = NexVariable(_tela.Global, _objeto.IDHora, "");
//   NexVariable nMinuto  = NexVariable(_tela.Global, _objeto.IDMin, "");
//   NexVariable nSegundo = NexVariable(_tela.Global, _objeto.IDSeg, "");
//   nHora.setValueByID((uint32_t)*Hora);
//   nMinuto.setValueByID((uint32_t)*Minuto);
//   nSegundo.setValueByID((uint32_t)*Segundo);

}

#pragma endregion Show informações de hora

#pragma region Show informações de Ambiente

 /* @brief Recebe um valor de temperatura do DHT11 e coloca na variável da tela do Nextion */
void screenNextionBoxCar::showTemperaturaOnScreen(byte *TemperaturaAmbiente) {  

    NexVariable nTemperatura = NexVariable(_tela.Global, _objeto.IDTemp, "");
    nTemperatura.setValueByID((uint32_t)*TemperaturaAmbiente);

}

 /* @brief Recebe um valor de umidade do DHT11 e coloca na variável da tela do Nextion */
void screenNextionBoxCar::showUmidadeOnScreen(byte *UmidadeAmbiente) {

    NexVariable nUmidade = NexVariable(_tela.Global, _objeto.IDUmidade, "");  
    nUmidade.setValueByID((uint32_t)*UmidadeAmbiente);

}

 /* @brief Recebe um valor de luminosidade do LDR e coloca na variável da tela do Nextion */
void screenNextionBoxCar::showLDROnScreen(byte *ValorSensor) {

    NexVariable LDR = NexVariable(_tela.Global, _objeto.IDLDR, "");
    LDR.setValueByID((uint32_t)*ValorSensor);
      
}

#pragma endregion Show informações de Ambiente

#pragma region Show informações de temperatura do sistema

 /* @brief Le a temperatura do sistema. O sensor fica no device DS3231 */
void screenNextionBoxCar::showTempSysOnScreen(byte *TemperaturaSys) {

    NexVariable nTempSys = NexVariable(_tela.Global, _objeto.IDTempSys, "");
    nTempSys.setValueByID((uint32_t)*TemperaturaSys);

}

#pragma endregion

/* @brief Este metodo trabalha com o objeto NexVariable */
void screenNextionBoxCar::showInfoOnScreen(uint8_t *idScreen, uint8_t *idObjeto, byte *valor) {

    NexVariable objNextion = NexVariable(*idScreen,  *idObjeto,  "");
    objNextion.setValueByID((uint32_t)*valor);

}

/* @brief Lê a variável Beep do screem para saber se emite Beep ou não */
bool screenNextionBoxCar::getBeepOnScreen() {

    uint32_t      value   = 0;
    NexVariable   nBeep   = NexVariable(_tela.Global, _objeto.IDBeep, "");

    nBeep.getValueByID(&value);
    if((bool)value == 1)
        return true;
    return false;

}

void screenNextionBoxCar::setBoxesOnScreen(const char Boxes[]) {

    NexVariable txtBoxes      = NexVariable(_tela.ConfigBoxFixo, _objeto.IDBoxes,      "");
    txtBoxes.setTextByID(Boxes);

}

byte screenNextionBoxCar::getSizeBoxesOnScreen() {

    uint32_t    value       = -1;
    NexVariable BoxesSize   = NexVariable(_tela.ConfigBoxFixo, _objeto.IDSizeBoxesLC,   "");

    BoxesSize.getValueByID(&value);
    return (byte)value;

}

byte screenNextionBoxCar::getQtdeItensBoxesOnScreen() {

    uint32_t    value           = -1;
    NexVariable QtdeItensBoxes  = NexVariable(_tela.ConfigBoxFixo, _objeto.IDQtdeItensBox,   "");

    QtdeItensBoxes.getValueByID(&value);
    return (byte)value;

}

byte screenNextionBoxCar::getBoxesOnScreen(char Boxes[], byte sizeBoxes) {

    uint32_t    value       = sizeBoxes;
    NexVariable txtBoxes    = NexVariable(_tela.ConfigBoxFixo, _objeto.IDBoxesLinCol,   "");

    memset(Boxes, 0, sizeof(Boxes));      // Inicializa o array de char
    return (byte)txtBoxes.getTextByID(Boxes, value);

}

byte screenNextionBoxCar::getItemBoxesOnScreen(byte IDItemBox) {

    uint32_t    value       = -1;
    NexVariable itemBox     = NexVariable(_tela.ConfigBoxFixo, IDItemBox,   "");

    itemBox.getValueByID(&value);
    return (byte)value;

}




