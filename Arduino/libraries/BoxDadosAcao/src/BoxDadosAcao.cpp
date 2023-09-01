/*
    Metodos da classe BoxDadosAcao para controle das ações 
    entre arduino e Nextion Screen

    Data: 27/05/18
    Autor: Edson Silva

*/

#include "BoxDadosAcao.h"


BoxDadosAcao::BoxDadosAcao() { }
BoxDadosAcao::~BoxDadosAcao() { }

void BoxDadosAcao::setCodeAcao(byte CodeAcao) {
    _CodeAcao = CodeAcao;
}

void BoxDadosAcao::setQualAcao(eQualAcao qualAcao) {
    _QualAcao = qualAcao;
}

eQualAcao BoxDadosAcao::getQualAcao() {
    return _QualAcao;
}

void BoxDadosAcao::setExecutando(bool valor){
    _Executando = valor;
}

bool BoxDadosAcao::getExecutando() {
    return _Executando;
}

void BoxDadosAcao::limpaDados() {
    _R      = 0, _G      = 0, _B      = 0, _Brilho = 0;
    _GammaR = 0, _GammaG = 0, _GammaB = 0;
}

void BoxDadosAcao::setRGBB(byte R, byte G, byte B, byte Brilho) {
    _R = R;
    _G = G;
    _B = B;
    _Brilho = Brilho;
}

void BoxDadosAcao::setRGBGamma(byte GammaR, byte GammaG, byte GammaB) {
    _GammaR = GammaR;
    _GammaG = GammaG;
    _GammaB = GammaB;
}

void BoxDadosAcao::setCodeAcaoRGBB(byte CodeAcao, byte R, byte G, byte B, byte Brilho) {
    setCodeAcao(CodeAcao);
    setRGBB(R, G, B, Brilho);
}

// /* @brief deprecated @deprecated */
// String BoxDadosAcao::gerarChaveAcao() {
//     _ChaveAcaoAnterior = _ChaveAcaoAtual;
//     _ChaveAcaoAtual = ((String)(String(_CodeAcao) + String(_R) + String(_G) + String(_B) + String(_Brilho)));
// }

// /* @brief deprecated @deprecated */
// String BoxDadosAcao::getChaveAcao() {
//     return _ChaveAcaoAtual;
// }

// /* @brief deprecated @deprecated */
// String BoxDadosAcao::getChaveAcaoAnterior() {
//     return _ChaveAcaoAnterior;
// }

// /* @brief deprecated @deprecated */
// bool BoxDadosAcao::chaveAcaoAnteriorAtualIgual() {
//     return _ChaveAcaoAnterior == _ChaveAcaoAtual ?  true : 
//                                                     false;
// }

byte BoxDadosAcao::getCodeAcao() {
    return _CodeAcao;
}

byte BoxDadosAcao::getIDAcaoMsg() {
    return _IDAcaoMsg;
}

bool BoxDadosAcao::chaveAcaoAtualIsMsg() {
    return _CodeAcao == _IDAcaoMsg ?    true : 
                                        false;
}

byte BoxDadosAcao::getR() {
    return _R;
}

byte BoxDadosAcao::getG() {
    return _G;
}

byte BoxDadosAcao::getB() {
    return _B;
}

byte BoxDadosAcao::getGammaR() {
    return _GammaR;
}

byte BoxDadosAcao::getGammaG() {
    return _GammaG;
}

byte BoxDadosAcao::getGammaB() {
    return _GammaB;
}

void BoxDadosAcao::setBrilho(byte Brilho) {
    _Brilho = Brilho;
}

byte BoxDadosAcao::getBrilho() {
    return _Brilho;
}

byte BoxDadosAcao::getSizeTemaBat() {
    return _sizeTemaBat;
}

void BoxDadosAcao::setDadoEEPROMIno(int Inicio, int Fim, byte Dado = 0x00) {
    for (byte posicao = Inicio; posicao <= Fim ; posicao++)
    {
        EEPROM.write(posicao, Dado);
    }
}

void BoxDadosAcao::inicializaEEPROMIno() {
    EEPROM.begin();
}

/* @brief A EEPROM do arduino tem estar inicializada as 50 primeiras posições com 0
   e o restante com 255
*/
void BoxDadosAcao::inicializaTemaBat() {
    setDadoEEPROMIno(_batAddressIni, _sizeBat - 1, 0x00);
}

int BoxDadosAcao::posicaoInicialDadoTema(byte PosicaoTemaBat) {
    return ((_addressIniBoxes + (PosicaoTemaBat * _sizeTemaBat)) - _sizeTemaBat);
}

int BoxDadosAcao::posicaoFinalDadoTema(byte PosicaoTemaBat) {
    return (_addressIniBoxes + (PosicaoTemaBat * _sizeTemaBat));
}

void BoxDadosAcao::limpaDadosTemaBat(byte PosicaoTema) {

    int posicaoInicialTema  = posicaoInicialDadoTema(PosicaoTema);
    int posicaoFinalTema    = posicaoFinalDadoTema(PosicaoTema);

    setDadoEEPROMIno(posicaoInicialTema, posicaoFinalTema - 1, 0x00);
}

byte BoxDadosAcao::getPosicaoTemaBatByDado(byte const *DadoPesquisa) {

    for (int posicaoBat = _batAddressIni; posicaoBat <= _sizeBat ; posicaoBat++)
    {
        if ((byte)EEPROM.read(posicaoBat) == *DadoPesquisa) 
            return (byte)posicaoBat;
    }
    return 0;       // Indicando q não existe o dado na BAT (Box Alocation Table)

}

byte BoxDadosAcao::getPosicaoTemaBat(byte CodigoTema) {
    return getPosicaoTemaBatByDado(&CodigoTema);
}

byte BoxDadosAcao::getPosicaoLivreTemaBat() {

    byte Zero = 0;      // Indicação de posição livre
    return getPosicaoTemaBatByDado(&Zero);

}

byte BoxDadosAcao::setPosicaoLivreTemaBat(byte CodigoTema) {

    byte posicaoLivre = getPosicaoLivreTemaBat();

    if(posicaoLivre > 0) {
        EEPROM.write((int)posicaoLivre, CodigoTema);
    }
    return posicaoLivre;

}

byte BoxDadosAcao::lerDadosTemaBat(byte Boxes[], byte PosicaoTema) {

    int posicaoInicialTema  = posicaoInicialDadoTema(PosicaoTema);
    int posicaoFinalTema    = posicaoFinalDadoTema(PosicaoTema);
    byte posicaoBoxes       = 0;

    for (int posicao = posicaoInicialTema; posicao < posicaoFinalTema; posicao++)
    {
    
        Boxes[posicaoBoxes] =  (byte)EEPROM.read(posicao);
        if(Boxes[posicaoBoxes] == 0x00) {
            break;         // Abandona o metodo por não ter mais dados
        }
        posicaoBoxes++;
    }

    return posicaoBoxes;

}

#pragma region Metodos de conversão de Linha, Coluna e LinhaColuna

/*
    @brief Conversão de dois bytes em um, onde os primeiros 4 bits é a represetação das 14 linhas no quadro
           e os outros 4 bits representa as 15 colunas no quadro.

           Ex. 0b11110000, onde 1111: as 14 linhas do quadro, 
                                0000: as 15 colunas do quadro.

    @param Linha: Informar um númenro entre 1 a 14. Este númenro representa uma linha do quadro de carrinhos.
    @param Coluna: Informar um númenro entre 1 a 15. Este númenro representa uma coluna do quadro de carrinhos.

    @return Um número onde representa a linha e coluna do quadro. Utilizar os metodos numLimha() e numColuna()
            para extarir a informação correta
*/
byte BoxDadosAcao::converteLinhaColuna(byte Linha, byte Coluna) {
    return (Linha << 4) | Coluna;
}

/*
    @brief Retira o número da Linha do número informado.

    @param LinhaColuna: Este número tem que ter sido convertido pelo método converteLinhaColuna()

    @return Um número onde representa a linha do quadro.
*/
byte BoxDadosAcao::numLinha(byte LinhaColuna) {
    return (byte)LinhaColuna >> 4;
}

/*
    @brief Retira o número da Coluna do número informado.

    @param LinhaColuna: Este número tem que ter sido convertido pelo método converteLinhaColuna()

    @return Um número onde representa a coluna do quadro.
*/
byte BoxDadosAcao::numColuna(byte LinhaColuna) {
    //return 0b00001111 & LinhaColuna; 
    return 0x0f & LinhaColuna;
}

#pragma endregion

