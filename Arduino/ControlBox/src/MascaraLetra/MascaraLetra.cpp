


#include "MascaraLetra.h"


MascaraLetra::MascaraLetra() { }
MascaraLetra::~MascaraLetra() { }

void MascaraLetra::montarMascaraSaudacao(word MapaBox[]) {
	
    MapaBox[0]  =  0b0000000000000000;    // Linha  1 do quadro e cada bit representa a coluna
    MapaBox[1]  =  0b0111001100011100;    // Linha  1 do quadro e cada bit representa a coluna
    MapaBox[2]  =  0b0100001010010000;    // Linha  2 do quadro e cada bit representa a coluna
    MapaBox[3]  =  0b0110001010011100;    // Linha  3 do quadro e cada bit representa a coluna
    MapaBox[4]  =  0b0100001010000100;    // Linha  4 do quadro e cada bit representa a coluna
    MapaBox[5]  =  0b0111001100011100;    // Linha  5 do quadro e cada bit representa a coluna
    MapaBox[6]  =  0b0000000000000000;    // Linha  6 do quadro e cada bit representa a coluna
    MapaBox[7]  =  0b0000111111100000;    // Linha  7 do quadro e cada bit representa a coluna
    MapaBox[8]  =  0b0001000000010000;    // Linha  8 do quadro e cada bit representa a coluna
    MapaBox[9]  =  0b0010010001001000;    // Linha  9 do quadro e cada bit representa a coluna
    MapaBox[10] =  0b0100000100000100;    // Linha 1  do quadro e cada bit representa a coluna
    MapaBox[11] =  0b0100000100000100;    // Linha 11 do quadro e cada bit representa a coluna
    MapaBox[12] =  0b0010011111001000;    // Linha 12 do quadro e cada bit representa a coluna
    MapaBox[13] =  0b0001100000110000;    // Linha 13 do quadro e cada bit representa a coluna
    MapaBox[14] =  0b0000011111000000;    // Linha 14 controle
    MapaBox[15] =  0b0000000000000000;    // Linha 15 de controle da cor para Label

}


void MascaraLetra::montarMascara(char Letra, char LetraMascarada[], byte *pFimBitMascara) {

    switch (Letra){

        case ' ':
            *pFimBitMascara=7;
            LetraMascarada[0]=0b00000000;
            LetraMascarada[1]=0b00000000;
            LetraMascarada[2]=0b00000000;
            LetraMascarada[3]=0b00000000;
            LetraMascarada[4]=0b00000000;
        break;

        case '.':
            *pFimBitMascara=7;
            LetraMascarada[0]=0b00000000;
            LetraMascarada[1]=0b00000000;
            LetraMascarada[2]=0b00000000;
            LetraMascarada[3]=0b00000000;
            LetraMascarada[4]=0b10000000;
        break;

        case '/':
            *pFimBitMascara=3;
            LetraMascarada[0]=0b00001000;
            LetraMascarada[1]=0b00010000;
            LetraMascarada[2]=0b00100000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b10000000;
        break;

        case '?':
            *pFimBitMascara=4;
            LetraMascarada[0]=0b01100000;
            LetraMascarada[1]=0b10010000;
            LetraMascarada[2]=0b00100000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b10000000;
        break;

        case '0':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case '1':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b01000000;
            LetraMascarada[1]=0b01000000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b11100000;
        break;

        case '2':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
        break;

        case '3':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b01100000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b11100000;
        break;

        case '4':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b00100000;
        break;

        case '5':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11000000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b11000000;
        break;

        case '6':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case '7':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b00100000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b00100000;
        break;

        case '8':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case '9':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'a': case 'A':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b10100000;
        break;

        case 'b': case 'B':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10000000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'c': case 'C':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b10000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
        break;

        case '~':                   // ç e Ç (usando o ~ porque o ç não funciona)
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b10000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
            LetraMascarada[5]=0b01000000;
        break;

        case 'd': case 'D':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b00100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'e': case 'E':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'f': case 'F':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b10000000;
        break;

        case 'g': case 'G':
            *pFimBitMascara=4;
            LetraMascarada[0]=0b11110000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b10110000;
            LetraMascarada[3]=0b10010000;
            LetraMascarada[4]=0b11110000;
        break;

        case 'h': case 'H':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b10100000;
        break;

        case 'i': case 'I':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b01000000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'j': case 'J':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b00100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b00100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'k': case 'K':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b11000000;
            LetraMascarada[2]=0b10000000;
            LetraMascarada[3]=0b11000000;
            LetraMascarada[4]=0b10100000;
        break;

        case 'l': case 'L':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10000000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b10000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'm': case 'M':
            *pFimBitMascara=3;
            LetraMascarada[0]=0b11011000;
            LetraMascarada[1]=0b11111000;
            LetraMascarada[2]=0b11111000;
            LetraMascarada[3]=0b10101000;
            LetraMascarada[4]=0b10101000;
        break;

        case 'n': case 'N':
            *pFimBitMascara=4;
            LetraMascarada[0]=0b10010000;
            LetraMascarada[1]=0b11010000;
            LetraMascarada[2]=0b10110000;
            LetraMascarada[3]=0b10110000;
            LetraMascarada[4]=0b10010000;
        break;

        case 'o': case 'O':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'p': case 'P':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b10000000;
        break;

        case 'q': case 'Q':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11000000;
        break;

        case 'r': case 'R':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b11000000;
            LetraMascarada[4]=0b10100000;
        break;

        case 's': case 'S':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b10000000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b00100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 't': case 'T':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b01000000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b01000000;
        break;

        case 'u': case 'U':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b11100000;
        break;

        case 'v': case 'V':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b10100000;
            LetraMascarada[4]=0b01000000;
        break;

        case 'w': case 'W':
            *pFimBitMascara=3;
            LetraMascarada[0]=0b10101000;
            LetraMascarada[1]=0b10101000;
            LetraMascarada[2]=0b11111000;
            LetraMascarada[3]=0b11111000;
            LetraMascarada[4]=0b11011000;
        break;

        case 'x': case 'X':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b11100000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b11100000;
            LetraMascarada[4]=0b10100000;
        break;

        case 'y': case 'Y':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b10100000;
            LetraMascarada[1]=0b10100000;
            LetraMascarada[2]=0b10100000;
            LetraMascarada[3]=0b01000000;
            LetraMascarada[4]=0b01000000;
        break;

        case 'z': case 'Z':
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b00100000;
            LetraMascarada[2]=0b01000000;
            LetraMascarada[3]=0b10000000;
            LetraMascarada[4]=0b11100000;
        break;

        default:
            *pFimBitMascara=5;
            LetraMascarada[0]=0b11100000;
            LetraMascarada[1]=0b11100000;
            LetraMascarada[2]=0b11100000;
            LetraMascarada[3]=0b11100000;
            LetraMascarada[4]=0b11100000;
    }

}
