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

    semAcaoBox              =   0,
    acaoAceso               =  49,
    acaoXadrez              =  52,
    acaoLinha               =  55,
    acaoColuna              =  58,
    acaoCascata             =  61,
    acaoSnake               =  64,
    acaoMsg                 =  67,
    acaoBatman              =  70,
    acaoStarWar             =  73,
    acaoVelozFurioso        =  76,
    acaoMoto                =  79,
    acaoPorche              =  82,
    acaoFerrari             =  85,
    acaoPagani              =  88,
    acaoMCLaren             =  91,
    acaoChevrolet           =  94,
    acaoAstomMart           =  97,
    acaoJaguar              = 100,
    acaoAudi                = 103,
    acaoBMW                 = 106,
    acaoMercedes            = 109,
    acaoTesla               = 112,
    acaoLamborghini         = 115,
    acaoNissan              = 118,
    acaoDodge               = 121,
    acaoBuick               = 124,
    acaoVolks               = 127,
    acaoFord                = 130,
    acaoFiat                = 133,
    acaoCadillac            = 136,
    acaoHonda               = 139,
    acaoAcura               = 142,
    acaoBentley             = 145,
    acaoMazda               = 148,
    acaoBugatti             = 151,

};


enum eQualAcao {
    semAcao                 = 0,
    executarAcao            = 1,
    pararAcao               = 2
};


enum eAcaoSistema {
    semAcaoSistema          = 0,
    configurarData          = 1,
    configurarHora          = 2,
    standBy                 = 3,
    configurarBeep          = 4,
    carregarTemas           = 5,
    salvarTemas             = 6,
};

#endif  // __BOXENUMACAO_H__

