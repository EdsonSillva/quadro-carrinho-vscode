/*
    Classe para controle da memória EEPROM usada pelos dois arduinos

    Arquitetura: I2C - Utiliza os pinos SDA(4) e SCL(5)
    
    Data: 01/06/19
    Autor: Edson Silva

*/

#ifndef __BOXEEPROM_H__
#define __BOXEEPROM_H__

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __BOXBUZZERCAR_H__
#include <BoxBuzzerCar.h>
#endif

#include <Arduino.h>
#include <Wire.h>
#include <Device.h>
#include <Pinos.h>

/*
    Classe de controle dos metodos de tratamento da memória EEPROM externa acoplada ao projeto quadro de carrinho.
*/
class BoxEEPROM
{
private:

    const unsigned int __CODE_EEPROM_NOT_AVAILABLE__ = 254;

    Device          _device                 = Device();
    Pinos           _pinos                  = Pinos();
    bool            _AlertaSonoroAtivo      = true;
    char            _TextoMsg[50]           = {0};
    unsigned int    _frequencia             = 0;
    unsigned long   _duracao                = 0;
    bool            _eepromDisponivel       = false;
    BoxBuzzerCar    _som;

    /* method */
    void gravarEEPROM(int offSet, unsigned int Dado);
    byte lerEEPROM(int offSet);
    void startEEPROMsetOffSet(unsigned int offSet);

public:

    BoxEEPROM();
    BoxEEPROM(BoxBuzzerCar som);
    BoxEEPROM(int pinoUsando, int pinoAlerta);
    BoxEEPROM(Device device, int pinoUsando, int pinoAlerta);
    ~BoxEEPROM();

    void inicializar();
    bool disponivel();
    byte getPinLedUso();
    void alertaSonoroNaoResponde();
    void getDadosOnMemory(BoxDadosAcao *DadosAcao);
    void setDadosOnMemory(BoxDadosAcao *DadosAcao);
    void setTextoOnMemory(char Texto[], byte QtdeChar);
    void getTextoOnMemory(char Texto[], byte *pQtdeChar);

};

#endif  // __BOXEEPROM_H__