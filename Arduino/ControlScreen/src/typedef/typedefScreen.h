
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
    byte    valor;
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

typedef struct {

    dataScreen_t    Data;
    horaScreen_t    Tempo;
    ambiente_t      Ambiente;
    valor_t         TemperaturaSys;
    
} dados_t,
  dadosSistema_t,
  dadosScreen_t;


// Typedef do projeto Control Box
// ##############################

// typedef struct {
//     uint8_t     Coluna;
//     int8_t      Linha;
//     int8_t      LinhaInicial;
//     uint8_t     Arrasto;
//     uint8_t     Percentual;
//     bool        Finalizado;
// } cascata_t;

// typedef struct {
//     byte        R;
//     byte        G;
//     byte        B;
// } boxRGB_t;

// typedef byte linCol;

// typedef struct {
//     linCol      Posicao;
//     boxRGB_t    RGB;
// } box_t;

// typedef struct {
//     byte        Arrasto;
//     box_t       Corpo[_CorpoSnake_];
//     boxRGB_t    CorFundo;
// } snake_t;

// typedef box_t alvo_t;


#endif  // __TYPEDEFSCREEN_H__