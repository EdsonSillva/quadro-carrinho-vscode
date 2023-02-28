/*
    Classe de suporte para a classe da memória EEPROM

    Data: 02/12/22
    Autor: Edson Silva

*/

#ifndef __PINOS_H__
#define __PINOS_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define _pino_usando_       11
#define _pino_alerta_       13

class Pinos
{
private:
    unsigned int _pinLedUsandoEEPROM        = _pino_usando_;
    unsigned int _pinLedAlerta              = _pino_alerta_;

public:
    Pinos();
    ~Pinos();
    void inicializar();
    void setPinos(byte pinoUsando, byte pinoAlerta);
    void setPinoLedUsandoEEPROM(byte pinoUsando);
    void setPinoLedAlerta(byte pinoAlerta);
    int getPinoLedUsandoEEPROM();
    int getPinoLedAlerta();

};

#endif  // __PINOS_H__