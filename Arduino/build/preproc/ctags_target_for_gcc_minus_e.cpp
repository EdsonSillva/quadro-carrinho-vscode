# 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
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
# 19 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
/*

    Define para direcionar a compilação do sketch

    __PROJETO_EM_BRANCO__ true  : Compila um sketch em branco

    __PROJETO_EM_BRANCO__ false : Complia o projeto desenvolvido



*/







# 38 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 39 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2

# 41 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 42 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 43 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 44 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 45 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 46 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 47 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2
# 48 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 2

/**

 * Definição das funções utilizadas no projeto

 */
# 53 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
void setup();
void loop();

void (*ResetScreen)() = 0; // Função de Reset apontando para o endereço 0 do microcontrolador

ScreenBoxCar screen = ScreenBoxCar();
byte ScreenIndisponivel = 0;


void setup() {

    screen.iniciar();

    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 66 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 66 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                   "Iniciando os testes NewExec Code"
# 66 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                   ); &__c[0];}))
# 66 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                   )));
    Serial.write(0xff),Serial.write(0xff),Serial.write(0xff);

}

void loop() {

    // byte StandBy = screen.tela.getStandByOnScreen();        // @deprecated

    bool StandBy = screen.getTelaStandBy();

    static double monitorando;

    // nexSerial.print(F("Monitorando: "));
    // nexSerial.print(monitorando);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    monitorando++;

    if (!screen.eeprom.disponivel()) {

        delay(1000); // Aguarda um tempo e tenta novamente o acesso e buscar das informações
        screen.tentarAcessarEAtualizarOnScreen(); // Se conseguir acessar e buscar as informações seta EEPROM disponível no objeto

    } else if (StandBy) {

        // if (StandBy == 255) {
        //     // Problemas na leitura do valor da variável (tela indisponível)

        //     ScreenIndisponivel++;                       // Necessário porque o timeout da serial é afetado pelo processamento na tela

        //     if(ScreenIndisponivel > 100) {
        //         // screen.som.beepBuzzer(16000, 300),   delay(500);
        //         ScreenIndisponivel--;                  // Decrementa 1 para não estourar o contador
        //         delay(1000);
        //     }

        // } else {

            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 105 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 105 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                           "Entrei em standBy"
# 105 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                           ); &__c[0];}))
# 105 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                           )));
            Serial.write(0xff),Serial.write(0xff),Serial.write(0xff);

            // ScreenIndisponivel = 0;                  // Zera o contador
            while (!screen.DadosRecebidoTela()); // aguarda até a tela acordar (sair do stand by)
            screen.tela.limparBufferNexSerial(); // limpa a UART
            screen.setTelaStandBy(false);
            delay(100); // necessário para processamento na tela (wake up)

            Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 114 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 114 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                           "Sai do standBy"
# 114 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino" 3
                           ); &__c[0];}))
# 114 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\ControlScreen.ino"
                           )));
            Serial.write(0xff),Serial.write(0xff),Serial.write(0xff);

        // }

    } else {

        screen.avaliarAcao();

    }
}
