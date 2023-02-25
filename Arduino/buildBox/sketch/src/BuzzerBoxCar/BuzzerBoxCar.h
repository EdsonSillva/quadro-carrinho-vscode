#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\src\\BuzzerBoxCar\\BuzzerBoxCar.h"
/*
    Módulo para tratar saida de siom por um auto falante
    Pino: Digital 7
    
    Desenvolvido por Edson Silva
    Date: 21/07/18

*/

#ifndef __BUZZERBOXCAR_H__
#define __BUZZERBOXCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define    _pin_Buzzer_  7               // Pino de saida para uso do Buzzer

class BuzzerBoxCar
{
private:
    /* data */

    byte    _pinoConexao        = _pin_Buzzer_;

public:
    BuzzerBoxCar(/* args */);
    ~BuzzerBoxCar();

    void setPinoConexao(byte Pino);         // Usar pinos analógicos
    void iniciarBuzzer();
    void beepBuzzer(unsigned int frequencia = 14000, unsigned long duracao = 6);

};


#endif  // __BUZZERBOXCAR_H__
