/*
    Módulo para tratar saida de siom por um auto falante
    Pino: Digital 7
    
    Desenvolvido por Edson Silva
    Date: 21/07/18

*/

#ifndef __BOXBUZZERCAR_H__
#define __BOXBUZZERCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define    _pin_Buzzer_  7               // Pino de saida para uso do Buzzer

class BoxBuzzerCar
{
private:

    byte    _pinoConexao        = _pin_Buzzer_;

public:
    BoxBuzzerCar();
    ~BoxBuzzerCar();

    void setPinoConexao(byte Pino);         // Usar pinos analógicos
    void iniciarBuzzer();
    void beepBuzzer(unsigned int frequencia = 14000, unsigned long duracao = 6);

};

#endif  // __BOXBUZZERCAR_H__
