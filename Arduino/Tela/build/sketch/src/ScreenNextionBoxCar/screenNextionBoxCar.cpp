#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\ScreenNextionBoxCar\\screenNextionBoxCar.cpp"

#include "screenNextionBoxCar.h"


screenNextionBoxCar::screenNextionBoxCar(/* args */) { }

screenNextionBoxCar::~screenNextionBoxCar() { }


bool screenNextionBoxCar::iniciarNextion() {

    bool Ok = false;
    Ok = nexInit();                                        // Necessário usar esta função para estabelecer a conexão com a tela
    delay(500);
    return Ok;

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