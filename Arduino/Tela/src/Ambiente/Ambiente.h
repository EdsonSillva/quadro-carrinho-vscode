/*
  Classe Base para controle dos componentes e devices que interagem com 
  o ambiente externo do quadro de  carrinhos
  
  Desenvolvido por Edson Silva
  Date: 03/01/23
*/


#ifndef __AMBIENTE_H__
#define __AMBIENTE_H__

#include "SensorLDRBoxCar/SensorLDRBoxCar.h"
#include "TemperaturaHumidadeBoxCar/TemperaturaHumidadeBoxCar.h"


class Ambiente : public SensorLDRBoxCar, public TemperaturaHumidadeBoxCar
{
private:
    /* data */
public:
    Ambiente(/* args */);
    ~Ambiente();

};

#endif  // __AMBIENTE_H__
