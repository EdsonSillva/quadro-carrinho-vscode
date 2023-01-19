#line 1 "c:\\Users\\edson\\OneDrive\\Documentos\\.Desenvolvimento\\Arduino\\Projetos\\IDE-vscode\\quadro-carrinho-vscode\\Arduino\\Box\\src\\BoxCar.h"
/*
  Classe Base para controle do tratamento das ações no quadro de carrinho

  Desenvolvido por Edson Silva
  Date: 27/05/18
  
*/

#ifndef __BOXCAR_H__
#define __BOXCAR_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __BOXMEMORYEEPROM_H__
#include <BoxMemoryEEPROM.h>
#endif

#ifndef __BOXDADOSACAO_H__
#include <BoxDadosAcao.h>
#endif

#ifndef __BOXBUZZERCAR_H__
#include <BoxBuzzerCar.h>
#endif


class BoxCar
{
private:
    /* data */
public:
    BoxCar(/* args */);
    ~BoxCar();
};



#endif  // __BOXCAR_H__

