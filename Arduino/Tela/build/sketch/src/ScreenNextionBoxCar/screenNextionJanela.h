#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\ScreenNextionBoxCar\\screenNextionJanela.h"


#ifndef Arduino_h
#include <Arduino.h>
#endif


class screenNextionJanela
{
private:
    /* data */
public:
    screenNextionJanela(/* args */);
    ~screenNextionJanela();

   /* Declaração dos ID's das Janelas do Nextion
    * ------------------------------------------ */ 
    uint8_t const   Splash              =  0,
                    MenuAcao            =  1,
                    Selecao             =  2,
                    ConfigMain          =  3,
                    ConfigDataHora      =  4,
                    VarGlobais          =  8,     // Contêm o id de controle da tela do device Nextion
                    Creditos            =  9,
                    ConfigArduino       = 12;
};
