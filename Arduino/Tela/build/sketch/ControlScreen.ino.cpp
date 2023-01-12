#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino"
/*
    Projeto Quadro de carrinhos
    Módulo: >> CONTROLADOR PARA TELA <<
    Descrição: Projeto para controlar os leds de cada box no quadro de carrinhos

    Este projeto tera uma tela como inteface das ações que serão executadas no quadro.

    Função deste sketch: Interagir com a tela e passar os comandos para a memória EEPROM,
                         onde o outro arduino irá interpretar e executar a função de 
                         interação com os leds do quadro de carrinho

    Autor:          Edson Silva
    Data Inicio:    27/05/18
    Data Fim:       Ago/20 - 1º versão
    Release:        jun/22
*/

/*
    Define para direcionar a compilação do sketch
    __PROJETO_EM_BRANCO__ true  : Compila um sketch em branco
    __PROJETO_EM_BRANCO__ false : Complia o projeto desenvolvido

*/
#define __PROJETO_EM_BRANCO__                       false
#define __MONITORAR_SERIAL__                        true

#if(__PROJETO_EM_BRANCO__ == true)

void setup(){ }
void loop() { }

#else

#include <Nextion.h>
#include <BoxMemoryEEPROM.h>
#include <BoxDadosAcao.h>
#include <dht.h>
#include <DS3231.h>
#include <Arduino.h>
#include "src/ScreenBoxCar.h"

/**
 * Definição das funções utilizadas no projeto
 */

void setup();
void loop();

ScreenBoxCar    screen = ScreenBoxCar();

void setup() {

    screen.iniciar();

}

void loop() {

    if (!screen.eeprom.disponivel()) {
        
        delay(1000);
        screen.atualizaDadosMemoriaOnScreen();

    } else if (screen.tela.getStandByOnScreen() == 1) {
        
        delay(1000);
    
    } else {
    
        screen.executarAcao();
    
    }    
}

#endif  //Fim da diretiva do código de controle de qual sketch será compilado. Sketch em branco ou o sketch do projeto

