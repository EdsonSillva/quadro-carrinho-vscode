#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\BuzzerBoxCar\\BuzzerBoxCar.h"
/*
    Módulo para tratar saida de siom por um auto falante
    Pino: Digital 7
    
    Desenvolvido por Edson Silva
    Date: 21/07/18

*/

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
    void beepBuzzer(unsigned int frequencia, unsigned long duracao);


};

