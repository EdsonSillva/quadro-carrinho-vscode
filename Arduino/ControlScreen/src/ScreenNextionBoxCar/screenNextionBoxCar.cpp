
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

    uint32_t value = 0;

    NexVariable AcaoArduino = NexVariable(_tela.Global, _objeto.IDAcaoArduino, "");
    AcaoArduino.getValueByID(&value);
    
    return (byte)value;
}

byte screenNextionBoxCar::getAcaoTemaOnScreen() {

    uint32_t value = 0;

    NexVariable AcaoTemaArduino = NexVariable(_tela.ConfigBoxFixo, _objeto.IDAcaoTema, "");
    AcaoTemaArduino.getValueByID(&value);
    
    return (byte)value;
}

byte screenNextionBoxCar::getStandByOnScreen() {

    uint32_t value = 0;     //Se não retorna nada informa que teve problemas em obter o valor da variável stand by na tela

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

void screenNextionBoxCar::setLDROnScreen(uint32_t ValorSensor) {

    NexVariable LDR = NexVariable(_tela.Global, _objeto.IDLDR, "");
    LDR.setValueByID(ValorSensor);
      
}

/* 
 * @deprecated Antiga
*/
// void screenNextionBoxCar::getRGBBrilhoOnScreen(byte *R, byte *G, byte *B, byte *Brilho) {

//     uint32_t  value     = -1;

//     NexVariable nR      = NexVariable(_tela.Global,  _objeto.IDR,       "");
//     NexVariable nG      = NexVariable(_tela.Global,  _objeto.IDG,       "");
//     NexVariable nB      = NexVariable(_tela.Global,  _objeto.IDB,       "");
//     NexVariable nBrilho = NexVariable(_tela.Global,  _objeto.IDBrilho,  "");

//     nR.getValueByID(&value),        *R      = (byte)value;
//     nG.getValueByID(&value),        *G      = (byte)value;
//     nB.getValueByID(&value),        *B      = (byte)value;
//     nBrilho.getValueByID(&value),   *Brilho = (byte)value;      

// }

void screenNextionBoxCar::getRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao) {

    uint32_t    value       = -1;
    byte        R           =  0;
    byte        G           =  0;
    byte        B           =  0;
    byte        Brilho      =  0;

    NexVariable nR      = NexVariable(_tela.Global,  _objeto.IDR,       "");
    NexVariable nG      = NexVariable(_tela.Global,  _objeto.IDG,       "");
    NexVariable nB      = NexVariable(_tela.Global,  _objeto.IDB,       "");
    NexVariable nBrilho = NexVariable(_tela.Global,  _objeto.IDBrilho,  "");

    nR.getValueByID(&value),        R      = (byte)value;
    nG.getValueByID(&value),        G      = (byte)value;
    nB.getValueByID(&value),        B      = (byte)value;
    nBrilho.getValueByID(&value),   Brilho = (byte)value;

    DadosAcao->setRGBB(R, G, B, Brilho);

}

/* 
    @deprecated Antigo 
*/
// void screenNextionBoxCar::setCodeRGBBrilhoOnScreen(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {
  
//     NexVariable vaCode = NexVariable(_tela.Global, _objeto.IDCode, "");
//     vaCode.setValueByID((uint32_t)CodeAcao);

//     NexVariable vaR = NexVariable(_tela.Global, _objeto.IDR, "");
//     vaR.setValueByID((uint32_t)R);

//     NexVariable vaG = NexVariable(_tela.Global, _objeto.IDG, "");
//     vaG.setValueByID((uint32_t)G);

//     NexVariable vaB = NexVariable(_tela.Global, _objeto.IDB, "");
//     vaB.setValueByID((uint32_t)B);

//     NexVariable vaBrilho = NexVariable(_tela.Global, _objeto.IDBrilho, "");
//     vaBrilho.setValueByID((uint32_t)Brilho);

//     NexVariable vaRGBNextion = NexVariable(_tela.Global, _objeto.IDCorRGB, "");

//     uint32_t RGBNextion = (R / 8 * 2048) + (G / 4 *32) + (B / 8);   // Cálculo necessário porque o Nextion trata a cor RGB diferente
//     vaRGBNextion.setValueByID(RGBNextion);

// }

void screenNextionBoxCar::setCodeRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao) {

    byte R      = DadosAcao->getR();
    byte G      = DadosAcao->getG();
    byte B      = DadosAcao->getB();

    NexVariable vaCode = NexVariable(_tela.Global, _objeto.IDCode, "");
    vaCode.setValueByID((uint32_t)DadosAcao->getCodeAcao());

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

    uint32_t    value =   0;

    NexSlider   sDoW   =   NexSlider(_tela.ConfigDataHora, _objeto.IDDoW, "sDoW");

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

  uint32_t    value =   -1;

  NexVariable txtTexto      = NexVariable(_tela.Global, _objeto.IDTexto,      "");
  NexVariable txtTextoQtde  = NexVariable(_tela.Global, _objeto.IDTextoQtde,  "");

  txtTextoQtde.getValueByID(&value);
  *pQtdeChar = (byte)value;

  memset(Texto, 0, sizeof(Texto));      // Inicializa o array de char
  txtTexto.getTextByID(Texto, value);

}

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

void screenNextionBoxCar::showHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {
  
  NexVariable nHora    = NexVariable(_tela.Global, _objeto.IDHora, "");
  NexVariable nMinuto  = NexVariable(_tela.Global, _objeto.IDMin, "");
  NexVariable nSegundo = NexVariable(_tela.Global, _objeto.IDSeg, "");

  nHora.setValueByID((uint32_t)*Hora);
  nMinuto.setValueByID((uint32_t)*Minuto);
  nSegundo.setValueByID((uint32_t)*Segundo);

}

/*********************************************************************
 * Le a variável Beep do Screen
 *********************************************************************/
bool screenNextionBoxCar::getBeepOnScreen() {

    uint32_t      value   =   0;

    NexVariable   nBeep   =   NexVariable(_tela.Global, _objeto.IDBeep, "");

    nBeep.getValueByID(&value);
    if((bool)value == 1)
        return true;
    return false;

}

 /*********************************************************************
  * Le a temperatura do sistema. O sensor fica no device DS3231
  *********************************************************************/
void screenNextionBoxCar::showTempSysOnScreen(int TemperaturaSys) {

    NexVariable nTempSys = NexVariable(_tela.Global, _objeto.IDTempSys, "");
    nTempSys.setValueByID((uint32_t)TemperaturaSys);

}

 /************************************************************************ 
  * Le a temperatura do device DH11 e coloca o valor na variável da Tela
  ************************************************************************/
void screenNextionBoxCar::showTemperaturaOnScreen(double TemperaturaAmbiente) {  

    NexVariable nTemperatura = NexVariable(_tela.Global, _objeto.IDTemp, "");
    nTemperatura.setValueByID((uint32_t)TemperaturaAmbiente);

}

 /********************************************************************** 
  * Le a humidade do device DH11 e coloca o valor na variável  da Tela
  **********************************************************************/
void screenNextionBoxCar::showHumidadeOnScreen(double HumidadeAmbiente) {

    NexVariable nHumidade = NexVariable(_tela.Global, _objeto.IDHumidade, "");  
    nHumidade.setValueByID((uint32_t)HumidadeAmbiente);

}

void screenNextionBoxCar::setBoxesOnScreen(const char Boxes[]) {

    NexVariable txtBoxes      = NexVariable(_tela.ConfigBoxFixo, _objeto.IDBoxes,      "");
    txtBoxes.setTextByID(Boxes);

}

byte screenNextionBoxCar::getSizeBoxesOnScreen() {

    uint32_t    value =   -1;

    NexVariable BoxesSize  = NexVariable(_tela.ConfigBoxFixo, _objeto.IDSizeBoxesLC,   "");

    BoxesSize.getValueByID(&value);
    return (byte)value;

}

byte screenNextionBoxCar::getQtdeItensBoxesOnScreen() {

    uint32_t    value =   -1;

    NexVariable QtdeItensBoxes  = NexVariable(_tela.ConfigBoxFixo, _objeto.IDQtdeItensBox,   "");

    QtdeItensBoxes.getValueByID(&value);
    return (byte)value;

}


byte screenNextionBoxCar::getBoxesOnScreen(char Boxes[], byte sizeBoxes) {

    uint32_t    value =   sizeBoxes;

    NexVariable txtBoxes      = NexVariable(_tela.ConfigBoxFixo, _objeto.IDBoxesLinCol,   "");

    // nexSerial.print(F("screenNextionBoxCar::getBoxesOnScreen:::"));
    // nexSerial.print(F("Boxxes={{")), nexSerial.print(Boxes);
    // nexSerial.print(F("}}"));
    // nexSerial.print(F("sizeBoxes={{")), nexSerial.print(sizeBoxes);
    // nexSerial.print(F("}}"));
    // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);

    memset(Boxes, 0, sizeof(Boxes));      // Inicializa o array de char
    return (byte)txtBoxes.getTextByID(Boxes, value);

    // nexSerial.print(F("screenNextionBoxCar::getTextByID:::"));
    // nexSerial.print(F("Boxxes={{")), nexSerial.print(Boxes);
    // nexSerial.print(F("}}"));
    // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);



}

byte screenNextionBoxCar::getItemBoxesOnScreen(byte IDItemBox) {

    uint32_t    value =   -1;

    NexVariable itemBox  = NexVariable(_tela.ConfigBoxFixo, IDItemBox,   "");

    itemBox.getValueByID(&value);
    return (byte)value;

}

// int  screenNextionBoxCar::setLenRestanteBoxes(byte QtdeBytes) {

//     NexVariable nTempSys = NexVariable(_tela.ConfigBoxFixo, _objeto.IDLenRestante, "");
//     nTempSys.setValueByID((uint32_t)QtdeBytes);

// }




