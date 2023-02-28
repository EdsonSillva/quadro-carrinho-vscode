


#include "BoxBuzzerCar.h"


BoxBuzzerCar::BoxBuzzerCar() { }

BoxBuzzerCar::~BoxBuzzerCar() { }

/**
 * Metodo para indicar o pino digital a ser usado pelo Buzzer
 * 
 * @param Pino Indicar um pino digital a ser usado pelo Buzzer
 * 
 */
void BoxBuzzerCar::setPinoConexao(byte Pino){
    _pinoConexao = Pino;
}
void BoxBuzzerCar::iniciarBuzzer() {
   
    pinMode(_pinoConexao, OUTPUT);          // Habilita o pino para utilização do Buzzer    
    delayMicroseconds(100);                 // Necessário para aguardar a inicialização do componente anterior.                 
}

void BoxBuzzerCar::beepBuzzer(unsigned int frequencia = 14000, unsigned long duracao = 6) {
    tone(_pinoConexao, frequencia, duracao);
}

