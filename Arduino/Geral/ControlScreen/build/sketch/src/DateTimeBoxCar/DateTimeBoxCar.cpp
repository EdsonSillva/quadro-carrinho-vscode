#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Tela\\src\\DateTimeBoxCar\\DateTimeBoxCar.cpp"


#include "DateTimeBoxCar.h"


DateTimeBoxCar::DateTimeBoxCar(/* args */) { }

DateTimeBoxCar::~DateTimeBoxCar() { }

/*
  Inicializa o device entrando via Wire

  @param Clock24hs indica se a contagem de horas vai ser em 12hs ou 24hs. Informe true=24hs ou false=12hs
  
*/
void DateTimeBoxCar::iniciarDS3231(bool Clock24hs) {

    // Serial.println(F("... DateTimeBoxCar::iniciarDS3231(bool Clock24hs)"));
    // delay(100);

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
  _RTC.setHour(Hora);
  _RTC.setMinute(Minuto);
  _RTC.setSecond(Segundo);
}

void DateTimeBoxCar::getHoraOnDS3231(byte *Hora, byte *Minuto, byte *Segundo) {
  bool h12, PM;
  *Hora=_RTC.getHour(h12,PM);
  *Minuto=_RTC.getMinute();
  *Segundo=_RTC.getSecond();
}

bool DateTimeBoxCar::setDataOnDS3231(byte Dia, byte Mes, byte Ano, byte DoW) {
  _RTC.setDate(Dia);
  _RTC.setMonth(Mes);
  _RTC.setYear(Ano);
  _RTC.setDoW(DoW);
}

void DateTimeBoxCar::getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW) {
  
  bool Century=false;
  
  *Dia=_RTC.getDate();
  *Mes=_RTC.getMonth(Century);
  *Ano=_RTC.getYear();
  *DoW=_RTC.getDoW();
}

void DateTimeBoxCar::getDataOnDS3231(byte *Dia, byte *Mes, byte *Ano, byte *DoW, int *Milenio) {
  
  bool Century=false;
  
  *Dia=_RTC.getDate();
  *Mes=_RTC.getMonth(Century);
  *Ano=_RTC.getYear();
  // *DoW=RTC.getDoW();
  *DoW = getDoWork(Dia, Mes, Ano, Milenio);
}

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

