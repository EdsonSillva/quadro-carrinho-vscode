
#include "ScreenBoxCar.h"


ScreenBoxCar::ScreenBoxCar() { }

ScreenBoxCar::~ScreenBoxCar() { }

void ScreenBoxCar::iniciar() {

    delay(3000);                        // Necessário para aguardar a inicialização física da tela e arduino Box.

    pinMode(_pinoControle, OUTPUT);     // Pino de controle indicando quando este arduino pode iniciar suas rotinas baseado na Ação da tela
    digitalWrite(_pinoControle, LOW);
    
    som.iniciarBuzzer();
    delay(1000);

    eeprom.inicializar();
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

            atualizaDadosMemoriaOnScreen();

        } else {        //Fica beepando se a inicialização da tela não for Ok
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(5000);
        }
    }
}

void ScreenBoxCar::avaliarAcao() {

    if(acaoSelecionada() && !acaoExecutando()) {
        // Existe ação no screen, mas screen.AcaoExecutando() = false: executar a ação
        executaAcao();

    } else if(!acaoSelecionada() && acaoExecutando()) {
        // Não existe ação no screen, mas screen.AcaoExecutando() = true: reset dos leds no quadro
        stopAcao();

    }

    // Não existe acao no screen e screen.AcaoExecutando() = false: não faz nada
    
    atualizaDadosNaTela();        // Atualização das variáveis de Data, hora, tempertura e humidade

}

bool ScreenBoxCar::acaoSelecionada() {
    acao.setCodeAcao(tela.getAcaoOnScreen());
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

void ScreenBoxCar::executaAcao() {

    byte CodeAcao = acao.getCodeAcao();
    
    if (CodeAcao > 10) {

        // acao.setCodeAcao(tela.getAcaoOnScreen());
        tela.getRGBBrilhoOnScreen(&acao);
        // acao.gerarChaveAcao();

        switch (CodeAcao) {

            // case 0:                                             // Reset Ação 
            //     digitalWrite(_pinoControle, LOW);               // Sinaliza ação  cancelada para o outro Arduino
            //     delay(50);
            //     break;
            case 254:                                               // Device EEPROM não disponível
            case 255:                                               // Reset Ação
                
                // if (!acao.chaveAcaoAnteriorAtualIgual()) {
                    digitalWrite(_pinoControle, LOW);               // Sinaliza Off para o outro Arduino
                    delay(50);
                // }

                break;

            default:
            
                /* 
                *  Ações direcionadas ao quadro de carrinho 
                */

                // if(!acao.chaveAcaoAnteriorAtualIgual()){

                if(acao.chaveAcaoAtualIsMsg()){                              // Mensagem na Tela
                    char Texto[50] = {0};
                    byte QtdeChar = 0;
                    tela.getTextoOnScreen(Texto, &QtdeChar);
                    eeprom.setTextoOnMemory(Texto, QtdeChar);
                }

                eeprom.setDadosOnMemory(&acao);
                delay(50);                                                  // Aguarda a atuaização da EEPROm 
                digitalWrite(_pinoControle, HIGH);                          // Indica que existe ação para o outro arduino
                acao.setExecutando(true);                                   // Indica que a ação está sendo executada 
                // }
        }

    } else {

        /* 
        * Ações reservadas para serem usadas na configuração do sistema e screen Nextion
        */
        switch (CodeAcao) {

            case 1:                                                             // Ação Configurar Data
                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                configuraDataNoDevice();        
                break;
            case 2:                                                             // Ação Configurar Hora
                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                configuraHoraNoDevice();
                break;
            case 3:                                                             // Ação Configurar RGB Brilho dos Led's
                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                break;
            case 4:                                                             // Ação Configurar Beep
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                _Beep = tela.getBeepOnScreen();
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;
            case 5:                                                             // Ação Salvar Dados Tema
                break;
            case 6:                                                             // Ação Ler Dados Tema
                break;
        }

    }

}

void ScreenBoxCar::atualizaDadosMemoriaOnScreen() {

    // nexSerial.print(F("Chamando: eeprom.getDadosOnMemory(&acao)"));
    eeprom.getDadosOnMemory(&acao);
    // nexSerial.print(F("Retornou de: eeprom.getDadosOnMemory(&acao)"));

    if (eeprom.disponivel()) {
        
        tela.setCodeRGBBrilhoOnScreen(&acao);

    } else {        // Fica beepando se a memória EEPROM não estiver disponível 
        som.beepBuzzer(),   delay(500);
        som.beepBuzzer(),   delay(500);
        som.beepBuzzer(),   delay(500);
    }
}

void ScreenBoxCar::atualizaLDROnScreen() {

    uint32_t ValorSensor = (uint32_t)ambiente.getValorMapInvertidoOnLDR();
    tela.setLDROnScreen(ValorSensor);

}

void ScreenBoxCar::atualizaDataHoraOnScreen() {

    byte Dia,  Mes,     Ano,      DoW;
    byte Hora, Minuto,  Segundo;
    int Milenio      = tela.getMilenio();

    data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    tela.ShowDataOnScreen(&Dia, &Mes, &Ano, &DoW);

    data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);
    tela.ShowHoraOnScreen(&Hora, &Minuto, &Segundo);

}

void ScreenBoxCar::atualizaTemperaturaSysOnScreen() {
    
    int temperatura = data.getTemperaturaSysOnDS3231();
    tela.ShowTempSysOnScreen(temperatura);
    
}

void ScreenBoxCar::atualizaTemperaturaOnScreen() {

    double ValorSensor = ambiente.getTemperaturaOnDHT();
    tela.ShowTemperaturaOnScreen(ValorSensor);

}

void ScreenBoxCar::atualizaHumidadeOnScreen() {

    double ValorSensor = ambiente.getHumidadeOnDHT();
    tela.ShowHumidadeOnScreen(ValorSensor);

}

void ScreenBoxCar::configuraDataNoDevice() {

    tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);          // Informando ao Screem que está processando o pedido
    byte Dia, Mes, Ano, DoW;
    tela.getDataOnScreen(&Dia, &Mes, &Ano, &DoW);                       // Le a data indicada da tela de configurações
    data.setDataOnDS3231(Dia, Mes,  Ano, DoW);                          // Seta a data no dispositivo DS3231
    tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);           // Informando ao Screem que processou o pedido

}

void ScreenBoxCar::configuraHoraNoDevice() {

    tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);          // Informando ao Screem que está processando o pedido
    byte Hora, Minuto, Segundo;
    tela.getHoraOnScreen(&Hora, &Minuto, &Segundo);                     // Le a hora selecionada da tela de configuração
    data.setHoraOnDS3231(Hora, Minuto,  Segundo);                       // Seta a hora no dispositivo DS3231
    tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);           // Informando ao Screem que processou o pedido

}

void ScreenBoxCar::atualizaDadosNaTela() {

    if(_Beep) som.beepBuzzer();

    if(millis() >= _MaxWait) {
        
        atualizaDataHoraOnScreen();
        atualizaTemperaturaSysOnScreen();
        atualizaTemperaturaOnScreen();       
        atualizaHumidadeOnScreen();
        atualizaLDROnScreen();

        _MaxWait = millis() + 10;                    // Acrescenta mais 0,5 segundo

    }
    
}

bool ScreenBoxCar::DadosRecebidoTela() {
    return tela.existeDadoNoNextion();
}

