# 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
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
# 18 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
/*

    Define para direcionar a compilação do sketch

    __PROJETO_EM_BRANCO__ true  : Compila um sketch em branco

    __PROJETO_EM_BRANCO__ false : Complia o projeto desenvolvido



*/







# 37 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 38 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 39 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 40 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 41 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 42 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 43 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 44 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 45 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2

/**

 * Definição das funções utilizadas no projeto

 */
# 50 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
void setup();
void loop();

ScreenBoxCar screen = ScreenBoxCar();
byte ScreenIndisponivel = 0;

void setup() {

    screen.iniciar();

}

void loop() {

    byte StandBy = screen.tela.getStandByOnScreen();

    if (!screen.eeprom.disponivel()) {

        delay(1000);
        screen.atualizarDadosMemoriaOnScreen();

    } else if (StandBy > 0) {

        if (StandBy == 255) {
            // Problemas na leitura do valor da variável (tela indisponível)

            ScreenIndisponivel++; // Necessário porque o timeout da serial é afetado pelo processamento na tela

            if(ScreenIndisponivel > 100) {
                // screen.som.beepBuzzer(16000, 300),   delay(500);
                ScreenIndisponivel--; // Decrementa 1 para não estourar o contador
                delay(1000);
            }

        } else {
            ScreenIndisponivel = 0; // Zera o contador
            while (!screen.DadosRecebidoTela()); // aguarda até a tela acordar (sair do stand by)
            delay(100); // necessário para processamrento na tela
        }

    } else {

        screen.avaliarAcao();

    }
}
