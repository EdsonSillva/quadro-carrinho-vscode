
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

void ScreenBoxCar::avaliarAcao() {

    if(acaoSelecionada() && !acaoExecutando()) {
        // Existe ação no screen, mas screen.AcaoExecutando() = false: executar a ação
        executarAcao();

    } else if(!acaoSelecionada() && acaoExecutando()) {
        // Não existe ação no screen, mas screen.AcaoExecutando() = true: reset dos leds no quadro
        stopAcao();

    }

    // Não existe acao no screen e screen.AcaoExecutando() = false: não faz nada
    
    atualizarDadosNaTela();        // Atualização das variáveis de Data, hora, tempertura e humidade

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

void ScreenBoxCar::executarAcao() {

    byte CodeAcao = acao.getCodeAcao();
    
    if (CodeAcao > 20) {

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
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                configurarDataNoDevice();        
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;

            case 2:                                                             // Ação Configurar Hora

                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                configurarHoraNoDevice();
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;

            case 3:                                                             // Ação Configurar RGB Brilho dos Led's

                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                break;

            case 4:                                                             // Ação Configurar Beep

                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                _Beep = tela.getBeepOnScreen();
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;

            case 5:                                                             // Ação Ler Dados Tema da EEPROM do Arduino

                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                carregarBoxesTema();
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;

            case 6:                                                             // Ação Salvar Dados Tema na EEPROM do Arduino

                tela.setAcaoOnScreen(-1);                                       // reset Ação Modo Idle
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutando);      // Informando ao Screem que está processando o pedido
                salvarBoxesTema();
                tela.setExecArduinoOnScreen(eCodeExec::ArduinoExecutado);       // Informando ao Screem que processou o pedido
                break;
        }

    }

}

void ScreenBoxCar::atualizarDadosMemoriaOnScreen() {

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

void ScreenBoxCar::atualizarLDROnScreen() {

    uint32_t ValorSensor = (uint32_t)ambiente.getValorMapInvertidoOnLDR();
    tela.setLDROnScreen(ValorSensor);

}

void ScreenBoxCar::atualizarDataHoraOnScreen() {

    byte Dia,  Mes,     Ano,      DoW;
    byte Hora, Minuto,  Segundo;
    int Milenio      = tela.getMilenio();

    data.getDataOnDS3231(&Dia, &Mes, &Ano, &DoW, &Milenio);
    tela.showDataOnScreen(&Dia, &Mes, &Ano, &DoW);

    data.getHoraOnDS3231(&Hora, &Minuto, &Segundo);
    tela.showHoraOnScreen(&Hora, &Minuto, &Segundo);

}

void ScreenBoxCar::atualizarTemperaturaSysOnScreen() {
    
    int temperatura = data.getTemperaturaSysOnDS3231();
    tela.showTempSysOnScreen(temperatura);
    
}

void ScreenBoxCar::atualizarTemperaturaOnScreen() {

    double ValorSensor = ambiente.getTemperaturaOnDHT();
    tela.showTemperaturaOnScreen(ValorSensor);

}

void ScreenBoxCar::atualizarHumidadeOnScreen() {

    double ValorSensor = ambiente.getHumidadeOnDHT();
    tela.showHumidadeOnScreen(ValorSensor);

}

void ScreenBoxCar::configurarDataNoDevice() {

    byte Dia, Mes, Ano, DoW;
    tela.getDataOnScreen(&Dia, &Mes, &Ano, &DoW);                       // Le a data indicada da tela de configurações
    data.setDataOnDS3231(Dia, Mes,  Ano, DoW);                          // Seta a data no dispositivo DS3231

}

void ScreenBoxCar::configurarHoraNoDevice() {

    byte Hora, Minuto, Segundo;
    tela.getHoraOnScreen(&Hora, &Minuto, &Segundo);                     // Le a hora selecionada da tela de configuração
    data.setHoraOnDS3231(Hora, Minuto,  Segundo);                       // Seta a hora no dispositivo DS3231

}

void ScreenBoxCar::atualizarDadosNaTela() {

    if(_Beep) som.beepBuzzer();

    if(millis() >= _MaxWait) {
        
        atualizarDataHoraOnScreen();
        atualizarTemperaturaSysOnScreen();
        atualizarTemperaturaOnScreen();       
        atualizarHumidadeOnScreen();
        atualizarLDROnScreen();

        _MaxWait = millis() + 10;                    // Acrescenta mais 0,5 segundo

    }
    
}

bool ScreenBoxCar::DadosRecebidoTela() {
    return tela.existeDadoNoNextion();
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

    if(posicaoTema > 0) {

        // nexSerial.print(F("ScreenBoxCar::lerEEPROMIno"));
        // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);

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

    // nexSerial.print(F("ScreenBoxCar::atualizarBoxesOnScreen"));
    // nexSerial.print(F("sizeof(Boxes)={{")), nexSerial.print(sizeBoxes);
    // nexSerial.print(F("}}"));
    // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);


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

    // nexSerial.print(F("sstrBoxes.c_str()={{")), nexSerial.print(strBoxes.c_str());
    // nexSerial.print(F("}}"));
    // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);

    tela.setBoxesOnScreen(strBoxes.c_str());    
}

void ScreenBoxCar::salvarBoxesTema() {

    byte sizeBoxes          = tela.getSizeBoxesOnScreen();
    char Boxes[sizeBoxes]   = {0};

    byte acaoTema       = tela.getAcaoTemaOnScreen();
    byte posicaoTema    = acao.getPosicaoTemaBat(acaoTema);
    
    // nexSerial.print(F("ScreenBoxCar::salvarBoxesTema:::"));
    // nexSerial.print(F("acaoTema={{")), nexSerial.print(acaoTema);
    // nexSerial.print(F("}}"));
    // nexSerial.print(F("posicaoTema={{")), nexSerial.print(posicaoTema);
    // nexSerial.print(F("}}"));
    // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);


    if(posicaoTema == 0) {
        // Não existe uma posicao cadastrada
        posicaoTema = acao.setPosicaoLivreTemaBat(acaoTema);

        // nexSerial.print(F("(Nova)posicaoTema={{")), nexSerial.print(posicaoTema);
        // nexSerial.print(F("}}"));
        // nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);

    }

    buscarBoxesOnScreen(Boxes, sizeBoxes);
    gravarDadosEEPROMIno(Boxes, sizeBoxes, posicaoTema);

}

void ScreenBoxCar::buscarBoxesOnScreen(char Boxes[], byte sizeBoxes) {
    tela.getBoxesOnScreen(Boxes, sizeBoxes);
}

void ScreenBoxCar::gravarDadosEEPROMIno(char Boxes[], byte sizeBoxes, int PosicaoTema) {

    int posicaoInicialTema      = acao.posicaoInicialDadoTema(PosicaoTema);
    int posicaoFinalTema        = acao.posicaoFinalDadoTema(PosicaoTema);

    // byte sizeTemaBat            = acao.getSizeTemaBat();
    // int posicaoInicialTema      = PosicaoTema * sizeTemaBat;
    // int posicaoFinalTema        = posicaoInicialTema + sizeTemaBat;

    byte posicaoEEPROMIno       = posicaoInicialTema;
    String strLinCol            = "";
    byte numLinCol              = 0;

    nexSerial.print(F("ScreenBoxCar::gravarDadosEEPROMIno:::"));
    nexSerial.print(F("Boxes={{")), nexSerial.print(Boxes);
    nexSerial.print(F("}}"));
    nexSerial.print(F("sizeBoxes={{")), nexSerial.print(sizeBoxes);
    nexSerial.print(F("}}"));
    nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);


    for (byte posicaoBoxes = 0; posicaoBoxes < sizeBoxes; posicaoBoxes++)
    {

        nexSerial.print(F("posicaoBoxes={{")), nexSerial.print(posicaoBoxes);
        nexSerial.print(F("}}"));
        nexSerial.print(F("Boxes[posicaoBoxes]={{")), nexSerial.print(Boxes[posicaoBoxes]);
        nexSerial.print(F("}}"));
        nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);


        if(Boxes[posicaoBoxes] == ';') {

            nexSerial.print(F("(e ;)strLinCol={{")), nexSerial.print(strLinCol);
            nexSerial.print(F("}}"));
            nexSerial.print(F("(e ;)posicaoEEPROMIno={{")), nexSerial.print(posicaoEEPROMIno);
            nexSerial.print(F("}}"));
            nexSerial.write(0xFF), nexSerial.write(0xFF), nexSerial.write(0xFF);


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