/*
    Controle dos enumeration usados no projeto para as ações nos box's
*/

#ifndef __ENUMPOSICAOBOX_H__
#define __ENUMPOSICAOBOX_H__

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

#endif  // __ENUMPOSICAOBOX_H__
