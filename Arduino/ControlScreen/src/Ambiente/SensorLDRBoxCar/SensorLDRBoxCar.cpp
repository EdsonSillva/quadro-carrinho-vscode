

#include "SensorLDRBoxCar.h"


SensorLDRBoxCar::SensorLDRBoxCar() { }

SensorLDRBoxCar::~SensorLDRBoxCar() { }

void SensorLDRBoxCar::iniciarSensorLDR() {
    
    pinMode(_pinoConexao, INPUT);    // Habilita o pino para utilização do sensor 
}

/**
 * Metodo para indicar o pino analógico a ser usado pelo LDR
 * 
 * @param Pino Indicar um pino analógico a ser usado pelo LDR
 * 
 */
void SensorLDRBoxCar::setPinoConexao(byte Pino){
    _pinoConexao = Pino;
}

void SensorLDRBoxCar::setMinimoMaximo(byte Min, byte Max) {
    _Min = Min;
    _Max = Max;
}

int inline SensorLDRBoxCar::lerSensor() {
    return analogRead(_pinoConexao);
}

int SensorLDRBoxCar::getValorPuroOnLDR() {
    return lerSensor();    
}

int SensorLDRBoxCar::getValorMapOnLDR() {
    return map(lerSensor(), 0, 1023, _Min, _Max);
}

int SensorLDRBoxCar::getValorMapInvertidoOnLDR() {
    return (int)((int)_Max - getValorMapOnLDR());
}
