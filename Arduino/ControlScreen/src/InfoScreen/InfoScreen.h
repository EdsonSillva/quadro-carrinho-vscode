/*
    Módulo para guardar as informações de atualização da tela do Nextion
    
    Desenvolvido por Edson Silva
    Date: 10/07/23

*/

#ifndef __INFOSCREEN_H__
#define __INFOSCREEN_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __TYPEDEFSCREEN_H__
#include "../typedef/typedefScreen.h"
#endif


class InfoScreen
{
private:

enum eTipoInfo {
    Screen,
    Sistema
};

dadosScreen_t   _infoScreen;
bool            _existeAlteracao;       // Se houver algum dado alterado esta variável deve ser setada em true

bool setInfoData(dados_t *info);
bool setInfoDia(dados_t *info);
bool setInfoMes(dados_t *info);
bool setInfoAno(dados_t *info);
bool setInfoDoW(dados_t *info);

bool setInfoTempo(dados_t *info);
bool setInfoHora(dados_t *info);
bool setInfoMin(dados_t *info);
bool setInfoSec(dados_t *info);

bool setInfoAmbiente(dados_t *info);
bool setInfoTemperatura(dados_t *info);
bool setInfoUmidade(dados_t *info);
bool setInfoLuminosidade(dados_t *info);

bool setInfoTemperaturaSys(dados_t *info);



public:

    InfoScreen();
    ~InfoScreen();

    void setInfoScreen(dados_t *info);
    bool existeAlteracao();
    
    dados_t getInfosAlterados();

};


#endif  // __INFOSCREEN_H__
