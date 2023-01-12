
#include "screenNextionBoxCar.h"


screenNextionBoxCar::screenNextionBoxCar() { }

screenNextionBoxCar::~screenNextionBoxCar() { }

bool screenNextionBoxCar::iniciarNextion() {

    bool Ok = false;
    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
    delay(500);
    return Ok;

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

    NexVariable AcaoArduino = NexVariable(_tela.VarGlobais, _objeto.IDAcaoArduino, "");
    AcaoArduino.getValueByID(&value);
    
    return (byte)value;

}

byte screenNextionBoxCar::getStandByOnScreen() {

    uint32_t value = 1;     //Se não retorna nada mantem em stand by

    NexVariable StandBy = NexVariable(_tela.VarGlobais, _objeto.IDStandBy, "");  
    StandBy.getValueByID(&value);
    
    return (byte)value;    

}

void screenNextionBoxCar::setAcaoOnScreen(uint32_t Acao) {

  NexVariable AcaoArduino = NexVariable(_tela.VarGlobais, _objeto.IDAcaoArduino, "");
  AcaoArduino.setValueByID(Acao);

}

void screenNextionBoxCar::setExecArduinoOnScreen(eCodeExec CodeExec) {

    uint32_t Code = (uint32_t)CodeExec;
        
    NexVariable ArduinoExec = NexVariable(_tela.VarGlobais, _objeto.IDArduinoExec, ""); 
    ArduinoExec.setValueByID(Code);

}

void screenNextionBoxCar::setLDROnScreen(uint32_t ValorSensor) {

    NexVariable LDR = NexVariable(_tela.VarGlobais, _objeto.IDLDR, "");
    LDR.setValueByID(ValorSensor);
      
}

/* 
 * @deprecated Antiga
*/
void screenNextionBoxCar::getRGBBrilhoOnScreen(byte *R, byte *G, byte *B, byte *Brilho) {

    uint32_t  value     = -1;

    NexVariable nR      = NexVariable(_tela.VarGlobais,  _objeto.IDR,       "");
    NexVariable nG      = NexVariable(_tela.VarGlobais,  _objeto.IDG,       "");
    NexVariable nB      = NexVariable(_tela.VarGlobais,  _objeto.IDB,       "");
    NexVariable nBrilho = NexVariable(_tela.VarGlobais,  _objeto.IDBrilho,  "");

    nR.getValueByID(&value),        *R      = (byte)value;
    nG.getValueByID(&value),        *G      = (byte)value;
    nB.getValueByID(&value),        *B      = (byte)value;
    nBrilho.getValueByID(&value),   *Brilho = (byte)value;      

}

void screenNextionBoxCar::getRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao) {

    uint32_t    value       = -1;
    byte        R           =  0;
    byte        G           =  0;
    byte        B           =  0;
    byte        Brilho      =  0;

    NexVariable nR      = NexVariable(_tela.VarGlobais,  _objeto.IDR,       "");
    NexVariable nG      = NexVariable(_tela.VarGlobais,  _objeto.IDG,       "");
    NexVariable nB      = NexVariable(_tela.VarGlobais,  _objeto.IDB,       "");
    NexVariable nBrilho = NexVariable(_tela.VarGlobais,  _objeto.IDBrilho,  "");

    nR.getValueByID(&value),        R      = (byte)value;
    nG.getValueByID(&value),        G      = (byte)value;
    nB.getValueByID(&value),        B      = (byte)value;
    nBrilho.getValueByID(&value),   Brilho = (byte)value;

    DadosAcao->setRGBB(R, G, B, Brilho);

}

/* 
    @deprecated Antigo 
*/
void screenNextionBoxCar::setCodeRGBBrilhoOnScreen(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {
  
    NexVariable vaCode = NexVariable(_tela.VarGlobais, _objeto.IDCode, "");
    vaCode.setValueByID((uint32_t)CodeAcao);

    NexVariable vaR = NexVariable(_tela.VarGlobais, _objeto.IDR, "");
    vaR.setValueByID((uint32_t)R);

    NexVariable vaG = NexVariable(_tela.VarGlobais, _objeto.IDG, "");
    vaG.setValueByID((uint32_t)G);

    NexVariable vaB = NexVariable(_tela.VarGlobais, _objeto.IDB, "");
    vaB.setValueByID((uint32_t)B);

    NexVariable vaBrilho = NexVariable(_tela.VarGlobais, _objeto.IDBrilho, "");
    vaBrilho.setValueByID((uint32_t)Brilho);

    NexVariable vaRGBNextion = NexVariable(_tela.VarGlobais, _objeto.IDCorRGB, "");

    uint32_t RGBNextion = (R / 8 * 2048) + (G / 4 *32) + (B / 8);   // Cálculo necessário porque o Nextion trata a cor RGB diferente
    vaRGBNextion.setValueByID(RGBNextion);

}


void screenNextionBoxCar::setCodeRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao) {

    byte R      = DadosAcao->getR();
    byte G      = DadosAcao->getG();
    byte B      = DadosAcao->getB();

    NexVariable vaCode = NexVariable(_tela.VarGlobais, _objeto.IDCode, "");
    vaCode.setValueByID((uint32_t)DadosAcao->getCodeAcao());

    NexVariable vaR = NexVariable(_tela.VarGlobais, _objeto.IDR, "");
    vaR.setValueByID((uint32_t)R);

    NexVariable vaG = NexVariable(_tela.VarGlobais, _objeto.IDG, "");
    vaG.setValueByID((uint32_t)G);

    NexVariable vaB = NexVariable(_tela.VarGlobais, _objeto.IDB, "");
    vaB.setValueByID((uint32_t)B);

    NexVariable vaBrilho = NexVariable(_tela.VarGlobais, _objeto.IDBrilho, "");
    vaBrilho.setValueByID((uint32_t)DadosAcao->getBrilho());

    NexVariable vaRGBNextion = NexVariable(_tela.VarGlobais, _objeto.IDCorRGB, "");

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

  NexVariable txtTexto      = NexVariable(_tela.VarGlobais, _objeto.IDTexto,      "");
  NexVariable txtTextoQtde  = NexVariable(_tela.VarGlobais, _objeto.IDTextoQtde,  "");

  txtTextoQtde.getValueByID(&value);
  *pQtdeChar = (byte)value;

  memset(Texto, 0, sizeof(Texto));      // Inicializa o array de char
  txtTexto.getTextByID(Texto, value);

}

void screenNextionBoxCar::ShowDataOnScreen(byte *Dia, byte *Mes, byte *Ano, byte *DoW) {

    //    byte       Dia, Mes, Ano, DoW;

    NexVariable nDia    = NexVariable(_tela.VarGlobais,  _objeto.IDDia, "");
    NexVariable nMes    = NexVariable(_tela.VarGlobais,  _objeto.IDMes, "");
    NexVariable nAno    = NexVariable(_tela.VarGlobais,  _objeto.IDAno, "");
    NexVariable nDoW    = NexVariable(_tela.VarGlobais,  _objeto.IDDoWGlobal, "");
    
    //getDataOnDS3231(Dia, Mes, Ano, DoW, &_Milenio);

    nDia.setValueByID((uint32_t)*Dia);
    nMes.setValueByID((uint32_t)*Mes);
    nAno.setValueByID((uint32_t)(_Milenio + *Ano));  
    
    nDoW.setValueByID((uint32_t)*DoW);

}

void screenNextionBoxCar::ShowHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo) {
  
  //byte    Hora, Minuto, Segundo;
    
  NexVariable nHora    = NexVariable(_tela.VarGlobais, _objeto.IDHora, "");
  NexVariable nMinuto  = NexVariable(_tela.VarGlobais, _objeto.IDMin, "");
  NexVariable nSegundo = NexVariable(_tela.VarGlobais, _objeto.IDSeg, "");

  // getHoraOnDS3231(&Hora, &Minuto, &Segundo);

  nHora.setValueByID((uint32_t)*Hora);
  nMinuto.setValueByID((uint32_t)*Minuto);
  nSegundo.setValueByID((uint32_t)*Segundo);

}

/*********************************************************************
 * Le a variável Beep do Screen
 *********************************************************************/
bool screenNextionBoxCar::getBeepOnScreen() {

    uint32_t      value   =   0;

    NexVariable   nBeep   =   NexVariable(_tela.VarGlobais, _objeto.IDBeep, "");

    nBeep.getValueByID(&value);
    if((bool)value == 1)
        return true;
    return false;

}

 /*********************************************************************
  * Le a temperatura do sistema. O sensor fica no device DS3231
  *********************************************************************/
void screenNextionBoxCar::ShowTempSysOnScreen(int TemperaturaSys) {

    NexVariable nTempSys = NexVariable(_tela.VarGlobais, _objeto.IDTempSys, "");

    // nTempSys.setValueByID(getTemperaturaSysOnDS3231());
    nTempSys.setValueByID((uint32_t)TemperaturaSys);

}

 /************************************************************************ 
  * Le a temperatura do device DH11 e coloca o valor na variável da Tela
  ************************************************************************/
void screenNextionBoxCar::ShowTemperaturaOnScreen(double TemperaturaAmbiente) {  

    //uint32_t ValorSensor = (uint32_t)getTemperaturaOnDHT();
    
    NexVariable nTemperatura = NexVariable(_tela.VarGlobais, _objeto.IDTemp, "");
    nTemperatura.setValueByID((uint32_t)TemperaturaAmbiente);

}

 /********************************************************************** 
  * Le a humidade do device DH11 e coloca o valor na variável  da Tela
  **********************************************************************/
void screenNextionBoxCar::ShowHumidadeOnScreen(double HumidadeAmbiente) {

  //uint32_t ValorSensor = (uint32_t)getHumidadeOnDHT();
  
  NexVariable nHumidade = NexVariable(_tela.VarGlobais, _objeto.IDHumidade, "");  
  nHumidade.setValueByID((uint32_t)HumidadeAmbiente);

}










