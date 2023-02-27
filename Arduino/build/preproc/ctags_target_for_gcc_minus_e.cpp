# 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
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
# 19 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
/*

    Define para direcionar a compilação do sketch

    __PROJETO_EM_BRANCO__ true  : Compila um sketch em branco

    __PROJETO_EM_BRANCO__ false : Complia o projeto desenvolvido



*/
# 38 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
# 39 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 40 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 41 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 42 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 43 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 44 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 45 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2
# 46 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2


# 49 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino" 2





# 53 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
/**

 * Definição das funções utilizadas no projeto

 */
# 57 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\ControlBox.ino"
void setup();
void loop();


BoxCar box = BoxCar();

void setup() {

    box.iniciarBoxCar();

}

void loop() {

    if (box.acaoScreen.acaoAtiva()) {
        box.identificarExecutarAcao();
    }

}