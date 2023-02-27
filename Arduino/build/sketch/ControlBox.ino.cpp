#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
/*
    Projeto Quadro de carrinhos
    Módulo: >> CONTROLADOR QUADRO LED (BOX) <<
    Descrição: Projeto para controlar os leds de cada box no quadro de carrinhos

    Este projeto tera uma tela como inteface das ações 
    que serão executadas no quadro.

    Função deste sketch: Interagir com os leds do quadro de carrinhos executando as ações 
                         selecionadas na tela do Nextion, lendo estes comandos na memória EEPROM.


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

#include <Arduino.h>

void setup(){ }
void loop() { }

#else


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <BoxEEPROM.h>
#include <BoxDadosAcao.h>
#include <BoxBuzzerCar.h>
#include "src/BoxCar.h"
#include "src/enum/enumBoxTematico.h"
#include "src/enum/enumAcao.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif



/**
 * Definição das funções utilizadas no projeto
 */

void setup();
void loop();


BoxCar box   = BoxCar();

void setup() {
	
    box.iniciarBoxCar();

}

void loop() {
	
    if (box.acaoSolicitada()) {
        box.identificarExecutarAcao();
    }

}



#endif  //Fim da diretiva do código de controle de qual sketch será compilado. Sketch em branco ou o sketch com os código

