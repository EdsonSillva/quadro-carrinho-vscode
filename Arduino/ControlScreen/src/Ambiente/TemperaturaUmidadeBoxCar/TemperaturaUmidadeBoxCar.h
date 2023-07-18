/*
    Módulo para tratar as chamadas da Biblioteca DHT
    Pino: Analógico A1
    
    Desenvolvido por Edson Silva
    Date: 03/06/18

*/

#ifndef __TEMPERATURAUMIDADEBOXCAR_H__
#define __TEMPERATURAUMIDADEBOXCAR_H__


#ifndef dht_h
#include <dht.h>
#endif

// Definição do pino do DHT
// ------------------------
#define pin_dht             A1              // Pino para receber o sinal do DHT11

class TemperaturaUmidadeBoxCar
{
private:

    dht     _dht            = dht();
    byte    _pinoConexao    = pin_dht;

public:
    TemperaturaUmidadeBoxCar();
    ~TemperaturaUmidadeBoxCar();

    void setPinoConexao(byte Pino);         // Usar pinos digitais
    void readDHT();
    double getTemperaturaOnDHT();
    double getUmidadeOnDHT();
    bool ErroReadOnDHT11();

};



#endif  // __TEMPERATURAUMIDADEBOXCAR_H__