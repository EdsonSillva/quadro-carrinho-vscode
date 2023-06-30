

#include "TemperaturaHumidadeBoxCar.h"


TemperaturaHumidadeBoxCar::TemperaturaHumidadeBoxCar() { }

TemperaturaHumidadeBoxCar::~TemperaturaHumidadeBoxCar() { }

/**
 * Metodo para indicar o pino analógico a ser usado pelo DHT
 * 
 * @param Pino Indicar um pino analógico a ser usado pelo DHT
 * 
 */
void TemperaturaHumidadeBoxCar::setPinoConexao(byte Pino){
    _pinoConexao = Pino;
}

void inline TemperaturaHumidadeBoxCar::readDHT() {
    _dht.read11(_pinoConexao);
}

double TemperaturaHumidadeBoxCar::getTemperaturaOnDHT() {
    readDHT();
    return _dht.temperature;
}

double TemperaturaHumidadeBoxCar::getHumidadeOnDHT() {
    readDHT();
    return _dht.humidity;
}

bool TemperaturaHumidadeBoxCar::ErroReadOnDHT11() {
    if(isnan(_dht.temperature || _dht.humidity)) return true;
    else return false;    
}
