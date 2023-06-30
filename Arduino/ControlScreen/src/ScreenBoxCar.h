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

#ifndef __BOXEEPROM_H__
#include <BoxEEPROM.h>
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
  bool    _Beep                   = true;
  long    _MaxWait                = millis();
  bool    _telaOnLine             = false;

  void configurarDataNoDevice();
  void configurarHoraNoDevice();
  void carregarBoxesTema();
  void carregarBoxesTemaEEPROMCompartilhada(eAcaoBox CodeAcao);
  bool lerEEPROMIno(byte Boxes[]);
  void atualizarBoxesOnScreen(byte Boxes[], byte sizeBoxes);
  void salvarBoxesTema();
  void salvarBoxesTemaByItem();
  void buscarBoxesOnScreen(char Boxes[], byte sizeBoxes);
  void buscarBoxesOnScreenByItem(byte Boxes[], byte sizeBoxes);
  void gravarDadosEEPROMIno(char Boxes[], byte sizeBoxes, int PosicaoTema);
  void gravarDadosEEPROMInoByItem(byte Boxes[], byte sizeBoxes, int PosicaoTema);
  void inicializacaoDaTela();

  

public:

  ScreenBoxCar();
  ~ScreenBoxCar();

  screenNextionBoxCar         tela        = screenNextionBoxCar();
  BoxBuzzerCar                som         = BoxBuzzerCar();
  DateTimeBoxCar              data        = DateTimeBoxCar();
  Ambiente                    ambiente    = Ambiente();
  BoxEEPROM                   eeprom      = BoxEEPROM(&som);
  BoxDadosAcao                acao        = BoxDadosAcao();

  void iniciar();
  void avaliarAcao();
  void executarAcao();
  // void executaConfig();
  bool acaoSelecionada();
  bool acaoExecutando();
  void stopAcao();
  void atualizarDadosNaTela();
  void atualizarLDROnScreen();
  void atualizarDataHoraOnScreen();
  void atualizarTemperaturaSysOnScreen();
  void atualizarTemperaturaOnScreen();
  void atualizarHumidadeOnScreen();
  void atualizarDadosMemoriaOnScreen();
  void tentarAcessarEAtualizarOnScreen();
  bool DadosRecebidoTela();

};


#endif  // __SCREENBOXCAR_H__
