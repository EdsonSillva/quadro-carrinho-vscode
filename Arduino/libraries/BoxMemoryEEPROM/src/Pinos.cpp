/*
    Metodos da classe de suporte para a classe da memória EEPROM

    Data: 02/12/22
    Autor: Edson Silva

*/

#include <Pinos.h>

Pinos::Pinos(){}
Pinos::~Pinos(){}

void Pinos::inicializar() {

    pinMode(_pinLedUsandoEEPROM,        OUTPUT);
    digitalWrite(_pinLedUsandoEEPROM,   LOW);
    pinMode(_pinLedAlerta,              OUTPUT);
    digitalWrite(_pinLedAlerta,         LOW);
    delayMicroseconds(5);                         // Aguarda as inicializações

}

void Pinos::setPinos(byte pinoUsando, byte pinoAlerta) {
    _pinLedUsandoEEPROM = pinoUsando;
    _pinLedAlerta = pinoAlerta;
}

void Pinos::setPinoLedUsandoEEPROM(byte pinoUsando) {
    _pinLedUsandoEEPROM = pinoUsando;
 }

void Pinos::setPinoLedAlerta(byte pinoAlerta) {
    _pinLedAlerta = pinoAlerta;
 }

int Pinos::getPinoLedUsandoEEPROM(){
    return _pinLedUsandoEEPROM;
}

int Pinos::getPinoLedAlerta(){
    return _pinLedAlerta;
}

