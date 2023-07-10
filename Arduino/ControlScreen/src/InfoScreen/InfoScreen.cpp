
#include "InfoScreen.h"


InfoScreen::InfoScreen() {

    // _infoScreen = {{0, 0, 0, 0}, 
    //                {0, 0, 0},
    //                {0, 0},
    //                0
    //                };
}

InfoScreen::~InfoScreen() { }

bool InfoScreen::existeAlteracao() {
    return _existeAlteracao;
}

void InfoScreen::setInfoScreen(dados_t *info) {

    bool dataMudou      = setInfoData(info);
    bool tempoMudou     = setInfoHora(info);
    bool ambienteMudou  = setInfoAmbiente(info);
    bool tempSysMudou   = setInfoTemperaturaSys(info);

    _existeAlteracao = dataMudou || tempoMudou || ambienteMudou || tempSysMudou;

}

#pragma region Tratamento de Data

bool InfoScreen::setInfoData(dados_t *info) {

    bool DiaMudou = setInfoDia(info);
    bool MesMudou = setInfoMes(info);
    bool AnoMudou = setInfoAno(info);
    bool DoWMudou = setInfoDoW(info);

    return DiaMudou || MesMudou || AnoMudou || DoWMudou;

}

bool InfoScreen::setInfoDia(dados_t *info) {

    _infoScreen.Data.Dia.mudou = _infoScreen.Data.Dia.valor != 
                                 info->Data.Dia.valor ? 
                                 true : false;
    
    _infoScreen.Data.Dia.valor = info->Data.Dia.valor;

    return _infoScreen.Data.Dia.mudou;

}

bool InfoScreen::setInfoMes(dados_t *info) {

    _infoScreen.Data.Mes.mudou = _infoScreen.Data.Mes.valor != 
                                 info->Data.Mes.valor ? 
                                 true : false;
    
    _infoScreen.Data.Mes.valor = info->Data.Mes.valor;

    return _infoScreen.Data.Mes.mudou;

}

bool InfoScreen::setInfoAno(dados_t *info) {

    _infoScreen.Data.Ano.mudou = _infoScreen.Data.Ano.valor != 
                                 info->Data.Ano.valor ? 
                                 true : false;
    
    _infoScreen.Data.Ano.valor = info->Data.Ano.valor;

    return _infoScreen.Data.Ano.mudou;

}

bool InfoScreen::setInfoDoW(dados_t *info) {

    _infoScreen.Data.DoW.mudou = _infoScreen.Data.DoW.valor != 
                                 info->Data.DoW.valor ? 
                                 true : false;
    
    _infoScreen.Data.DoW.valor = info->Data.DoW.valor;

    return _infoScreen.Data.DoW.mudou;

}

#pragma endregion Tratamento de Data


#pragma region Tratamento de Hora

bool InfoScreen::setInfoTempo(dados_t *info) {

    bool HoraMudou = setInfoHora(info);
    bool MinMudou  = setInfoMin(info);
    bool SecMudou  = setInfoSec(info);

    return HoraMudou || MinMudou || SecMudou;

}

bool InfoScreen::setInfoHora(dados_t *info) {

    _infoScreen.Tempo.Hora.mudou = _infoScreen.Tempo.Hora.valor != 
                                 info->Tempo.Hora.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Hora.valor = info->Tempo.Hora.valor;

    return _infoScreen.Tempo.Hora.mudou;

}

bool InfoScreen::setInfoMin(dados_t *info) {

    _infoScreen.Tempo.Min.mudou = _infoScreen.Tempo.Min.valor != 
                                 info->Tempo.Min.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Min.valor = info->Tempo.Min.valor;

    return _infoScreen.Tempo.Min.mudou;

}

bool InfoScreen::setInfoSec(dados_t *info) {

    _infoScreen.Tempo.Sec.mudou = _infoScreen.Tempo.Sec.valor != 
                                 info->Tempo.Sec.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Sec.valor = info->Tempo.Sec.valor;

    return _infoScreen.Tempo.Sec.mudou;

}

#pragma endregion Tratamento de Hora


#pragma region Tratamento de Ambiente

bool InfoScreen::setInfoAmbiente(dados_t *info) {

    bool TemperaturaMudou   = setInfoTemperatura(info);
    bool UmidadeMudou       = setInfoUmidade(info);
    bool LuminosidadeMudou  = setInfoUmidade(info);

    return TemperaturaMudou || UmidadeMudou || LuminosidadeMudou;

}

bool InfoScreen::setInfoTemperatura(dados_t *info) {

    _infoScreen.Ambiente.Temperatura.mudou = _infoScreen.Ambiente.Temperatura.valor != 
                                            info->Ambiente.Temperatura.valor ? 
                                            true : false;
    
    _infoScreen.Ambiente.Temperatura.valor = info->Ambiente.Temperatura.valor;

    return _infoScreen.Ambiente.Temperatura.mudou;

}

bool InfoScreen::setInfoUmidade(dados_t *info) {

    _infoScreen.Ambiente.Umidade.mudou = _infoScreen.Ambiente.Umidade.valor != 
                                          info->Ambiente.Umidade.valor ? 
                                          true : false;
    
    _infoScreen.Ambiente.Umidade.valor = info->Ambiente.Umidade.valor;

    return _infoScreen.Ambiente.Umidade.mudou;

}

bool InfoScreen::setInfoLuminosidade(dados_t *info) {

    _infoScreen.Ambiente.Luminosidade.mudou = _infoScreen.Ambiente.Luminosidade.valor != 
                                              info->Ambiente.Luminosidade.valor ? 
                                              true : false;
    
    _infoScreen.Ambiente.Luminosidade.valor = info->Ambiente.Luminosidade.valor;

    return _infoScreen.Ambiente.Luminosidade.mudou;

}

#pragma endregion Tratamento de Ambiente


#pragma region Tratamento de Sistema

bool InfoScreen::setInfoTemperaturaSys(dados_t *info) {

    _infoScreen.TemperaturaSys.mudou = _infoScreen.TemperaturaSys.valor != 
                                       info->TemperaturaSys.valor ? 
                                       true : false;
    
    _infoScreen.TemperaturaSys.valor = info->TemperaturaSys.valor;

    return _infoScreen.TemperaturaSys.mudou;

}

#pragma endregion Tratamento de Sistema



