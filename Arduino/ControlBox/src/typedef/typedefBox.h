
/*
    Tipos definidos para serem usados no projeto

    Autor:  Edson Silva
    Data:   07/02/2023
*/


#ifndef __TYPEDEFBOX_H__
#define __TYPEDEFBOX_H__


#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif


typedef void (*funcAcaoClass_t)(bool, byte, BoxDadosAcao);
typedef void (*FuncAcaoVoid)(bool, byte, byte, byte, byte);
typedef void (*FuncAcao)(bool, BoxDadosAcao);

typedef struct cascata_t {
    uint8_t   Coluna;
    int8_t    Linha;
    uint8_t   Arrasto;
    float     Percentual;
    bool      Finalizado;
} cascata_t;

#endif  // __TYPEDEFBOX_H__