/*
    Módulo para tratar as chamadas da Biblioteca DHT
    Pino: Analógico A1
    
    Desenvolvido por Edson Silva
    Date: 03/06/18

*/

#ifndef dht_h
#include <dht.h>
#endif

// Definição do pino do DHT
// ------------------------
#define pin_dht     A1    // Pino para recedber o sinal do DHT11

class TemperaturaHumidadeBoxCar
{
private:
    /* data */
    dht     _dht            = dht();
    byte    _pinoConexao    = pin_dht;

public:
    TemperaturaHumidadeBoxCar(/* args */);
    ~TemperaturaHumidadeBoxCar();

    void setPinoConexao(byte Pino);         // Usar pinos digitais
    void readDHT();
    double getTemperaturaOnDHT();
    double getHumidadeOnDHT();
    bool ErroReadOnDHT11();

};

