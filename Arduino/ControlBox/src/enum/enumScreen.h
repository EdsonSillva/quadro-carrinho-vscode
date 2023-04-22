/*
    Controle dos enumeration usados no projeto para as ações nos box's
*/

#ifndef __ENUMSCREEN_H__
#define __ENUMSCREEN_H__

/**
 * Enumeration para indicar a posição do box no quadro 
 */
enum eBoxPosicao {

    semPosicao              = 0,
    boxTop                  = 1,
    boxBottom               = 2,
    boxLeft                 = 3,
    boxRight                = 4,
    boxNoAlvo               = 5,
    PosicaoDadaLinha        = 6,
    PosicaoDadaColuna       = 7

};

/**
 * Enumeration para indicar direção baseado em dois pontos no quadro 
 */
enum eBoxDirecao {

    semDirecao              = 0,
    boxTopBottom            = 1,
    boxBottomTop            = 2,
    boxLeftRight            = 3,
    boxRightLeft            = 4

};

/**
 * Enumeration para indicar movimento do snake em relação ao alvo no quadro 
 */
enum eBoxMovimentoSnake {
     
    semMovimento            = 0,
    boxLinha                = 1,
    boxColuna               = 2

};



#endif  // __ENUMSCREEN_H__
