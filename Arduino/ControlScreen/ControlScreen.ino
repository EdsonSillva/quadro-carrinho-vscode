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
#define __MONITORAR_SERIAL__                        false

#if(__PROJETO_EM_BRANCO__ == true)

#include <Arduino.h>

void setup(){ }
void loop() { }

#else

#include <Nextion.h>
#include <BoxEEPROM.h>
#include <BoxDadosAcao.h>
#include <BoxBuzzerCar.h>
#include <dht.h>
#include <DS3231.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "src/ScreenBoxCar.h"

/**
 * Definição das funções utilizadas no projeto
 */

void setup();
void loop();

ScreenBoxCar    screen                  = ScreenBoxCar();
byte            ScreenIndisponivel      = 0;

void setup() {

    screen.iniciar();

}

void loop() {

    byte StandBy = screen.tela.getStandByOnScreen();

    if (!screen.eeprom.disponivel()) {
        
        delay(1000);
        screen.atualizaDadosMemoriaOnScreen();

    } else if (StandBy > 0) {

        if (StandBy == 255) {
            // Problemas na leitura do valor da variável (tela indisponível)
            
            ScreenIndisponivel++;                           // Necessário porque o timeout da serial é afetado pelo processamento na tela
    
            if(ScreenIndisponivel > 100) {
                screen.som.beepBuzzer(16000, 300),   delay(500);
                ScreenIndisponivel--;                  // Decrementa 1 para não estourar o contador
                delay(1000);
            }

        } else {
            ScreenIndisponivel = 0;                     // Zera o contador
            while (!screen.DadosRecebidoTela());        // aguarda até a tela acordar (sair do stand by)
            delay(100);                                 // necessário para processamrento na tela
        }

    } else {

        screen.avaliarAcao();
    
    }    
}

#endif  //Fim da diretiva do código de controle de qual sketch será compilado. Sketch em branco ou o sketch do projeto
