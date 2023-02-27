#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\ScreenBoxCar.h"
/*
  Classe Base para controle do tratamento com a tela Nextion (screen)

  Desenvolvido por Edson Silva
  Date: 26/05/18
  
*/

#ifndef __SCREENBOXCAR_H__
#define __SCREENBOXCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __BOXMEMORYEEPROM_H__
#include <BoxMemoryEEPROM.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __BOXBUZZERCAR_H__
#include <BoxBuzzerCar.h>
#endif

#ifndef __ENUMBOX_H__
#include "enum/enumBox.h"
#endif

// #include "BuzzerBoxCar/BuzzerBoxCar.h"
#include "ScreenNextionBoxCar/screenNextionBoxCar.h"
#include "DateTimeBoxCar/DateTimeBoxCar.h"
#include "Ambiente/Ambiente.h"

#define   _pin_Controle_          12
#define   _pino_eeprom_usado_     11
#define   _pino_eeprom_alerta_    13

class ScreenBoxCar
{

private:

  byte    _pinoControle           = _pin_Controle_;
  byte    _pinoUsandoEEPROM       = _pino_eeprom_usado_;
  byte    _pinoAlertaEEPROM       = _pino_eeprom_alerta_;
  bool    _Beep                   = false;
  long    _MaxWait                = millis();
  bool    _telaOnLine             = false;

  void configuraDataNoDevice();
  void configuraHoraNoDevice();
  void atualizaDadosNaTela();
  void inicializacaoDaTela();

public:

  ScreenBoxCar();
  ~ScreenBoxCar();

  screenNextionBoxCar         tela        = screenNextionBoxCar();
  BoxBuzzerCar                som         = BoxBuzzerCar();
  DateTimeBoxCar              data        = DateTimeBoxCar();
  Ambiente                    ambiente    = Ambiente();
  BoxMemoryEEPROM             eeprom      = BoxMemoryEEPROM();
  BoxDadosAcao                acao        = BoxDadosAcao();

  void iniciar();
  void executarAcao();
  void atualizaLDROnScreen();
  void atualizaDataHoraOnScreen();
  void atualizaTemperaturaSysOnScreen();
  void atualizaTemperaturaOnScreen();
  void atualizaHumidadeOnScreen();
  void atualizaDadosMemoriaOnScreen();

};


#endif  // __SCREENBOXCAR_H__