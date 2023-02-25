/*
    Controle dos enumeration das ações disponiveis
*/

#ifndef __ENUMACAO_H__
#define __ENUMACAO_H__

/**
 * Enumeration para indicar qual tema foi solicitado e acerder o box relacionado 
 */
enum eAcao {

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

#endif  // __ENUMACAO_H__

/*

    switch (CodeAcao) {

        case 0:                                                    // Reset Ação
        case AcaoIcon001:                                          // Ação Manter os Leds Aceso
        case AcaoIcon002:                                          // Ação acender Xadrez box
        case AcaoIcon003:                                          // Ação acender Linhas box
        case AcaoIcon004:                                          // Ação acender Colunas box 
        case AcaoIcon005:                                          // Ação cascata 
        case AcaoIcon006:                                          // Ação Msg box 
        case AcaoIcon007:                                          // Ação acender Batman box 
        case AcaoIcon008:                                          // Ação acender star War box 
        case AcaoIcon009:                                          // Ação acender Veloz. fur. box 
        case AcaoIcon010:                                          // Ação acender moto box 
        case AcaoIcon011:                                          // Ação acender porche box 
        case AcaoIcon012:                                          // Ação acender ferrari box 
        case AcaoIcon013:                                          // Ação acender pagani box 
        case AcaoIcon014:                                          // Ação acender mclaren box 
        case AcaoIcon015:                                          // Ação acender chevrolet box 
        case AcaoIcon016:                                          // Ação acender astom mart box 
        case AcaoIcon017:                                          // Ação acender jaguar box 
        case AcaoIcon018:                                          // Ação acender audi box 
        case AcaoIcon019:                                          // Ação acender bmw box 
        case AcaoIcon020:                                          // Ação acender mercedes box 
        case AcaoIcon021:                                          // Ação acender tesla box 
        case AcaoIcon022:                                          // Ação acender lamborghini box 
        case AcaoIcon023:                                          // Ação acender nissan box 
        case AcaoIcon024:                                          // Ação acender dodge box 
        case AcaoIcon025:                                          // Ação acender buick box 
        case AcaoIcon026:                                          // Ação acender volks box 
        case AcaoIcon027:                                          // Ação acender ford box 
        case AcaoIcon028:                                          // Ação acender fiat box 
        case AcaoIcon029:                                          // Ação acender cadillac box 
        case AcaoIcon030:                                          // Ação acender honda box 
        case AcaoIcon031:                                          // Ação acender acura box 
        case AcaoIcon032:                                          // Ação acender bentley box 
        case AcaoIcon033:                                          // Ação acender mazda box 
        case AcaoIcon034:                                          // Ação acender bugatti box 
        case AcaoIcon035:                                          // Sem Vai-Vem (vários tipos - foram os promeiros códigos)
        case AcaoIcon036:                                          // Ação Debug 


*/