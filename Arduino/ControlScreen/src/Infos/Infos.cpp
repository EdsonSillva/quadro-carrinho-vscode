
#include "Infos.h"


#pragma region Classe InfoScreen

Infos::InfoScreen::InfoScreen() { }

Infos::InfoScreen::~InfoScreen() { }

bool Infos::InfoScreen::existeAlteracao() {
    return _existeAlteracao;
}

void Infos::InfoScreen::setInfoScreen(dados_t *info) {

    bool dataMudou      = setInfoData(info);
    bool tempoMudou     = setInfoHora(info);
    bool ambienteMudou  = setInfoAmbiente(info);
    bool tempSysMudou   = setInfoTemperaturaSys(info);

    _existeAlteracao = dataMudou || tempoMudou || ambienteMudou || tempSysMudou;

}

bool Infos::InfoScreen::foiAlterado(eTipoDadoInfo tipo) {

    uint8_t mask = 0b00000000;

    switch (tipo) {

        case eTipoDadoInfo::DataInfo:
            mask = 0b00000001;
        break;

        case eTipoDadoInfo::TempoInfo:
            mask = 0b00000010;
        break;

        case eTipoDadoInfo::AmbienteInfo:
            mask = 0b00000100;
        break;

        case eTipoDadoInfo::TempreraturaSysInfo:
            mask = 0b00001000;
        break;

    }

    return  mask & _infoScreen.Alterado;

}


#pragma region Tratamento de Data

bool Infos::InfoScreen::setInfoData(dados_t *info) {

    bool DiaMudou = setInfoDia(info);
    bool MesMudou = setInfoMes(info);
    bool AnoMudou = setInfoAno(info);
    bool DoWMudou = setInfoDoW(info);

    uint8_t dataMask        = 0b00000000;

    if (DiaMudou || MesMudou || AnoMudou || DoWMudou) {

        // Liga Bit
        dataMask        = 0b00000001;
        _infoScreen.Alterado = dataMask | _infoScreen.Alterado;

    } else {

        // Desliga bit
        dataMask        = 0b11111110;
        _infoScreen.Alterado = dataMask & _infoScreen.Alterado;

    }
    
    return DiaMudou || MesMudou || AnoMudou || DoWMudou;

}

bool Infos::InfoScreen::setInfoDia(dados_t *info) {

    _infoScreen.Data.Dia.mudou = _infoScreen.Data.Dia.valor != 
                                 info->Data.Dia.valor ? 
                                 true : false;
    
    _infoScreen.Data.Dia.valor = info->Data.Dia.valor;

    return _infoScreen.Data.Dia.mudou;

}

bool Infos::InfoScreen::setInfoMes(dados_t *info) {

    _infoScreen.Data.Mes.mudou = _infoScreen.Data.Mes.valor != 
                                 info->Data.Mes.valor ? 
                                 true : false;
    
    _infoScreen.Data.Mes.valor = info->Data.Mes.valor;

    return _infoScreen.Data.Mes.mudou;

}

bool Infos::InfoScreen::setInfoAno(dados_t *info) {

    _infoScreen.Data.Ano.mudou = _infoScreen.Data.Ano.valor != 
                                 info->Data.Ano.valor ? 
                                 true : false;
    
    _infoScreen.Data.Ano.valor = info->Data.Ano.valor;

    return _infoScreen.Data.Ano.mudou;

}

bool Infos::InfoScreen::setInfoDoW(dados_t *info) {

    _infoScreen.Data.DoW.mudou = _infoScreen.Data.DoW.valor != 
                                 info->Data.DoW.valor ? 
                                 true : false;
    
    _infoScreen.Data.DoW.valor = info->Data.DoW.valor;

    return _infoScreen.Data.DoW.mudou;

}

#pragma endregion Tratamento de Data


#pragma region Tratamento de Hora

bool Infos::InfoScreen::setInfoTempo(dados_t *info) {

    bool HoraMudou = setInfoHora(info);
    bool MinMudou  = setInfoMin(info);
    bool SecMudou  = setInfoSec(info);

    uint8_t tempoMask        = 0b00000000;

    if (HoraMudou || MinMudou || SecMudou) {

        // Liga Bit
        tempoMask        = 0b00000010;
        _infoScreen.Alterado = tempoMask | _infoScreen.Alterado;

    } else {

        // Desliga bit
        tempoMask        = 0b11111101;
        _infoScreen.Alterado = tempoMask & _infoScreen.Alterado;

    }

    return HoraMudou || MinMudou || SecMudou;

}

bool Infos::InfoScreen::setInfoHora(dados_t *info) {

    _infoScreen.Tempo.Hora.mudou = _infoScreen.Tempo.Hora.valor != 
                                 info->Tempo.Hora.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Hora.valor = info->Tempo.Hora.valor;

    return _infoScreen.Tempo.Hora.mudou;

}

bool Infos::InfoScreen::setInfoMin(dados_t *info) {

    _infoScreen.Tempo.Min.mudou = _infoScreen.Tempo.Min.valor != 
                                 info->Tempo.Min.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Min.valor = info->Tempo.Min.valor;

    return _infoScreen.Tempo.Min.mudou;

}

bool Infos::InfoScreen::setInfoSec(dados_t *info) {

    _infoScreen.Tempo.Sec.mudou = _infoScreen.Tempo.Sec.valor != 
                                 info->Tempo.Sec.valor ? 
                                 true : false;
    
    _infoScreen.Tempo.Sec.valor = info->Tempo.Sec.valor;

    return _infoScreen.Tempo.Sec.mudou;

}

#pragma endregion Tratamento de Hora


#pragma region Tratamento de Ambiente

bool Infos::InfoScreen::setInfoAmbiente(dados_t *info) {

    bool TemperaturaMudou   = setInfoTemperatura(info);
    bool UmidadeMudou       = setInfoUmidade(info);
    bool LuminosidadeMudou  = setInfoUmidade(info);

    uint8_t ambienteMask        = 0b00000000;

    if (TemperaturaMudou || UmidadeMudou || LuminosidadeMudou) {

        // Liga Bit
        ambienteMask        = 0b00000100;
        _infoScreen.Alterado = ambienteMask | _infoScreen.Alterado;

    } else {

        // Desliga bit
        ambienteMask        = 0b11111011;
        _infoScreen.Alterado = ambienteMask & _infoScreen.Alterado;

    }

    return TemperaturaMudou || UmidadeMudou || LuminosidadeMudou;

}

bool Infos::InfoScreen::setInfoTemperatura(dados_t *info) {

    _infoScreen.Ambiente.Temperatura.mudou = _infoScreen.Ambiente.Temperatura.valor != 
                                            info->Ambiente.Temperatura.valor ? 
                                            true : false;
    
    _infoScreen.Ambiente.Temperatura.valor = info->Ambiente.Temperatura.valor;

    return _infoScreen.Ambiente.Temperatura.mudou;

}

bool Infos::InfoScreen::setInfoUmidade(dados_t *info) {

    _infoScreen.Ambiente.Umidade.mudou = _infoScreen.Ambiente.Umidade.valor != 
                                          info->Ambiente.Umidade.valor ? 
                                          true : false;
    
    _infoScreen.Ambiente.Umidade.valor = info->Ambiente.Umidade.valor;

    return _infoScreen.Ambiente.Umidade.mudou;

}

bool Infos::InfoScreen::setInfoLuminosidade(dados_t *info) {

    _infoScreen.Ambiente.Luminosidade.mudou = _infoScreen.Ambiente.Luminosidade.valor != 
                                              info->Ambiente.Luminosidade.valor ? 
                                              true : false;
    
    _infoScreen.Ambiente.Luminosidade.valor = info->Ambiente.Luminosidade.valor;

    return _infoScreen.Ambiente.Luminosidade.mudou;

}

#pragma endregion Tratamento de Ambiente


#pragma region Tratamento de Sistema

bool Infos::InfoScreen::setInfoTemperaturaSys(dados_t *info) {

    _infoScreen.TemperaturaSys.mudou = _infoScreen.TemperaturaSys.valor != 
                                       info->TemperaturaSys.valor ? 
                                       true : false;
    
    _infoScreen.TemperaturaSys.valor = info->TemperaturaSys.valor;

    uint8_t tempSysMask        = 0b00000000;

    if (_infoScreen.TemperaturaSys.mudou) {

        // Liga Bit
        tempSysMask        = 0b00001000;
        _infoScreen.Alterado = tempSysMask | _infoScreen.Alterado;

    } else {

        // Desliga bit
        tempSysMask        = 0b11110111;
        _infoScreen.Alterado = tempSysMask & _infoScreen.Alterado;

    }

    return _infoScreen.TemperaturaSys.mudou;

}

#pragma endregion Tratamento de Sistema


#pragma endregion Classe InfoScreen


#pragma region Classe InfoSys

Infos::infoSys::infoSys() { }

Infos::infoSys::~infoSys() { }

#pragma endregion Classe InfoSys

