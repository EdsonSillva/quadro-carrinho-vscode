/*
    Metodos da classe de controle da memória EEPROM usada pelos dois arduinos

    Arquitetura: I2C - Utiliza os pinos SDA(4) e SCL(5)
    
    Data: 01/06/19
    Autor: Edson Silva

*/

#include <BoxEEPROM.h>

/**
 * Este construtor utiliza os pinos padrões de 'uso' e 'alerta'
 * definidos na classe Pinos.
*/
BoxEEPROM::BoxEEPROM() {
    _som = BoxBuzzerCar();
 }

BoxEEPROM::BoxEEPROM(BoxBuzzerCar som) {
    _som = som;
 }

BoxEEPROM::BoxEEPROM(int pinoUsando, int pinoAlerta)
{
    _som = BoxBuzzerCar();
    _pinos.setPinos(pinoUsando, pinoAlerta);
}

BoxEEPROM::BoxEEPROM(Device device, int pinoUsando, int pinoAlerta) { 
    _som = BoxBuzzerCar();
    _device = device;
    _pinos.setPinos(pinoUsando, pinoAlerta);
}

BoxEEPROM::~BoxEEPROM() { }

void BoxEEPROM::inicializar() {
    
    Wire.begin();                           // Entra no barramento I2c e inicializa os pinos do I2c
    delay(10);                              // Aguarda a inicialização do Wire
    _pinos.inicializar();                   // Inicializa os pinos de uso e leitura da EEPROM
    delayMicroseconds(1000);                // Necessário para aguardar a inicialização do componente anterior.
    _som.iniciarBuzzer();                   // Inicializar a saida de som

}

bool BoxEEPROM::disponivel() {
    return _eepromDisponivel;
}

byte BoxEEPROM::getPinLedUso(){
    return (byte)_pinos.getPinoLedUsandoEEPROM();
}

void BoxEEPROM::alertaSonoroNaoResponde(){
    _som.beepBuzzer(_frequencia, _duracao);
    digitalWrite(_pinos.getPinoLedAlerta(), HIGH), delay(500);
    _som.beepBuzzer(_frequencia, _duracao);
    digitalWrite(_pinos.getPinoLedAlerta(), LOW), delay(200);
    _som.beepBuzzer(_frequencia, _duracao);
    digitalWrite(_pinos.getPinoLedAlerta(), HIGH), delay(500);
    _som.beepBuzzer(_frequencia, _duracao);
    digitalWrite(_pinos.getPinoLedAlerta(), LOW);
}

void BoxEEPROM::getDadosOnMemory(BoxDadosAcao *DadosAcao) {

    byte CodeAcao = 0, R = 0, G = 0, B = 0, Brilho = 0;

    digitalWrite(_pinos.getPinoLedUsandoEEPROM(), HIGH);

        CodeAcao  = lerEEPROM((int)_device.AddressCodeAcao);

        if(!_eepromDisponivel){

            alertaSonoroNaoResponde();

        } else {

            R         = lerEEPROM((int)_device.AddressR);
            G         = lerEEPROM((int)_device.AddressG);
            B         = lerEEPROM((int)_device.AddressB);
            Brilho    = lerEEPROM((int)_device.AddressBrilho);
        }
    
        DadosAcao->setCodeAcaoRGBB(CodeAcao, R, G, B, Brilho);
    
    digitalWrite(_pinos.getPinoLedUsandoEEPROM(),LOW);

}

void BoxEEPROM::setDadosOnMemory(BoxDadosAcao *DadosAcao) {

    DadosAcao->getR();

    digitalWrite(_pinos.getPinoLedUsandoEEPROM(), HIGH);
        gravarEEPROM((int)_device.AddressR, DadosAcao->getR());
        gravarEEPROM((int)_device.AddressG, DadosAcao->getG());
        gravarEEPROM((int)_device.AddressB, DadosAcao->getB());
        gravarEEPROM((int)_device.AddressBrilho, DadosAcao->getBrilho());
        gravarEEPROM((int)_device.AddressCodeAcao, DadosAcao->getCodeAcao());
    digitalWrite(_pinos.getPinoLedUsandoEEPROM(),LOW);

}

void BoxEEPROM::setTextoOnMemory(char Texto[], byte QtdeChar) {

    int Address   = _device.AddressIniTexto;                      // Pega o endereço inicial da mensagem

    gravarEEPROM((int)_device.AddressQtdeChar, QtdeChar);         // Grava o tamanho da Mensagem
    for(byte P = 0; P <= QtdeChar; P++) {
        gravarEEPROM((int)Address, Texto[P]);
        Address++;
    }

}

void BoxEEPROM::getTextoOnMemory(char Texto[], byte *pQtdeChar) {

    int Address   = _device.AddressIniTexto;                  // Pega o endereço inicial da mensagem
    int QtdeChar  = lerEEPROM((int)_device.AddressQtdeChar);          // Le o tamanho da Mensagem

    *pQtdeChar = QtdeChar;
    for(byte P = 0; P <= QtdeChar; P++) {
        Texto[P] = lerEEPROM((int)Address);
        Address++;
    }

}

byte BoxEEPROM::lerEEPROM(int offSet) {

    byte            Dado          = 0xFF;
    unsigned long   MaxWait       = millis() + 10000;        // Seta o tempo máximo de 10 segundos aguardando a resposta do device EEPROM
    bool            IsMaxWait     = false;
    
    _eepromDisponivel = true;

    startEEPROMsetOffSet(offSet);
    Wire.endTransmission();

    Wire.requestFrom(_device.getAddress(), 1);
    
        while(!Wire.available()){

            if(MaxWait < millis()){
                IsMaxWait = true;
                Dado = __CODE_EEPROM_NOT_AVAILABLE__;
                _eepromDisponivel = false;
                break; // Sai do loop
            }
        }

        if(!IsMaxWait) Dado = Wire.read();

        Wire.endTransmission();

    return Dado;

}

void BoxEEPROM::gravarEEPROM(int offSet, unsigned int Dado) {
    startEEPROMsetOffSet(offSet);
    Wire.write((byte)Dado);
    Wire.endTransmission();
    delay(5);

}

void BoxEEPROM::startEEPROMsetOffSet(unsigned int offSet) {
    Wire.beginTransmission((uint8_t)_device.getAddress());
        Wire.write( (int)(offSet >>    8) );
        Wire.write( (int)(offSet &  0xFF) );
}

