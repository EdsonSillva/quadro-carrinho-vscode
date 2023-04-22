/*
    Classe de suporte para a classe da memória EEPROM

    Data: 02/12/22
    Autor: Edson Silva

*/

#include <Device.h>

Device::Device() { }
Device::~Device() { }

void Device::setAddress(unsigned int Address) {
    _deviceEEPROM = Address;
  }

unsigned int Device::getAddress() {
    return _deviceEEPROM;
}