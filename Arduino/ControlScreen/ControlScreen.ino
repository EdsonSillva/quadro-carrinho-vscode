/*
    Projeto Quadro de carrinhos
    Módulo: >> CONTROLADOR PARA TELA <<
    Descrição: Projeto para controlar os leds de cada box no quadro de carrinhos

    Este projeto tera uma tela como inteface das ações que serão executadas no quadro.

    Função deste sketch: Interagir com a tela e passar os comandos para a memória EEPROM,
                         onde o outro arduino irá interpretar e executar a função de 
                         interação com os leds do quadro de carrinho

    @author:        Edson Silva
    Data Inicio:    27/05/18
    Data Fim:       Ago/20 - 1º versão
    Release:        jun/22
    Release:        jun/23
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

#include <Arduino.h>
#include <Nextion.h>

#include <BoxEEPROM.h>
#include <BoxDadosAcao.h>
#include <BoxBuzzerCar.h>
#include <dht.h>
#include <DS3231.h>
#include <EEPROM.h>
#include "src/ScreenBoxCar.h"
#include <SD.h>


/**
 * Definição das funções utilizadas no projeto
 */

void setup();
void loop();

void (*ResetScreen)() = 0;            // Função de Reset apontando para o endereço 0 do microcontrolador

ScreenBoxCar    screen                  = ScreenBoxCar();
byte            ScreenIndisponivel      = 0;


void setup() {

    screen.iniciar();

    //nexSerial.print(F("Iniciando os testes NewExec Code"));
    //nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

}

void loop() {

    bool StandBy = screen.getTelaStandBy();

    if (!screen.eeprom.disponivel()) {
        
        delay(1000);                                    // Aguarda um tempo e tenta novamente o acesso e buscar das informações
        screen.tentarAcessarEAtualizarOnScreen();       // Se conseguir acessar e buscar as informações seta EEPROM disponível no objeto

    } else if (StandBy) {

        // ScreenIndisponivel = 0;                  // Zera o contador
        while (!screen.DadosRecebidoTela());        // aguarda até a tela acordar (sair do stand by)
        screen.tela.limparBufferNexSerial();        // limpa a UART
        screen.setTelaStandBy(false);
        delay(100);                                 // necessário para processamento da tela (wake up)

    } else {

        // TODO: Problemas no reconhecimento q existe ação. Ao chamar as rotinas de atualização das informações no nextion
        //       o metodo do nextion apaga toda chamada da UART (RX), com isso o comando feito na tela se perde

        // NAO FUNCIONOU BEM, PORQUE O NEXTION SEMPRE RETORNO ALGO QUANDO É ENVIADO INFORMAÇÕES NA TX
        // FUNCIONARIA BEM COM PINOS DIGITAIS DA NEXTION SINALIZANDO UM "CHANGE"

        screen.avaliarAcao();       // Avalia e executa a ação
    
    }    
}

#endif  //Fim da diretiva do código de controle de qual sketch será compilado. Sketch em branco ou o sketch do projeto
