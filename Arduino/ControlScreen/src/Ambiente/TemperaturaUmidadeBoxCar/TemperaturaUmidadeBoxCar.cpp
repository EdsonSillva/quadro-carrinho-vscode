

#include "TemperaturaUmidadeBoxCar.h"


TemperaturaUmidadeBoxCar::TemperaturaUmidadeBoxCar() { }

TemperaturaUmidadeBoxCar::~TemperaturaUmidadeBoxCar() { }

/**
 * Metodo para indicar o pino analógico a ser usado pelo DHT
 * 
 * @param Pino Indicar um pino analógico a ser usado pelo DHT
 * 
 */
void TemperaturaUmidadeBoxCar::setPinoConexao(byte Pino){
    _pinoConexao = Pino;
}

void inline TemperaturaUmidadeBoxCar::readDHT() {
    _dht.read11(_pinoConexao);
}

double TemperaturaUmidadeBoxCar::getTemperaturaOnDHT() {
    readDHT();
    return _dht.temperature;
}

double TemperaturaUmidadeBoxCar::getUmidadeOnDHT() {
    readDHT();
    return _dht.humidity;
}

bool TemperaturaUmidadeBoxCar::ErroReadOnDHT11() {
    if(isnan(_dht.temperature || _dht.humidity)) return true;
    else return false;    
}
