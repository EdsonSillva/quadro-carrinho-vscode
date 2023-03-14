

#ifndef __MASCARALETRA_H__
#define __MASCARALETRA_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif


class MascaraLetra
{
private:


public:
    MascaraLetra();
    ~MascaraLetra();
    void montarMascara(char Letra, char LetraMascarada[], byte *pFimBitMascara);
    void montarMascaraSaudacao(word MapaBox[]);

};


#endif  // __MASCARALETRA_H__