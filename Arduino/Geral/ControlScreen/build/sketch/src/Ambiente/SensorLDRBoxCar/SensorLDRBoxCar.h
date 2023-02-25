#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\Ambiente\\SensorLDRBoxCar\\SensorLDRBoxCar.h"
/*
    Módulo para tratar leitura do sensor de luminosidade LDR
    Pino: Analógico A0
    
    Desenvolvido por Edson Silva
    Date: 22/07/18

*/

#ifndef __SENSORLDRBOXCAR_H__
#define __SENSORLDRBOXCAR_H__

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

    void iniciarSensorLDR();
    void setPinoConexao(byte Pino);         // Usar pinos analógicos
    void setMinimoMaximo(byte Min, byte Max);
    int getValorPuroOnLDR();
    int getValorMapOnLDR();
    int getValorMapInvertidoOnLDR();

};


#endif  // __SENSORLDRBOXCAR_H__
