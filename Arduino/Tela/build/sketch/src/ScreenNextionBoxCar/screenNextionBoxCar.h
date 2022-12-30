#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\ScreenNextionBoxCar\\screenNextionBoxCar.h"
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

#ifndef __NEXTION_H__
#include <Nextion.h>
#endif

#include "../enum/enumBox.h"
#include "screenNextionJanela.h"
#include "ScreenNextionObjeto.h"

class screenNextionBoxCar
{
private:

    screenNextionJanela     _tela       = screenNextionJanela();
    screenNextionObjeto     _objeto     = screenNextionObjeto();
    eCodeExec               _CodeExec   = eCodeExec::SemExecucao;
        
    int                     _Milenio    = 2000;



public:
    screenNextionBoxCar(/* args */);
    ~screenNextionBoxCar();

    bool iniciarNextion();
    void setVarNextion(char VarGlobal[], int TestoLEngth, String NomeVar);
    byte getAcaoOnScreen();
    byte getStandByOnScreen();
    void setAcaoOnScreen(uint32_t Acao);
    void setExecArduinoOnScreen(eCodeExec CodeExec);

};

