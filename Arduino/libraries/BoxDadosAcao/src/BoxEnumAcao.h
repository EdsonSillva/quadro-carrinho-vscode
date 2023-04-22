/*
    Controle dos enumeration das ações disponiveis
*/

#ifndef __BOXENUMACAO_H__
#define __BOXENUMACAO_H__

/**
 * @brief   Enumeration para indicar qual Ação ou Tema foi solicitado e processar a ação relacionada. 
 *          Os números indicados em cada item são os mesmo que o Nextion retorna ao selecionar uma ação.
 */
enum eAcaoBox {

    semAcao                 = 0,
    acaoAceso               = 49,
    acaoXadrez              = 52,
    acaoLinha               = 55,
    acaoColuna              = 58,
    acaoCascata             = 61,
    acaoMsg                 = 64,
    acaoBatman              = 67,
    acaoStarWar             = 70,
    acaoVelozFurioso        = 73,
    acaoMoto                = 76,
    acaoPorche              = 79,
    acaoFerrari             = 82,
    acaoPagani              = 85,
    acaoMCLaren             = 88,
    acaoChevrolet           = 91,
    acaoAstomMart           = 94,
    acaoJaguar              = 97,
    acaoAudi                = 100,
    acaoBMW                 = 103,
    acaoMercedes            = 106,
    acaoTesla               = 109,
    acaoLamborghini         = 112,
    acaoNissan              = 115,
    acaoDodge               = 118,
    acaoBuick               = 121,
    acaoVolks               = 124,
    acaoFord                = 127,
    acaoFiat                = 130,
    acaoCadillac            = 133,
    acaoHonda               = 136,
    acaoAcura               = 139,
    acaoBentley             = 142,
    acaoMazda               = 145,
    acaoBugatti             = 148,

};

#endif  // __BOXENUMACAO_H__
