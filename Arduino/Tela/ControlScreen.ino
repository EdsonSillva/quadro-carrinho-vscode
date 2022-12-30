
/*
    Projeto Quadro de carrinhos
    Módulo: >> CONTROLADOR PARA TELA <<
    Descrição: Projeto para controlar os leds de cada box no quadro de carrinhos

    Este projeto tera uma tela como inteface das ações 
    que serão executadas no quadro.

    Função deste sketch: Interagir com a tela e passar os comandos para a memória EEPROM,
                         onde o outro arduino irá interpretar e executar a função

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
#include <dht.h>
#include <Arduino.h>

/**
 * Definição das funções utilizadas no projeto
 */

void setup();
void loop();

BoxMemoryEEPROM Memory = BoxMemoryEEPROM(11, 13);

void setup()
{

}

void loop()
{
    
}



#endif  //Fim da diretiva do código de controle de qual sketch será compilado. Sketch em branco ou o sketch do projeto
