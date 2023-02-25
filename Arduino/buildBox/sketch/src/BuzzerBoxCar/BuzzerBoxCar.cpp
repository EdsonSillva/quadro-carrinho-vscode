#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\src\\BuzzerBoxCar\\BuzzerBoxCar.cpp"



#include "BuzzerBoxCar.h"


BuzzerBoxCar::BuzzerBoxCar(/* args */) { }

BuzzerBoxCar::~BuzzerBoxCar() { }

/**
 * Metodo para indicar o pino digital a ser usado pelo Buzzer
 * 
 * @param Pino Indicar um pino digital a ser usado pelo Buzzer
 * 
 */
void BuzzerBoxCar::setPinoConexao(byte Pino){
    _pinoConexao = Pino;
}
void BuzzerBoxCar::iniciarBuzzer() {
   
    // Serial.println(F("... BuzzerBoxCar::iniciarBuzzer()"));

    pinMode(_pinoConexao, OUTPUT);          // Habilita o pino para utilização do Buzzer    
    delayMicroseconds(100);                 // Necessário para aguardar a inicialização do componente anterior.                 
}

void BuzzerBoxCar::beepBuzzer(unsigned int frequencia = 14000, unsigned long duracao = 6) {
    tone(_pinoConexao, frequencia, duracao);
}

