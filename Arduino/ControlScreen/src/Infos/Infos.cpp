
#include "Infos.h"


#pragma region Classe InfoScreen

Infos::InfoScreen::InfoScreen() { }

Infos::InfoScreen::~InfoScreen() { }

bool Infos::InfoScreen::existeAlteracao() {
    return _existeAlteracao;
}

void Infos::InfoScreen::setInfoScreen(dados_t *info) {

    bool dataMudou      = setInfoData(info);
    bool tempoMudou     = setInfoTempo(info);
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

    bool DiaMudou = setValorInfo(&_infoScreen.Data.Dia.valor, &info->Data.Dia.valor);
    bool MesMudou = setValorInfo(&_infoScreen.Data.Mes.valor, &info->Data.Mes.valor);
    bool AnoMudou = setValorInfo(&_infoScreen.Data.Ano.valor, &info->Data.Ano.valor);
    bool DoWMudou = setValorInfo(&_infoScreen.Data.DoW.valor, &info->Data.DoW.valor);

    // @deprecated
    // bool DiaMudou = setInfoDia(info);
    // bool MesMudou = setInfoMes(info);
    // bool AnoMudou = setInfoAno(info);
    // bool DoWMudou = setInfoDoW(info);

    uint8_t dataMask        = 0b00000000;

    bool mudouData = DiaMudou || MesMudou || AnoMudou || DoWMudou;

    if (mudouData) {                    // Liga Bit

        dataMask        = 0b00000001;
        _infoScreen.Alterado = dataMask | _infoScreen.Alterado;

    } else {                            // Desliga bit

        dataMask        = 0b11111110;
        _infoScreen.Alterado = dataMask & _infoScreen.Alterado;

    }
    
    return mudouData;

}

// /* @deprecated */
// bool Infos::InfoScreen::setInfoDia(dados_t *info) {

//     _infoScreen.Data.Dia.mudou = _infoScreen.Data.Dia.valor != 
//                                  info->Data.Dia.valor ? 
//                                  true : false;
    
//     _infoScreen.Data.Dia.valor = info->Data.Dia.valor;

//     return _infoScreen.Data.Dia.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoMes(dados_t *info) {

//     _infoScreen.Data.Mes.mudou = _infoScreen.Data.Mes.valor != 
//                                  info->Data.Mes.valor ? 
//                                  true : false;
    
//     _infoScreen.Data.Mes.valor = info->Data.Mes.valor;

//     return _infoScreen.Data.Mes.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoAno(dados_t *info) {

//     _infoScreen.Data.Ano.mudou = _infoScreen.Data.Ano.valor != 
//                                  info->Data.Ano.valor ? 
//                                  true : false;
    
//     _infoScreen.Data.Ano.valor = info->Data.Ano.valor;

//     return _infoScreen.Data.Ano.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoDoW(dados_t *info) {

//     _infoScreen.Data.DoW.mudou = _infoScreen.Data.DoW.valor != 
//                                  info->Data.DoW.valor ? 
//                                  true : false;
    
//     _infoScreen.Data.DoW.valor = info->Data.DoW.valor;

//     return _infoScreen.Data.DoW.mudou;

// }

#pragma endregion Tratamento de Data


#pragma region Tratamento de Hora

bool Infos::InfoScreen::setInfoTempo(dados_t *info) {

    bool HoraMudou = setValorInfo(&_infoScreen.Tempo.Hora.valor, &info->Tempo.Hora.valor);
    bool MinMudou  = setValorInfo(&_infoScreen.Tempo.Min.valor, &info->Tempo.Min.valor);
    bool SecMudou  = setValorInfo(&_infoScreen.Tempo.Sec.valor, &info->Tempo.Sec.valor);

    // @deprecated
    // bool HoraMudou = setInfoHora(info);
    // bool MinMudou  = setInfoMin(info);
    // bool SecMudou  = setInfoSec(info);

    uint8_t tempoMask        = 0b00000000;

    bool mudouTempo = HoraMudou || MinMudou || SecMudou;

    if (mudouTempo) {                   // Liga Bit

        tempoMask        = 0b00000010;
        _infoScreen.Alterado = tempoMask | _infoScreen.Alterado;

    } else {                            // Desliga bit

        tempoMask        = 0b11111101;
        _infoScreen.Alterado = tempoMask & _infoScreen.Alterado;

    }

    return mudouTempo;

}

// /* @deprecated */
// bool Infos::InfoScreen::setInfoHora(dados_t *info) {

//     _infoScreen.Tempo.Hora.mudou = _infoScreen.Tempo.Hora.valor != 
//                                  info->Tempo.Hora.valor ? 
//                                  true : false;
    
//     _infoScreen.Tempo.Hora.valor = info->Tempo.Hora.valor;

//     return _infoScreen.Tempo.Hora.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoMin(dados_t *info) {

//     _infoScreen.Tempo.Min.mudou = _infoScreen.Tempo.Min.valor != 
//                                  info->Tempo.Min.valor ? 
//                                  true : false;
    
//     _infoScreen.Tempo.Min.valor = info->Tempo.Min.valor;

//     return _infoScreen.Tempo.Min.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoSec(dados_t *info) {

//     _infoScreen.Tempo.Sec.mudou = _infoScreen.Tempo.Sec.valor != 
//                                  info->Tempo.Sec.valor ? 
//                                  true : false;
    
//     _infoScreen.Tempo.Sec.valor = info->Tempo.Sec.valor;

//     return _infoScreen.Tempo.Sec.mudou;

// }

#pragma endregion Tratamento de Hora


#pragma region Tratamento de Ambiente

bool Infos::InfoScreen::setInfoAmbiente(dados_t *info) {

    bool TemperaturaMudou  = setValorInfo(&_infoScreen.Ambiente.Temperatura.valor, &info->Ambiente.Temperatura.valor);
    bool UmidadeMudou      = setValorInfo(&_infoScreen.Ambiente.Umidade.valor, &info->Ambiente.Umidade.valor);
    bool LuminosidadeMudou = setValorInfo(&_infoScreen.Ambiente.Luminosidade.valor, &info->Ambiente.Luminosidade.valor);

    //@deprecated
    // bool TemperaturaMudou   = setInfoTemperatura(info);
    // bool UmidadeMudou       = setInfoUmidade(info);
    // bool LuminosidadeMudou  = setInfoUmidade(info);

    uint8_t ambienteMask        = 0b00000000;

    bool mudouAmbiente = TemperaturaMudou || UmidadeMudou || LuminosidadeMudou;

    if (mudouAmbiente) {                // Liga Bit
        
        ambienteMask        = 0b00000100;
        _infoScreen.Alterado = ambienteMask | _infoScreen.Alterado;

    } else {                            // Desliga bit

        ambienteMask        = 0b11111011;
        _infoScreen.Alterado = ambienteMask & _infoScreen.Alterado;

    }

    return mudouAmbiente;

}

// /* @deprecated */
// bool Infos::InfoScreen::setInfoTemperatura(dados_t *info) {

//     _infoScreen.Ambiente.Temperatura.mudou = _infoScreen.Ambiente.Temperatura.valor != 
//                                             info->Ambiente.Temperatura.valor ? 
//                                             true : false;
    
//     _infoScreen.Ambiente.Temperatura.valor = info->Ambiente.Temperatura.valor;

//     return _infoScreen.Ambiente.Temperatura.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoUmidade(dados_t *info) {

//     _infoScreen.Ambiente.Umidade.mudou = _infoScreen.Ambiente.Umidade.valor != 
//                                           info->Ambiente.Umidade.valor ? 
//                                           true : false;
    
//     _infoScreen.Ambiente.Umidade.valor = info->Ambiente.Umidade.valor;

//     return _infoScreen.Ambiente.Umidade.mudou;

// }

// /* @deprecated */
// bool Infos::InfoScreen::setInfoLuminosidade(dados_t *info) {

//     _infoScreen.Ambiente.Luminosidade.mudou = _infoScreen.Ambiente.Luminosidade.valor != 
//                                               info->Ambiente.Luminosidade.valor ? 
//                                               true : false;
    
//     _infoScreen.Ambiente.Luminosidade.valor = info->Ambiente.Luminosidade.valor;

//     return _infoScreen.Ambiente.Luminosidade.mudou;

// }

#pragma endregion Tratamento de Ambiente


#pragma region Tratamento de Sistema

bool Infos::InfoScreen::setInfoTemperaturaSys(dados_t *info) {

    bool TemperaturaSysMudou  = setValorInfo(&_infoScreen.TemperaturaSys.valor, &info->TemperaturaSys.valor);

    // @deprecated
    // _infoScreen.TemperaturaSys.mudou = _infoScreen.TemperaturaSys.valor != 
    //                                    info->TemperaturaSys.valor ? 
    //                                    true : false;
    // _infoScreen.TemperaturaSys.valor = info->TemperaturaSys.valor;

    uint8_t tempSysMask        = 0b00000000;

    if (TemperaturaSysMudou) {          // Liga Bit
        
        tempSysMask        = 0b00001000;
        _infoScreen.Alterado = tempSysMask | _infoScreen.Alterado;

    } else {                            // Desliga bit
        
        tempSysMask        = 0b11110111;
        _infoScreen.Alterado = tempSysMask & _infoScreen.Alterado;

    }

    return TemperaturaSysMudou;

}

#pragma endregion Tratamento de Sistema


#pragma region Rotinas gerais da classe

/* @brief Ajusta o bit 8 para 0 ou 1. Se o valor mudou o bit 8 será 1 se não será 0. @return retorna o valor com o controle de mudança de valor no bit 8*/
byte Infos::InfoScreen::setBitChange(bool mudou, uint8_t *valor) {

    byte mask = 0b00000000;

    if (mudou) { mask = 0b10000000; }

    return mask | *valor;

}

/* @brief Converte o valor recebido em valor com controle no bit 8 e retorna o valor com o controle no bit 8. @return retorna o valor com o controle de mudança de valor no bit 8  */
bool Infos::InfoScreen::setValorInfo(byte *valoInforScreen, byte *valorSys) {

    // TODODone - Efetuando as mudanças no controle do valor para uma única variável

    byte valorOriginal = getvalorOriginal(valoInforScreen);

    bool mudouValor = valorOriginal != *valorSys ? true : 
                                                   false;

    *valoInforScreen = setBitChange(mudouValor, valorSys);

    return mudouValor;

}

/* @brief Busca o valor junto com o controle de alteração. Este valor contém controle de alteração no bit 8 */
byte Infos::InfoScreen::getvalorSys(eTipoTodos tipoInfo) {

    byte valorSys   = 0x00;

    switch (tipoInfo) {

        case eTipoTodos::DiaInfo:
            valorSys = _infoScreen.Data.Dia.valor;
        break;        

        case eTipoTodos::MesInfo:
            valorSys = _infoScreen.Data.Dia.valor;
        break;        

        // TODO: Fazer um case para cada ite de _infoScreen


    }

    return  valorSys;      // Retorna valor com controle de alteração no bit 8

}

/* @brief Busca o valor sem o controle de alteração. Este valor não contém o controle de alteração no bit 8 */
byte Infos::InfoScreen::getvalorOriginal(byte *valor) {

    byte mask       = 0b01111111;

    return mask & *valor;      // Retorna só valor

}

/* @brief Busca o valor da variável sem o controle de alteração. Este valor não contém o controle de alteração no bit 8 */
byte Infos::InfoScreen::getvalor(eTipoTodos tipoInfo) {

    byte valorSys   = getvalorSys(tipoInfo);

    return getvalorOriginal(&valorSys);      // Retorna só valor

}

/* @brief Verifica se a variável teve alteração e retorn true/false. Se for passado um ponteiro em *value será passado o valor original. Este valor não contém o controle de alteração no bit 8 @param value ponteiro para receber o valor original */
bool Infos::InfoScreen::valorAlterado(eTipoTodos tipoInfo, byte *value = NULL) {

    byte mask       = 0b10000000;
    byte valorSys   = getvalorSys(tipoInfo);

    if (value != NULL) {
        *value = getvalorOriginal(&valorSys);
    }

    return mask & valorSys;      // Retorna só valor

    // TODO Parei aqui - Continuar amanhã com Finalizar o switch da getvalorSys() e desenvolver como alterar o bit 8 quando recebe os valores na classe


}

#pragma endregion Rotinas gerais da classe

#pragma endregion Classe InfoScreen


#pragma region Classe InfoSys

Infos::infoSys::infoSys() { }

Infos::infoSys::~infoSys() { }

#pragma endregion Classe InfoSys

