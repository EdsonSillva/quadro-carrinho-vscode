/*
    Classe para controle da memória EEPROM usada pelos dois arduinos

    Arquitetura: I2C - Utiliza os pinos SDA(4) e SCL(5)
    
    Data: 01/06/19
    Autor: Edson Silva

*/

#ifndef __BOXMEMORYEEPROM_H__
#define __BOXMEMORYEEPROM_H__

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#include <Arduino.h>
#include <Wire.h>
#include <Device.h>
#include <Pinos.h>

typedef void (*pTipoVoid)(unsigned int, unsigned long);

/*
    Classe de controle dos metodos de tratamento da memória EEPROM externa acoplada ao projeto quadro de carrinho.
*/
class BoxMemoryEEPROM
{
private:

    const unsigned int __CODE_EEPROM_NOT_AVAILABLE__ = 254;

    /* data */
    Device          _device                 = Device();
    Pinos           _pinos                  = Pinos();
    bool            _AlertaSonoroAtivo      = true;
    char            _TextoMsg[50]           = {0};
    pTipoVoid       _FuncBuzzer;
    unsigned int    _frequencia             = 0;
    unsigned long   _duracao                = 0;
    bool            _eepromDisponivel       = false;

    /* method */
    void gravarEEPROM(int offSet, unsigned int Dado);
    byte lerEEPROM(int offSet);
    void startEEPROMsetOffSet(unsigned int offSet);

public:

    BoxMemoryEEPROM();
    BoxMemoryEEPROM(int pinoUsando, int pinoAlerta);
    BoxMemoryEEPROM(Device device, int pinoUsando, int pinoAlerta);
    ~BoxMemoryEEPROM();

    void inicializar();
    bool disponivel();
    byte getPinLedUso();
    void alertaSonoroNaoResponde();
    void getDadosOnMemory(byte *pCodeAcao, byte *pR, byte *pG, byte *pB, byte *pBrilho);
    void getDadosOnMemory(BoxDadosAcao *DadosAcao);
    void setDadosOnMemory(byte CodeAcao, byte R, byte G, byte B, byte Brilho);
    void setDadosOnMemory(BoxDadosAcao *DadosAcao);
    void setTextoOnMemory(char Texto[], byte QtdeChar);
    void getTextoOnMemory(char Texto[], byte *pQtdeChar);

    void setFuncBuzzer(pTipoVoid FuncBuzzer, unsigned int frequencia, unsigned long duracao);

};


#endif  // __BoxMEMORYEEPROM_H__