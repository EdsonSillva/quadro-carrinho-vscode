/*

  Biblioteca auxiliar para Nextion (screen)
  Desenvolvido por Edson Silva
  Date: 26/05/18
  Comunicação Rx e Tx padrão do microcontrolador (Serial: 9600)

*/


#ifndef __SCREENNEXTIONJANELA_H__
#define __SCREENNEXTIONJANELA_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

class screenNextionJanela
{
private:
    
public:
    screenNextionJanela();
    ~screenNextionJanela();

   /* Declaração dos ID's das Janelas do Nextion
    * ------------------------------------------ */ 
    uint8_t const   Splash              =  0,
                    MenuAcao            =  1,
                    Selecao             =  2,
                    ConfigMain          =  3,
                    ConfigDataHora      =  4,
                    ConfigArduino       =  9,
                    ConfigBoxFixo       = 10, 
                    Creditos            = 11,
                    Global              = 12;     // Contêm o id de controle da tela do device Nextion
};



#endif  // __SCREENNEXTIONJANELA_H__
