#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\enum\\enumBox.h"
/*
    Controle dos enumeration usados no projeto
*/

#ifndef __ENUMBOX_H__
#define __ENUMBOX_H__

/**
 * Enumeration para indicar se uma ação foi solicitada e se o arduino está executando
 */
enum eCodeExec {

    SemExecucao                 = 0,        // Estado inicial ou sem pedido de execução - Usado pelo Nextion
    NextionSolicitaExecucao     = 1,        // Screeen solicitando Execução no Arduino  - Usado pelo Nextion
    ArduinoExecutando           = 2,        // Arduino Executando                       - Usado pelo Arduino
    ArduinoExecutado            = 3         // Execução finalizada pelo Arduino         - Usado pelo Arduino

};


#endif  // __ENUMBOX_H__