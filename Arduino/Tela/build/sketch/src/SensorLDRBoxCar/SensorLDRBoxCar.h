#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\SensorLDRBoxCar\\SensorLDRBoxCar.h"
/*
    Módulo para tratar leitura do sensor de luminosidade LDR
    Pino: Analógico A0
    
    Desenvolvido por Edson Silva
    Date: 22/07/18

*/

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define     _pin_LDR_    A0        // Pino de entrada para uso do sensor de luminosidade
#define     _Min_         0
#define     _Max_       120

class SensorLDRBoxCar
{
private:
    /* data */
    byte    _pinoConexao        = _pin_LDR_;
    byte    _Min                = _Min_;
    byte    _Max                = _Max_;

    int lerSensor();

public:
    SensorLDRBoxCar(/* args */);
    ~SensorLDRBoxCar();

    void setPinoConexao(byte Pino);         // Usar pinos analógicos
    void setMinimoMaximo(byte Min, byte Max);
    void IniciarSensorLDR();
    int getValorPuroOnLDR();
    int getValorMapOnLDR();
    int getValorMapInvertidoOnLDR();

};




