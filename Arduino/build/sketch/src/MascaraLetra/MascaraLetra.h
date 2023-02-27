#line 1 "C:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\ControlBox\\src\\MascaraLetra\\MascaraLetra.h"


#ifndef __MASCARALETRA_H__
#define __MASCARALETRA_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif


class MascaraLetra
{
private:


public:
    MascaraLetra(/* args */);
    ~MascaraLetra();
    void montarMascara(char Letra, char LetraMascarada[], byte *pFimBitMascara);
};


#endif  // __MASCARALETRA_H__