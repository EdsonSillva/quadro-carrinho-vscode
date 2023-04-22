
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

typedef struct {
    uint8_t     Coluna;
    int8_t      Linha;
    int8_t      LinhaInicial;
    uint8_t     Arrasto;
    uint8_t     Percentual;
    bool        Finalizado;
} cascata_t;

typedef struct {
    byte        R;
    byte        G;
    byte        B;
} boxRGB_t;

// union COLORUnion_t
// {
//     boxRGB_t RGBBox;
//     unsigned int value;
// } ColorBox_t;

typedef byte linCol;

typedef struct {
    linCol      Posicao;
    boxRGB_t    RGB;
} box_t;

typedef struct {
    byte        Arrasto;
    box_t       Corpo[12];
} snake_t;

typedef box_t alvo_t;



#endif  // __TYPEDEFBOX_H__