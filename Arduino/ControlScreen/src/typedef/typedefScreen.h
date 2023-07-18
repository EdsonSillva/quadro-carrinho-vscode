
/*
    Tipos definidos para serem usados no projeto Screen

    Autor:  Edson Silva
    Data:   07/02/2023
*/


#ifndef __TYPEDEFSCREEN_H__
#define __TYPEDEFSCREEN_H__


#ifndef Arduino_h
#include <Arduino.h>
#endif

typedef struct {
    byte    valor;  // Controle de alteração no valor (no ultimo bit 0b10000000)
    bool    mudou;
} valor_t;

typedef struct {
    valor_t    Dia;
    valor_t    Mes;
    valor_t    Ano;
    valor_t    DoW;
} dataScreen_t;

typedef struct {
    valor_t    Hora;
    valor_t    Min;
    valor_t    Sec;
} horaScreen_t;

typedef struct {
    valor_t    Temperatura; 
    valor_t    Umidade;
    valor_t    Luminosidade;
} ambiente_t;

// incluir uma variável do tipo uint16_t para controlar as mlterações nas variáveis (ganhar 7 bytes)
typedef struct {

    dataScreen_t    Data;
    horaScreen_t    Tempo;
    ambiente_t      Ambiente;
    valor_t         TemperaturaSys;
    uint8_t         Alterado;
    
} dados_t,
  dadosSistema_t,
  dadosScreen_t;

#endif  // __TYPEDEFSCREEN_H__
