#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\ScreenNextionBoxCar\\ScreenNextionObjeto.h"
/*

  Biblioteca auxiliar para Nextion (screen)
  Desenvolvido por Edson Silva
  Date: 26/05/18
  Comunicação Rx e Tx padrão do microcontrolador (Serial: 9600)

*/


#ifndef __SCREENNEXTIONOBJETO_H__
#define __SCREENNEXTIONOBJETO_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

class screenNextionObjeto
{
private:
    /* data */
public:
    screenNextionObjeto(/* args */);
    ~screenNextionObjeto();

   /* Declaração dos ID's dos Objetos Nextion
    * --------------------------------------- */
    uint8_t const   IDAcaoArduino             =  1,
                    IDStandBy                 = 29,
                    IDArduinoExec             =  3,
                    IDLDR                     = 24,
                    IDR                       = 20,
                    IDG                       = 21,
                    IDB                       = 22,
                    IDBrilho                  = 23,
                    IDCorRGB                  = 19,
                    IDCode                    = 25,
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
                    IDAS                      = 13;

};



#endif  // __SCREENNEXTIONOBJETO_H__
