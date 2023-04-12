/*
  Classe Base para controle do tratamento das ações no quadro de carrinho

  Desenvolvido por Edson Silva
  Date: 27/05/18
  
*/

#ifndef __BOXCAR_H__
#define __BOXCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __TYPEDEFBOX_H__
#include "typedef/typedefBox.h"
#endif

#ifndef __BOXEEPROM_H__
#include <BoxEEPROM.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __BOXENUMACAO_H__
#include <BoxEnumAcao.h>
#endif

#ifndef __BOXBUZZERCAR_H__
#include <BoxBuzzerCar.h>
#endif

#ifndef __ACAOSCREEN_H__
#include "AcaoScreen/AcaoScreen.h"
#endif

// #ifndef __ENUMACAO_H__
// #include "src/enum/enumAcao.h"
// #endif

#define   _pin_Controle_          12
#define   _pino_eeprom_usado_     11
#define   _pino_eeprom_alerta_    13
#define   _Linha_Show_            02

class BoxCar
{
private:

  byte    _pinoControle           = _pin_Controle_;
  byte    _pinoUsandoEEPROM       = _pino_eeprom_usado_;
  byte    _pinoAlertaEEPROM       = _pino_eeprom_alerta_;

public:

  BoxCar();
  ~BoxCar();

  BoxEEPROM             eeprom          = BoxEEPROM();
  BoxDadosAcao          dadosAcao       = BoxDadosAcao();
  AcaoScreen            acaoScreen      = AcaoScreen(_pinoControle);
  AcaoBox               acaoBox         = AcaoBox();
  

  void iniciarBoxCar(int BrilhoInicial = 50);
  void showSaudacao();
  bool acaoSolicitada();
  void identificarExecutarAcao();
  void executarAcao(eAcaoBox CodigoAcao);

};

#endif  // __BOXCAR_H__

