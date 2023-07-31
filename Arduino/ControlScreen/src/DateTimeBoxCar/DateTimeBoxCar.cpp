

#include "DateTimeBoxCar.h"


DateTimeBoxCar::DateTimeBoxCar() { }

DateTimeBoxCar::~DateTimeBoxCar() { }

/*
  Inicializa o device entrando via Wire

  @param Clock24hs indica se a contagem de horas vai ser em 12hs ou 24hs. Informe true=24hs ou false=12hs
  
*/
void DateTimeBoxCar::iniciarDS3231(bool Clock24hs) {

    Wire.begin();                           // Entra no barramento I2c
    delay(10);                              // Aguarda a inicialização do Wire
    _RTC.setClockMode(!Clock24hs);          // set  true=12hs false=24hs format
    _RTC.setDoW(0);                         // set the Day-of-Week to SUNDAY (0)
}

byte DateTimeBoxCar::getDoW() {
    return _RTC.getDoW();
}

byte DateTimeBoxCar::getDoWork(byte *Dia, byte *Mes, byte *Ano, int *Milenio) {
    int AnoComMilenio = *Milenio + *Ano;
    return CalculoDoW(Dia, Mes, &AnoComMilenio);
}

bool DateTimeBoxCar::setHoraOnDS3231(byte Hora, byte Minuto, byte Segundo) {

    // TODO 12 Hora

    nexSerial.print(F(">>> setando a hora no DS3231"));
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Hora:"));
    nexSerial.print(Hora);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Hora);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Minuto:"));
    nexSerial.print(Minuto);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Minuto, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Segundo:"));
    nexSerial.print(Segundo);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Segundo, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

  _RTC.setHour(Hora);
  _RTC.setMinute(Minuto);
  _RTC.setSecond(Segundo);


}

/*@brief deprecated @deprecated */
void DateTimeBoxCar::getHoraOnDS3231(byte *Hora, byte *Minuto, byte *Segundo) {
  bool h12, PM;
  *Hora=_RTC.getHour(h12,PM);
  *Minuto=_RTC.getMinute();
  *Segundo=_RTC.getSecond();
}

bool DateTimeBoxCar::setDataOnDS3231(byte Dia, byte Mes, byte Ano, byte DoW) {

    // TODO 03


    nexSerial.print(F(">>> setando a data no DS3231"));
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Dia:"));
    nexSerial.print(Dia);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Dia, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Mes:"));
    nexSerial.print(Mes);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Mes, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("Ano:"));
    nexSerial.print(Ano);
    nexSerial.print(F("| 0x"));
    nexSerial.print(Ano, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("DoW:"));
    nexSerial.print(DoW);
    nexSerial.print(F("| 0x"));
    nexSerial.print(DoW, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);


  _RTC.setDate(Dia);
  _RTC.setMonth(Mes);
  _RTC.setYear(Ano);
  _RTC.setDoW(DoW);
}

/*@brief deprecated @deprecated */
void DateTimeBoxCar::getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW) {
  
  bool Century=false;
  
  *Dia=_RTC.getDate();
  *Mes=_RTC.getMonth(Century);
  *Ano=_RTC.getYear();
  *DoW=_RTC.getDoW();
}

/*@brief deprecated @deprecated */
void DateTimeBoxCar::getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW, int *Milenio) {
  
  bool Century=false;
  
  *Dia=_RTC.getDate();
  *Mes=_RTC.getMonth(Century);
  *Ano=_RTC.getYear();
  // *DoW=RTC.getDoW();   // Não funciona
  *DoW = getDoWork(Dia, Mes, Ano, Milenio);
}


#pragma region Funções com parâmetros Infos::infoSys

/* @brief novo meio de chamar a função */
void DateTimeBoxCar::getDataOnDS3231(Infos::infoSys *infosSys, int *Milenio) {
  

    //TODO 06 getDS3231()

    bool Century=false;
    
    infosSys->Data.Dia.valor = _RTC.getDate();
    infosSys->Data.Mes.valor = _RTC.getMonth(Century);
    infosSys->Data.Ano.valor = _RTC.getYear();

    infosSys->Data.DoW.valor = getDoWork(&infosSys->Data.Dia.valor,
                                         &infosSys->Data.Mes.valor,
                                         &infosSys->Data.Ano.valor,
                                         Milenio
                                        );


    nexSerial.print(F("infosSys->DoW:"));
    nexSerial.print(infosSys->Data.DoW.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Data.DoW.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Ano:"));
    nexSerial.print(infosSys->Data.Ano.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Data.Ano.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Mes:"));
    nexSerial.print(infosSys->Data.Mes.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Data.Mes.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Dia:"));
    nexSerial.print(infosSys->Data.Dia.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Data.Dia.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);


}

/* @brief novo meio de chamar a função */
void DateTimeBoxCar::getHoraOnDS3231(Infos::infoSys *infosSys) {

    bool h12, PM;

    infosSys->Tempo.Hora.valor = _RTC.getHour(h12, PM);
    infosSys->Tempo.Min.valor = _RTC.getMinute();
    infosSys->Tempo.Sec.valor = _RTC.getSecond();


    nexSerial.print(F(">>> Hora"));
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Hora:"));
    nexSerial.print(infosSys->Tempo.Hora.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Tempo.Hora.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Minuto:"));
    nexSerial.print(infosSys->Tempo.Min.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Tempo.Min.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);

    nexSerial.print(F("infosSys->Segundo:"));
    nexSerial.print(infosSys->Tempo.Sec.valor);
    nexSerial.print(F("| 0x"));
    nexSerial.print(infosSys->Tempo.Sec.valor, HEX);
    nexSerial.write(0xff),nexSerial.write(0xff),nexSerial.write(0xff);




}

#pragma endregion Funções com parâmetros Infos::infoSys

/* @brief Esta função usa o sensor de temperatura do DS3231 para mediar a temperatura do sistema */
int DateTimeBoxCar::getTemperaturaSysOnDS3231(){
  return _RTC.getTemperature();
}

byte DateTimeBoxCar::CalculoDoW(byte *dia, byte *mes, int *ano) {

// DoW =  k mod 7, onde 0 = Sabado e Sexta = 6

  byte  mesZeller = *mes < 3 ? *mes + 12  : *mes;
  int   anoZeller = *mes < 3 ? *ano - 1   : *ano;

  size_t k =  *dia + (2 * mesZeller) + (3 * (mesZeller + 1) / 5) + 
              anoZeller + (anoZeller / 4) - (anoZeller / 100) + (anoZeller / 400) + 2;

  return k % 7;    
}

