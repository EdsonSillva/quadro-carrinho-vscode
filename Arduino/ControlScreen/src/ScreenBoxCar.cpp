
#include "ScreenBoxCar.h"

ScreenBoxCar::ScreenBoxCar() {  }
ScreenBoxCar::~ScreenBoxCar() { }

#pragma region Rotinas de inicialização

void ScreenBoxCar::iniciar() {

    delay(3000);                        // Necessário para aguardar a inicialização física da tela e arduino Box.

    pinMode(_pinoControle, OUTPUT);     // Pino de controle indicando quando este arduino pode iniciar suas rotinas baseado na Ação da tela
    digitalWrite(_pinoControle, LOW);
    
    som.iniciarBuzzer();
    delay(1000);

    eeprom.inicializar();
    delay(1000);

    acao.inicializaEEPROMIno();
    delay(1000);

    ambiente.iniciarSensorLDR();
    delayMicroseconds(1000);
    
    data.iniciarDS3231(true);
    delay(1000);
    
    inicializacaoDaTela();
    delayMicroseconds(1000);
    
}

void ScreenBoxCar::inicializacaoDaTela() {

    while(!_telaOnLine){        

        _telaOnLine = tela.iniciarNextion();

        if(_telaOnLine) {
    
            delayMicroseconds(1000);

            atualizarDadosMemoriaOnScreen();

        } else {        //Fica beepando se a inicialização da tela não for Ok
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(5000);
        }
    }
}

#pragma endregion Rotinas de inicialização

/* @brief deprecated @deprecated*/
// void ScreenBoxCar::avaliarAcao() {
//     if(acaoSelecionada() && !acaoExecutando()) {
//         // Existe ação no screen, mas screen.AcaoExecutando() = false: executar a ação
//         executarAcao();
//     } else if(!acaoSelecionada() && acaoExecutando()) {
//         // Não existe ação no screen, mas screen.AcaoExecutando() = true: reset dos leds no quadro
//         stopAcao();
//     }
//     // Não existe acao no screen e screen.AcaoExecutando() = false: não faz nada
//     atualizarDadosNaTela();        // Atualização das variáveis de Data, hora, tempertura ambiente, temperatura sistema e Umidade
// }

void ScreenBoxCar::avaliarAcao() {

    //TODO 1) Iniciar as mudanças no reconhecimento do ExecCode e se está apontando que está executando na Tela

    // nexSerial.print(F("avaliarAcao()"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    if(tela.existeDadoNoNextion()) {     // Existe alguma solicitação

        // nexSerial.print(F(">>> existeDadoNoNextion()-sim"));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // TODODone criar função para limpar o buffer da serial

        tela.limparBufferNexSerial();
        // nexSerial.flush();
        // delay(10);

        // Busca código ação via dado disponível na serial e carrega no objeto acao
        if(getAcaoSelecionada()) {
            
            executarAcao();     // pode ser iniciar uma ação ou cancletar uma já em execução

        }

    } 

    // Não existe ação no screen e screen.AcaoExecutando() = false: não faz nada
    
    atualizarDadosNaTela();        // Avalia se deve atualizar as variáveis de Data, hora, tempertura ambiente, temperatura sistema e Umidade

    // if(acaoSelecionada() && !acaoExecutando()) {
    //     // Existe ação no screen, mas screen.AcaoExecutando() = false: executar a ação
    //     executarAcao();
    // } else if(!acaoSelecionada() && acaoExecutando()) {
    //     // Não existe ação no screen, mas screen.AcaoExecutando() = true: reset dos leds no quadro
    //     stopAcao();
    // }
    // // Não existe acao no screen e screen.AcaoExecutando() = false: não faz nada
    // atualizarDadosNaTela();        // Atualização das variáveis de Data, hora, tempertura ambiente, temperatura sistema e Umidade

}


/* @brief deprecated @deprecated */
// bool ScreenBoxCar::acaoSelecionada() {
//     acao.setCodeAcao(tela.getAcaoOnScreen());
//     if (acao.getCodeAcao() > 0) return true;
//     return false;
// }

bool ScreenBoxCar::getAcaoSelecionada() {

    // nexSerial.flush();
    byte codeAcao =  tela.getAcaoOnScreen();

    // nexSerial.print(F("getAcaoSelecionada()"));
    // nexSerial.print(F("codeAcao="));
    // nexSerial.print(codeAcao);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    acao.setCodeAcao(codeAcao);
    acao.setQualAcao((eQualAcao)tela.getEstadoAcaoOnScreen());

    // nexSerial.print(F("qualAcao="));
    // nexSerial.print(acao.getQualAcao());
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);


    if (acao.getCodeAcao() > 0) return true;
    return false;

}

bool ScreenBoxCar::acaoExecutando() {

    return acao.getExecutando();

}

void ScreenBoxCar::stopAcao() {

    digitalWrite(_pinoControle, LOW);               // Sinaliza ação cancelada para o outro Arduino
    acao.setExecutando(false);
    delay(50);

}

bool ScreenBoxCar::getTelaStandBy() {
    return _telaStandBy;
}

void ScreenBoxCar::setTelaStandBy(bool valor) {
    _telaStandBy = valor;
}

/* @brief deprecated @deprecated */
// void ScreenBoxCar::executarAcao() {
//     byte CodeAcao = acao.getCodeAcao();
//     if (CodeAcao > 20) {
//         tela.getRGBBrilhoOnScreen(&acao);
//         switch (CodeAcao) {
//             case 254:                                               // Device EEPROM não disponível
//             case 255:                                               // Reset Ação
//                 digitalWrite(_pinoControle, LOW);               // Sinaliza Off para o outro Arduino
//                 delay(50);
//                 break;
//             default:
//                 /* 
//                 *  Ações direcionadas ao quadro de carrinho 
//                 */
//                 if(CodeAcao >= eAcaoBox::acaoBatman) {
//                     carregarBoxesTemaEEPROMCompartilhada((eAcaoBox)CodeAcao);
//                 } else if(acao.chaveAcaoAtualIsMsg()) {                              // Mensagem na Tela
//                     char Texto[50] = {0};
//                     byte QtdeChar = 0;
//                     tela.getTextoOnScreen(Texto, &QtdeChar);
//                     eeprom.setTextoOnMemory(Texto, QtdeChar);
//                 }
//                 eeprom.setDadosOnMemory(&acao);
//                 delay(50);                                                  // Aguarda a atuaização da EEPROm 
//                 digitalWrite(_pinoControle, HIGH);                          // Indica que existe ação para o outro arduino
//                 acao.setExecutando(true);                                   // Indica que a ação está sendo executada 
//         }
//     } else {
//         /* 
//         * Ações reservadas para serem usadas na configuração do sistema e screen Nextion
//         */
//         switch (CodeAcao) {
//             case 1:                                                             // Ação Configurar Data
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
//                 configurarDataNoDevice();        
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
//                 break;
//             case 2:                                                             // Ação Configurar Hora
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
//                 configurarHoraNoDevice();
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
//                 break;
//             case 3:                                                             // Ação Configurar RGB Brilho dos Led's
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 break;
//             case 4:                                                             // Ação Configurar Beep
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
//                 _Beep = tela.getBeepOnScreen();
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
//                 break;
//             case 5:                                                             // Ação Ler Dados Tema da EEPROM do Arduino
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
//                 carregarBoxesTema();
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
//                 break;
//             case 6:                                                             // Ação Salvar Dados Tema na EEPROM do Arduino
//                 tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
//                 // salvarBoxesTema();   // Não está funcionando corretamente (perdendo dados ao receber via Serial)
//                 salvarBoxesTemaByItem();
//                 tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
//                 break;
//         }
//     }
// }

void ScreenBoxCar::executarAcao() {

    byte codeAcao = acao.getCodeAcao();

    // nexSerial.print(F("executarAcao()"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);
    // nexSerial.print(F("......"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("codeAcao="));
    // nexSerial.print(codeAcao);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("......"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    if(codeAcao < 40) {     /* Ações do sistema */

        // nexSerial.print(F("executar acaoSistema()"));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        acaoSistema(&codeAcao);
    
    } else {                /* Ações no quadro de carrinho */
    
        // nexSerial.print(F("executar acaoQuadroCarrinho()"));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        acaoQuadroCarrinho(&codeAcao);
    
    }

    // if (codeAcao > 20) {
    //     tela.getRGBBrilhoOnScreen(&acao);
    //     switch (codeAcao) {
    //         case 254:                                               // Device EEPROM não disponível
    //         case 255:                                               // Reset Ação
    //             digitalWrite(_pinoControle, LOW);               // Sinaliza Off para o outro Arduino
    //             delay(50);
    //             break;
    //         default:
    //             /* 
    //             *  Ações direcionadas ao quadro de carrinho 
    //             */
    //             if(codeAcao >= eAcaoBox::acaoBatman) {
    //                 carregarBoxesTemaEEPROMCompartilhada((eAcaoBox)codeAcao);
    //             } else if(acao.chaveAcaoAtualIsMsg()) {                              // Mensagem na Tela
    //                 char Texto[50] = {0};
    //                 byte QtdeChar = 0;
    //                 tela.getTextoOnScreen(Texto, &QtdeChar);
    //                 eeprom.setTextoOnMemory(Texto, QtdeChar);
    //             }
    //             eeprom.setDadosOnMemory(&acao);
    //             delay(50);                                                  // Aguarda a atuaização da EEPROm 
    //             digitalWrite(_pinoControle, HIGH);                          // Indica que existe ação para o outro arduino
    //             acao.setExecutando(true);                                   // Indica que a ação está sendo executada 
    //     }
    // } else {
    //     /* 
    //     * Ações reservadas para serem usadas na configuração do sistema e screen Nextion
    //     */
    //     switch (codeAcao) {
    //         case 1:                                                             // Ação Configurar Data
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
    //             configurarDataNoDevice();        
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
    //             break;
    //         case 2:                                                             // Ação Configurar Hora
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
    //             configurarHoraNoDevice();
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
    //             break;
    //         case 3:                                                             // Ação Configurar RGB Brilho dos Led's
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             break;
    //         case 4:                                                             // Ação Configurar Beep
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
    //             _Beep = tela.getBeepOnScreen();
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
    //             break;
    //         case 5:                                                             // Ação Ler Dados Tema da EEPROM do Arduino
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
    //             carregarBoxesTema();
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
    //             break;
    //         case 6:                                                             // Ação Salvar Dados Tema na EEPROM do Arduino
    //             tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
    //             // salvarBoxesTema();   // Não está funcionando corretamente (perdendo dados ao receber via Serial)
    //             salvarBoxesTemaByItem();
    //             tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
    //             break;
    //     }
    // }

}

void ScreenBoxCar::acaoSistema(byte *codeAcao) {

    switch ((eAcaoSistema)*codeAcao) {

        case eAcaoSistema::configurarData:      // Ação Configurar Data

            // TODO 01 Data

            tela.setAcaoOnScreen(0);                                        // reset Ação Modo Idle
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
            configurarDataNoDevice();        
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
            break;

        case eAcaoSistema::configurarHora:      // Ação Configurar Hora


            // nexSerial.print(F(">>> eAcaoSistema::configurarHora"));
            // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);
            // nexSerial.print(F("......"));
            // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

            // TODO 10 Hora

            tela.setAcaoOnScreen(0);                                       // reset Ação Modo Idle
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
            configurarHoraNoDevice();
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido

            _maxWait = 0;       // Necessário para executar a rotina de atualização

            break;

        case eAcaoSistema::standBy:             // Ação indicando q o screen está enm stand by ou não

            if(acao.getQualAcao() == eQualAcao::executarAcao) {
                _telaStandBy = true;
            } else {
                _telaStandBy = false;
            }
            break;

        case eAcaoSistema::configurarBeep:      // Ação Configurar Beep

            tela.setAcaoOnScreen(0);                                       // reset Ação Modo Idle
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
            _Beep = tela.getBeepOnScreen();
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
            break;

        case eAcaoSistema::carregarTemas:       // Ação Ler Dados Tema da EEPROM do Arduino

            nexSerial.print(F(">>> eAcaoSistema::carregarTemas"));
            nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff),delay(400);

            tela.setAcaoOnScreen(0);                                       // reset Ação Modo Idle
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
            carregarBoxesTema();
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
            break;

        case eAcaoSistema::salvarTemas:         // Ação Salvar Dados Tema na EEPROM do Arduino

            nexSerial.print(F(">>> eAcaoSistema::salvarTemas"));
            nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff),delay(400);

            tela.setAcaoOnScreen(0);                                       // reset Ação Modo Idle
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
            // salvarBoxesTema();   // Não está funcionando corretamente (perdendo dados ao receber via Serial)
            salvarBoxesTemaByItem();
            tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
            break;
    }

}

void ScreenBoxCar::acaoQuadroCarrinho(byte *codeAcao) {

    switch (acao.getQualAcao())
    {
    case eQualAcao::semAcao:
    case eQualAcao::pararAcao:

        stopAcao();
        acao.setExecutando(false);   // Indica que a ação parou de executar
        break;
    
    default:        // eQualAcao::executarAcao

        executarAcaoQuadroCarrinho(codeAcao);
        break;

    }

}

void ScreenBoxCar::executarAcaoQuadroCarrinho(byte *codeAcao) {

    tela.getRGBBrilhoOnScreen(&acao);

    if(*codeAcao >= eAcaoBox::acaoBatman) {     // Açoes de tema
        
        carregarBoxesTemaEEPROMCompartilhada((eAcaoBox)*codeAcao);

    } else if(acao.chaveAcaoAtualIsMsg()) {     // Mensagem na Tela
        
        char Texto[50] = {0};
        byte QtdeChar = 0;
        tela.getTextoOnScreen(Texto, &QtdeChar);
        eeprom.setTextoOnMemory(Texto, QtdeChar);
    
    }

    eeprom.setDadosOnMemory(&acao);
    delay(50);                                  // Aguarda a atualização da EEPROM 
    digitalWrite(_pinoControle, HIGH);          // Indica que existe ação para o outro arduino
    acao.setExecutando(true);                   // Indica que a ação está sendo executada 

    tela.setAcaoOnScreen(0);                    // reset Ação Modo Idle

    
}


void ScreenBoxCar::tentarAcessarEAtualizarOnScreen(){
    
    atualizarDadosMemoriaOnScreen();

}

void ScreenBoxCar::atualizarDadosMemoriaOnScreen() {

    eeprom.getDadosOnMemory(&acao);

    if (eeprom.disponivel()) {
        
        tela.setDadosRGBBOnScreen(&acao, true);

    } else {        // beep se a memória EEPROM não estiver disponível 
        som.beepBuzzer(),   delay(500);
        som.beepBuzzer(),   delay(500);
        som.beepBuzzer(),   delay(500);
    }
}

void ScreenBoxCar::configurarDataNoDevice() {


    // TODO 02


    byte Dia, Mes, Ano, DoW;
    tela.getDataOnScreen(&Dia, &Mes, &Ano, &DoW);                       // Le a data indicada da tela de configurações


    // nexSerial.print(F(">>> retorno do nextion"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("Dia:"));
    // nexSerial.print(Dia);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Dia, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("Mes:"));
    // nexSerial.print(Mes);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Mes, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("Ano:"));
    // nexSerial.print(Ano);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Ano, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("DoW:"));
    // nexSerial.print(DoW);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(DoW, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    data.setDataOnDS3231(Dia, Mes,  Ano, DoW);                          // Seta a data no dispositivo DS3231


}

void ScreenBoxCar::configurarHoraNoDevice() {

    // TODO 11 Hora

    byte Hora, Minuto, Segundo;
    tela.getHoraOnScreen(&Hora, &Minuto, &Segundo);                     // Le a hora selecionada da tela de configuração

    // nexSerial.print(F(">>> retorno do nextion"));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("hora="));
    // nexSerial.print(Hora);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Hora, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("Min="));
    // nexSerial.print(Minuto);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Minuto, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    // nexSerial.print(F("Seg="));
    // nexSerial.print(Segundo);
    // nexSerial.print(F("| 0x"));
    // nexSerial.print(Segundo, HEX);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    data.setHoraOnDS3231(Hora, Minuto,  Segundo);                       // Seta a hora no dispositivo DS3231

}

void ScreenBoxCar::atualizarDadosNaTela() {

    // TODO 04 (Atualização)

    if(millis() >= _maxWait) {

        Infos::infoSys infoSistema = Infos::infoSys();

        obterInfosSistema(&infoSistema);

        infoTela.setInfoScreen(&infoSistema);

        // nexSerial.print(F("Ano="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::AnoInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("AnoSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::AnoInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::AnoInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("Mes="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::MesInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("MesSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::MesInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::MesInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("Dia="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::DiaInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("DiaSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::DiaInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::DiaInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("Hora="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::HoraInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("HoraSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::HoraInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::HoraInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("Minuto="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::MinutoInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("MinutoSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::MinutoInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::MinutoInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("Segundo="));
        // nexSerial.print(infoTela.getvalor(eTipoTodos::SegundoInfo));
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        // nexSerial.print(F("SegundoSys="));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::SegundoInfo));
        // nexSerial.print(F("|0b"));
        // nexSerial.print(infoTela.getvalorSys(eTipoTodos::SegundoInfo), BIN);
        // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

        if (infoTela.existeAlteracao()) {

            if(_Beep) som.beepBuzzer();

            bool InfoMudou = false;

            if(infoTela.foiAlterado(eTipoDadoInfo::DataInfo)) {
                atualizarDataOnScreen();
            }

            if(infoTela.foiAlterado(eTipoDadoInfo::TempoInfo)) {

                // if(infoTela.valorAlterado(eTipoTodos::HoraInfo)) {

                //     nexSerial.print(F("Tempo Alterado (Hora)"));
                //     nexSerial.print(infoTela.getvalor(eTipoTodos::HoraInfo));
                //     nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

                //     nexSerial.print(F("Tempo Alterado (Hora)"));
                //     nexSerial.print(infoTela.getvalorSys(eTipoTodos::HoraInfo), BIN);
                //     nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

                // }

                atualizarHoraOnScreen();

            }

            if(infoTela.foiAlterado(eTipoDadoInfo::AmbienteInfo)) {
                atualizarAmbienteOnScreen();
            }

            if(infoTela.foiAlterado(eTipoDadoInfo::TempreraturaSysInfo)) {
                atualizarTemperaturaSysOnScreen();
            }

        }

        // @deprecated 
        // atualizarDataHoraOnScreen();
        // atualizarTemperaturaSysOnScreen();
        // atualizarTemperaturaOnScreen();       
        // atualizarUmidadeOnScreen();
        // atualizarLDROnScreen();

        _maxWait = millis() + 1200;                    // Acrescenta um tempo de espera

    }
    
}

bool ScreenBoxCar::DadosRecebidoTela() {
    return tela.existeDadoNoNextion();
}

void ScreenBoxCar::carregarBoxesTemaEEPROMCompartilhada(eAcaoBox CodeAcao) {

    byte sizeBoxes              = acao.getSizeTemaBat();
    byte Boxes[sizeBoxes]       = {0};
    byte posicaoTema            = acao.getPosicaoTemaBat(CodeAcao);

    if(posicaoTema > 0) {

        byte QtdeBoxTema = acao.lerDadosTemaBat(Boxes, posicaoTema);

        eeprom.setTemaOnMemory(Boxes, sizeBoxes, QtdeBoxTema);

    } else {

        eeprom.limparQtdeTema();                      // limpa o endereço de quantidade por não existir tema

    }

}

void ScreenBoxCar::carregarBoxesTema() {

    byte sizeBoxes              = acao.getSizeTemaBat();
    byte Boxes[sizeBoxes]       = {0};
    
    if(lerEEPROMIno(Boxes))
        atualizarBoxesOnScreen(Boxes, sizeBoxes);

}

bool ScreenBoxCar::lerEEPROMIno(byte Boxes[]) {

    byte acaoTema       = tela.getAcaoTemaOnScreen();
    byte posicaoTema    = acao.getPosicaoTemaBat(acaoTema);

    // TODO Estou aqui avaliando o retorno do código do tema

    nexSerial.print(F("acaoTema="));
    nexSerial.print(acaoTema);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff),delay(400);


    if(posicaoTema > 0) {

        acao.lerDadosTemaBat(Boxes, posicaoTema);
        return true;
    }
    return false;
}

void ScreenBoxCar::atualizarBoxesOnScreen(byte Boxes[], byte sizeBoxes) {

    byte Linha              =  0;
    byte Coluna             =  0;
    String strBoxes         = "";
    String strValor         = "";

    for (byte posicao = 0; posicao < sizeBoxes; posicao++)
    {
        if(Boxes[posicao] == 0x00) {

            break;      // Não existe mais dados

        } else {

            Linha = acao.numLinha(Boxes[posicao]);
            Coluna = acao.numColuna(Boxes[posicao]);

            if(Linha < 10)
                strBoxes.concat("0");

            strBoxes.concat((int)Linha);
            strBoxes.concat(":");

            if(Coluna < 10)
                strBoxes.concat("0");

            strBoxes.concat((int)Coluna);
            strBoxes.concat(";");
        }
    }

    tela.setBoxesOnScreen(strBoxes.c_str());    
}

/* @brief Funciona, mas a recepção dos dados via Serial Nextion não estão sendo recebidos na totalidade */
void ScreenBoxCar::salvarBoxesTema() {

    byte sizeBoxes          = tela.getSizeBoxesOnScreen();
    char Boxes[sizeBoxes];

    byte acaoTema       = tela.getAcaoTemaOnScreen();
    byte posicaoTema    = acao.getPosicaoTemaBat(acaoTema);
    
    if(posicaoTema == 0) {

        // Não existe uma posicao cadastrada
        posicaoTema = acao.setPosicaoLivreTemaBat(acaoTema);

    }

    buscarBoxesOnScreen(Boxes, sizeBoxes);
    gravarDadosEEPROMIno(Boxes, sizeBoxes, posicaoTema);

}

void ScreenBoxCar::salvarBoxesTemaByItem() {

    byte sizeBoxes          = tela.getQtdeItensBoxesOnScreen();
    byte Boxes[sizeBoxes];

    byte acaoTema       = tela.getAcaoTemaOnScreen();
    byte posicaoTema    = acao.getPosicaoTemaBat(acaoTema);
    
    if(posicaoTema == 0) {

        // Não existe uma posicao cadastrada
        posicaoTema = acao.setPosicaoLivreTemaBat(acaoTema);

    }

    buscarBoxesOnScreenByItem(Boxes, sizeBoxes);
    gravarDadosEEPROMInoByItem(Boxes, sizeBoxes, posicaoTema);

}

/* @brief Funciona, mas a recepção dos dados via Serial Nextion não estão sendo recebidos na totalidade */
void ScreenBoxCar::buscarBoxesOnScreen(char Boxes[], byte sizeBoxes) {
    byte sizeRecebido = tela.getBoxesOnScreen(Boxes, sizeBoxes);
}

void ScreenBoxCar::buscarBoxesOnScreenByItem(byte Boxes[], byte sizeBoxes) {

    screenNextionObjeto IDObejtos   = screenNextionObjeto();
    byte itemBox                    = 0;
    byte itemBoxes                  = 0;

    for (byte IDItem = IDObejtos.IDItemBoxIni ; IDItem <= IDObejtos.IDItemBoxFim ; IDItem++)
    {
        itemBox = tela.getItemBoxesOnScreen(IDItem);

        Boxes[itemBoxes] = itemBox;
        itemBoxes++;

    }
    
}

/* @brief Funciona, mas a recepção dos dados via Serial Nextion não estão sendo recebidos na totalidade */
void ScreenBoxCar::gravarDadosEEPROMIno(char Boxes[], byte sizeBoxes, int PosicaoTema) {

    int posicaoInicialTema      = acao.posicaoInicialDadoTema(PosicaoTema);
    int posicaoFinalTema        = acao.posicaoFinalDadoTema(PosicaoTema);
    byte posicaoEEPROMIno       = posicaoInicialTema;
    String strLinCol            = "";
    byte numLinCol              = 0;

    for (byte posicaoBoxes = 0; posicaoBoxes < sizeBoxes; posicaoBoxes++)
    {

        if(Boxes[posicaoBoxes] == ';') {

            numLinCol = (byte)strLinCol.toInt();
            EEPROM.write(posicaoEEPROMIno, numLinCol);
            posicaoEEPROMIno++;
            strLinCol = "";
            numLinCol = 0;
            if(posicaoEEPROMIno > posicaoFinalTema) return;     // respeita o tamanho da área do tema

        } else {

            strLinCol += Boxes[posicaoBoxes];

        }
    }

    if (posicaoEEPROMIno < posicaoFinalTema) {
        EEPROM.write(posicaoEEPROMIno, 0x00);           // Grava 0x00 na próxima posição livre do último dado (indica para a rotima de leitura que finalizou os dados salvos mesmo com espaço restantes para acabar a área de dados do tema)
        //acao.setDadoEEPROMIno(posicaoEEPROMIno, posicaoFinalTema -1, 0x00);   // não vou usar porque irá comsumir muito a escrita da memória eeprom
    }


}

void ScreenBoxCar::gravarDadosEEPROMInoByItem(byte Boxes[], byte sizeBoxes, int PosicaoTema) {

    int posicaoInicialTema      = acao.posicaoInicialDadoTema(PosicaoTema);
    int posicaoFinalTema        = acao.posicaoFinalDadoTema(PosicaoTema);
    byte posicaoEEPROMIno       = posicaoInicialTema;

    for (byte posicaoBoxes = 0; posicaoBoxes < sizeBoxes; posicaoBoxes++)
    {

        if(Boxes[posicaoBoxes] != 0) {

            EEPROM.write(posicaoEEPROMIno, Boxes[posicaoBoxes]);
            posicaoEEPROMIno++;
            if(posicaoEEPROMIno > posicaoFinalTema) return;     // respeita o tamanho da área do tema

        } 
    }

    if (posicaoEEPROMIno < posicaoFinalTema) {
        EEPROM.write(posicaoEEPROMIno, 0x00);           // Grava 0x00 na próxima posição livre do último dado (indica para a rotima de leitura que finalizou os dados salvos mesmo com espaço restantes para acabar a área de dados do tema)
        //acao.setDadoEEPROMIno(posicaoEEPROMIno, posicaoFinalTema -1, 0x00);   // não vou usar porque irá comsumir muito a escrita da memória eeprom
    }

}

void ScreenBoxCar::obterInfosSistema(Infos::infoSys *infoSistema) {
    

    // TODO 05 Obtendo dados dos devices



    int Milenio      = tela.getMilenio();
    // data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    data.getDataOnDS3231(infoSistema, &Milenio);

    // byte Hora, Minuto, Segundo;
    // data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);
    data.getHoraOnDS3231(infoSistema);

    infoSistema->Ambiente.Temperatura.valor = (byte)ambiente.getTemperaturaOnDHT();

    infoSistema->Ambiente.Umidade.valor = (byte)ambiente.getUmidadeOnDHT();

    // uint32_t ValorSensor = (uint32_t)ambiente.getValorMapInvertidoOnLDR();
    infoSistema->Ambiente.Luminosidade.valor = (byte)ambiente.getValorMapInvertidoOnLDR();

    infoSistema->TemperaturaSys.valor = data.getTemperaturaSysOnDS3231();

}

#pragma region ### ATUALIZAÇÕES SISTEMA ###

#pragma region Atualização de data e hora

/* @brief deprecated @deprecated */
void ScreenBoxCar::atualizarDataHoraOnScreen() {

    // byte Dia,  Mes,     Ano,      DoW;
    // byte Hora, Minuto,  Segundo;
    // int Milenio      = tela.getMilenio();
    // data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    // data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);

    atualizarDataOnScreen();
    atualizarHoraOnScreen();

    // byte Dia,  Mes,     Ano,      DoW;
    // byte Hora, Minuto,  Segundo;
    // int Milenio      = tela.getMilenio();
    // data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    // tela.showDataOnScreen(&Dia, &Mes, &Ano, &DoW);
    // data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);
    // tela.showHoraOnScreen(&Hora, &Minuto, &Segundo);

}

void ScreenBoxCar::atualizarDataOnScreen() {

    bool mudouValor = false;
    byte valor      = 0x00;

    // byte Dia,   Mes,    Ano,    DoW;
    // int Milenio      = tela.getMilenio();
    // data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    // tela.showDataOnScreen(&Dia, &Mes, &Ano, &DoW);

    mudouValor = infoTela.valorAlterado(eTipoTodos::DiaInfo, &valor);
    if (mudouValor) {
        tela.showDataOnScreen(eTipoDataInfo::DiaInfo, &valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::MesInfo, &valor);
    if (mudouValor) {
        tela.showDataOnScreen(eTipoDataInfo::MesInfo, &valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::AnoInfo, &valor);

    // nexSerial.print(F("..."));
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);
    // nexSerial.print(F("...valor(Ano)="));
    // nexSerial.print(valor);
    // nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);


    if (mudouValor) {
        tela.showDataOnScreen(eTipoDataInfo::AnoInfo, &valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::DoWorkInfo, &valor);
    if (mudouValor) {
        tela.showDataOnScreen(eTipoDataInfo::DoWorkInfo, &valor);
    }

}

void ScreenBoxCar::atualizarHoraOnScreen() {

    bool mudouValor = false;
    byte valor      = 0x00;

    // byte Hora, Minuto, Segundo;
    // data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);
    // tela.showHoraOnScreen(&Hora, &Minuto, &Segundo);

    mudouValor = infoTela.valorAlterado(eTipoTodos::HoraInfo, &valor);
    if (mudouValor) {
        tela.showHoraOnScreen(eTipoTempoInfo::HoraInfo, &valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::MinutoInfo, &valor);
    if (mudouValor) {
        tela.showHoraOnScreen(eTipoTempoInfo::MinutoInfo, &valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::SegundoInfo, &valor);
    if (mudouValor) {
        tela.showHoraOnScreen(eTipoTempoInfo::SegundoInfo, &valor);
    }

}

#pragma endregion Atualização de data e hora

#pragma region Atualizações de Ambiente


void ScreenBoxCar::atualizarAmbienteOnScreen() {

    bool mudouValor = false;
    byte valor      = 0x00;

    mudouValor = infoTela.valorAlterado(eTipoTodos::TemperaturaInfo, &valor);
    if (mudouValor) {
        tela.showTemperaturaOnScreen(&valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::UmidadeInfo, &valor);
    if (mudouValor) {
        tela.showUmidadeOnScreen(&valor);
    }

    mudouValor = infoTela.valorAlterado(eTipoTodos::LuminosidadeInfo, &valor);
    if (mudouValor) {
        tela.showLDROnScreen(&valor);
    }

    // atualizarTemperaturaOnScreen();       
    // atualizarUmidadeOnScreen();
    // atualizarLDROnScreen();

}

/* @brief deprecated @deprecated */
void ScreenBoxCar::atualizarTemperaturaOnScreen() {
    double ValorSensor = ambiente.getTemperaturaOnDHT();
    // tela.showTemperaturaOnScreen(ValorSensor);
}

/* @brief deprecated @deprecated */
void ScreenBoxCar::atualizarUmidadeOnScreen() {
    double ValorSensor = ambiente.getUmidadeOnDHT();
    // tela.showUmidadeOnScreen(ValorSensor);
}

/* @brief deprecated @deprecated */
void ScreenBoxCar::atualizarLDROnScreen() {
    uint32_t ValorSensor = (uint32_t)ambiente.getValorMapInvertidoOnLDR();
    // tela.setLDROnScreen(ValorSensor);
}

#pragma endregion Atualizações de Ambiente


#pragma region Atualizações de sistema

void ScreenBoxCar::atualizarTemperaturaSysOnScreen() {
    
    bool mudouValor = false;
    byte valor      = 0x00;

    mudouValor = infoTela.valorAlterado(eTipoTodos::TemperaturaSysInfo, &valor);
    if (mudouValor) {
        tela.showTempSysOnScreen(&valor);
    }

    // byte temperatura = (byte)data.getTemperaturaSysOnDS3231();
    // tela.showTempSysOnScreen(&temperatura);
    
}

#pragma endregion Atualizações de sistema


#pragma endregion ### ATUALIZAÇÕES SISTEMA ###

