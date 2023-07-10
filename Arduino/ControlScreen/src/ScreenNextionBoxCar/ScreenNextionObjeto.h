/*

  Biblioteca auxiliar para Nextion (screen)
  Desenvolvido por Edson Silva
  Date: 26/05/18
  Comunicação Rx e Tx padrão do microcontrolador (Serial: 9600)

  Modificado em: 10/07/23

*/


#ifndef __SCREENNEXTIONOBJETO_H__
#define __SCREENNEXTIONOBJETO_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

class screenNextionObjeto
{
private:
    
public:
    screenNextionObjeto();
    ~screenNextionObjeto();

   /*
    @brief  Relação dos objetos da tela Nextion para serem usados nas 
            chamadas dos métodos. O número representa o ID do objeto na 
            tela do Nextion.
   */
    uint8_t const   IDAcaoArduino             =  1,
                    IDAcaoEmExec              = 36,
                    IDStandBy                 = 29,
                    IDArduinoExec             =  3,
                    IDLDR                     = 24,
                    IDR                       = 20,
                    IDG                       = 21,
                    IDB                       = 22,
                    IDBrilho                  = 23,
                    IDCorRGB                  = 19,
                    IDEEPROMDisp              = 25,
                    IDDoW                     = 26,
                    IDTexto                   = 26,
                    IDTextoQtde               = 27,
                    IDDia                     =  8,
                    IDMes                     =  9,
                    IDAno                     = 10,
                    IDDoWGlobal               = 12,
                    IDHora                    = 13,
                    IDMin                     = 14,
                    IDSeg                     = 15,
                    IDBeep                    = 28,
                    IDTempSys                 = 17,
                    IDTemp                    = 16,
                    IDHumidade                = 18,
                    IDDH                      = 11,
                    IDMM                      = 12,
                    IDAS                      = 13,
                    IDAcaoTema                = 59,
                    IDBoxes                   = 22,
                    IDBoxesLinCol             = 53,
                    IDSizeBoxesLC             = 58,
                    IDItemBoxIni              = 61,
                    IDItemBoxFim              = 80,
                    IDQtdeItensBox            = 81;

};



#endif  // __SCREENNEXTIONOBJETO_H__
