/*
    Classe de suporte para a classe da memória EEPROM

    Data: 02/12/22
    Autor: Edson Silva

*/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#define _address_device_        0x50

class Device
{
private:

    // Endereço da EEPROM no barramento I2c
    unsigned int _deviceEEPROM          = _address_device_;

public:

    // Controle do segmento da ação, cor, brilho e Beep
    unsigned int AddressDataSeg         = 0x00;
    unsigned int AddressCodeAcao        = AddressDataSeg + 0x00;
    unsigned int AddressR               = AddressDataSeg + 0x01;
    unsigned int AddressG               = AddressDataSeg + 0x02;
    unsigned int AddressB               = AddressDataSeg + 0x03;
    unsigned int AddressBrilho          = AddressDataSeg + 0x04;
    unsigned int AddressBeep            = AddressDataSeg + 0x05;

    // Controle do segmento da mensagem 
    unsigned int AddressDataSegTxt      = 16;
    unsigned int AddressQtdeChar        = AddressDataSegTxt + 0x00;
    unsigned int AddressIniTexto        = AddressDataSegTxt + 0x01;

    // Controle do segmento do tema 
    unsigned int AddressDataSegBox      = 70;
    unsigned int AddressQtdeTemaBox     = AddressDataSegBox;
    unsigned int AddressBoxInicio       = AddressQtdeTemaBox    + 0x01;
    unsigned int AddressBoxFim          = AddressBoxInicio      + 0x14;         // 20 posições


    Device();
    ~Device();
    void setAddress(unsigned int Address);
    unsigned int getAddress();
};

#endif  // __DEVICE_H__