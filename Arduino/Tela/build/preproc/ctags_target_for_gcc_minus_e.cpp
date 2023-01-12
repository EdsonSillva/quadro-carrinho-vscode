# 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino"
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
# 18 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino"
/*

    Define para direcionar a compilação do sketch

    __PROJETO_EM_BRANCO__ true  : Compila um sketch em branco

    __PROJETO_EM_BRANCO__ false : Complia o projeto desenvolvido



*/





# 35 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 36 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 37 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 38 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 39 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 40 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2
# 41 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino" 2

/**

 * Definição das funções utilizadas no projeto

 */
# 46 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\ControlScreen.ino"
void setup();
void loop();

ScreenBoxCar screen = ScreenBoxCar();

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
