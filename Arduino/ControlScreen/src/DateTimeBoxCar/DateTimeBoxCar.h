/*
    Módulo para configurar e ler a data, hora, umidade e temperatura do DS3231
    Pino I2C: SDA(A4) e SCL(A5) 
    
    Desenvolvido por Edson Silva
    Date: 13/05/18

*/

#ifndef __DATETIMEBOXCAR_H__
#define __DATETIMEBOXCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __INFOS_H__
#include "../Infos/Infos.h"
#endif

#include <DS3231.h>
#include <Wire.h>


class DateTimeBoxCar
{
private:

    DS3231 _RTC;

    byte CalculoDoW(byte *dia, byte *mes, int *ano);

public:

    DateTimeBoxCar();
    ~DateTimeBoxCar();

    void iniciarDS3231(bool Clock24hs);
    byte getDoW();
    byte getDoWork(byte *Dia, byte *Mes, byte *Ano, int *Milenio);
    bool setHoraOnDS3231(byte Hora, byte Minuto, byte Segundo);
    void getHoraOnDS3231(byte *Hora, byte *Minuto, byte *Segundo);
    bool setDataOnDS3231(byte Dia, byte Mes, byte Ano, byte DoW);
    void getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW);
    void getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW, int *Milenio);
    int getTemperaturaSysOnDS3231();

    // FIXME Mudar todas as funções

    void getDataOnDS3231(Infos::infoSys *infosSys, int *Milenio);
    void getHoraOnDS3231(Infos::infoSys *infosSys);


};

#endif  // __DATETIMEBOXCAR_H__
