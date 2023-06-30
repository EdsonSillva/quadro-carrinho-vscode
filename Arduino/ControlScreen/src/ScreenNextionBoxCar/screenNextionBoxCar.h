/*

  Biblioteca Nextion (screen)
  Desenvolvido por Edson Silva
  Date: 26/05/18
  Comunicação Rx e Tx padrão do microcontrolador (Serial: 9600)
  
  Observação: Fiz um ajuste na Lib do Nextion para aceitar a passagem de parâmetro 
  via ID do objeto do Nextion. A função original só estava aceitando passagem por string 
  (nome do objeto criado no nextion). Assim consegui reduzir o consumo da memória do 
  microcontrolador. No arquivo zDumpNextion.ino contêm a solução completa e funcionando com o
  código original 'comentado' com a passagem via string e também usando a função F().

*/

#ifndef __SCREENNEXTIONBOXCAR_H__
#define __SCREENNEXTIONBOXCAR_H__

#ifndef __NEXTION_H__
#include <Nextion.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#include "../enum/enumBox.h"
#include "screenNextionJanela.h"
#include "ScreenNextionObjeto.h"

typedef void (*funcDataDS3231)(byte*, byte*, byte*, byte*, int*);
typedef void (*funcHoraDS3231)(byte*, byte*, byte*);

class screenNextionBoxCar
{
private:

    screenNextionJanela     _tela       = screenNextionJanela();
    screenNextionObjeto     _objeto     = screenNextionObjeto();
    eCodeExec               _CodeExec   = eCodeExec::SemExecucao;
    int                     _Milenio    = 2000;

    void DataHoraOnScreen(byte *pDH, byte *pMM, byte *pAS);

public:
    screenNextionBoxCar();
    ~screenNextionBoxCar();

    bool iniciarNextion();
    int getMilenio();
    void setVarNextion(char VarGlobal[], int TestoLEngth, String NomeVar);
    byte getAcaoOnScreen();
    byte getAcaoTemaOnScreen();
    byte getStandByOnScreen();
    bool existeDadoNoNextion();
    void setAcaoOnScreen(uint32_t Acao);
    void setExecArduinoOnScreen(eCodeExec CodeExec);
    void setLDROnScreen(uint32_t ValorSensor);
    void getRGBBrilhoOnScreen(BoxDadosAcao *DadosAcao);
    void setDadosRGBBOnScreen(BoxDadosAcao *DadosAcao, bool EEPROMDisp);
    byte getDoWOnScreen();
    void getDataOnScreen(byte *pDia, byte *pMes, byte *pAno, byte *DoW);
    void getHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo);
    void getTextoOnScreen(char Texto[], byte *pQtdeChar);
    void showDataOnScreen(byte *Dia, byte *Mes, byte *Ano, byte *DoW);
    void showHoraOnScreen(byte *Hora, byte *Minuto, byte *Segundo);
    bool getBeepOnScreen();
    void showTempSysOnScreen(int TemperaturaSys);
    void showTemperaturaOnScreen(double TemperaturaAmbiente);
    void showHumidadeOnScreen(double HumidadeAmbiente);
    void setBoxesOnScreen(const char Boxes[]);
    byte getSizeBoxesOnScreen();
    byte getQtdeItensBoxesOnScreen();
    byte getBoxesOnScreen(char Boxes[], byte sizeBoxes);
    byte getItemBoxesOnScreen(byte IDItemBox);

};


#endif  // __SCREENNEXTIONBOXCAR_H__
