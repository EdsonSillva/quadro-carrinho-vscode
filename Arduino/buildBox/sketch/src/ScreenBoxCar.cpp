#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlScreen\\src\\ScreenBoxCar.cpp"

#include "ScreenBoxCar.h"


ScreenBoxCar::ScreenBoxCar() { }

ScreenBoxCar::~ScreenBoxCar() { }

void ScreenBoxCar::iniciar() {

    delay(3000);                        // Necessário para aguardar a inicialização física da tela e arduino Box.

    // Serial.println("...ScreenBoxCar::iniciar():Entrou");

    pinMode(_pinoControle, OUTPUT);     // Pino de controle indicando quando este arduino pode iniciar suas rotinas baseado na Ação da tela
    digitalWrite(_pinoControle, LOW);
    
    // digitalWrite(_pinoControle, HIGH);
    // delay(5000);
    // digitalWrite(_pinoControle, LOW);

    // Serial.println(F(" >> ScreenBoxCar::iniciar():In(EEPROM)"));
      eeprom.inicializar();
    delay(1000);
    // Serial.println(F("  >> ScreenBoxCar::iniciar():Out"));
    
    // Serial.println(F(">> ScreenBoxCar::iniciar():In(Buzzer)"));
      som.iniciarBuzzer();
    delay(1000);

    // Serial.println(F("  >> ScreenBoxCar::iniciar():Out"));
    
    // Serial.println(F(">> ScreenBoxCar::iniciar():In(iniciarSensorLDR)"));
      ambiente.iniciarSensorLDR();
    delayMicroseconds(1000);
    // Serial.println(F("  >> ScreenBoxCar::iniciar():Out"));
    
    // Serial.println(F(">> ScreenBoxCar::iniciar():In(iniciarDS3231)"));
      data.iniciarDS3231(true);
    delay(1000);
    // Serial.println(F("  >> ScreenBoxCar::iniciar():Out"));
    
    inicializacaoDaTela();
    delayMicroseconds(1000);
    
    // Serial.println("...ScreenBoxCar::iniciar():Saiu");

}

void ScreenBoxCar::inicializacaoDaTela() {

    // Serial.println(F(" >> ScreenBoxCar::iniciar():inicializacaoDaTela")),delay(1000);

    while(!_telaOnLine){        

        _telaOnLine = tela.iniciarNextion();

        if(_telaOnLine) {
    
            delayMicroseconds(1000);

            atualizaDadosMemoriaOnScreen();

        } else {        //Fica beepando se a inicialização da tela não for Ok
            // Serial.println(F(" >> erro:inicializacaoDaTela")), delay(1000);
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(500);
            som.beepBuzzer(),   delay(5000);
        }
    }
}

void ScreenBoxCar::executarAcao() {

    acao.setCodeAcao(tela.getAcaoOnScreen());
    tela.getRGBBrilhoOnScreen(&acao);
    acao.gerarChaveAcao();
    
    switch (acao.getCodeAcao()) {

        case 0:                                                 // Reset Ação 
        case 254:                                               // Device EEPROM não disponível
        case 255:                                               // Reset Ação
            
            if (!acao.chaveAcaoAnteriorAtualIgual()) {
                digitalWrite(_pinoControle, LOW);               // Sinaliza Off para o outro Arduino
                delay(50);
            }

        break;

        /* 
         * ******************************************************************
         * Ações usadas para configuração do sistema e screen Nextion
         * ******************************************************************
         */

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

    default:
        
        /* *******************************************************************
        *  Opções para ação no quadro de carrinho 
        *  ********************************************************************
        */

        if(!acao.chaveAcaoAnteriorAtualIgual()){

            if(acao.chaveAcaoAtualIsMsg()){                              // Mensagem na Tela
                char Texto[50] = {0};
                byte QtdeChar = 0;
                tela.getTextoOnScreen(Texto, &QtdeChar);
                eeprom.setTextoOnMemory(Texto, QtdeChar);
            }
            // eeprom.setDadosOnMemory(CodeAcao,  R,  G,  B,  Brilho);
            eeprom.setDadosOnMemory(&acao);
            digitalWrite(_pinoControle, HIGH);
        }

    }

    /* *****************************************************************************
     *  Rotinas de atualização das variáveis de Data, hora, tempertura e humidade
     * *****************************************************************************
     */

    atualizaDadosNaTela();

}

void ScreenBoxCar::atualizaDadosMemoriaOnScreen() {

    eeprom.getDadosOnMemory(&acao);

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

        _MaxWait = millis() + 500;                    // Acrescenta mais 0,5 segundo

    }
    
}

