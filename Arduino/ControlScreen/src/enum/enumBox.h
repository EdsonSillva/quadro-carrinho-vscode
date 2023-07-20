/*
    Controle dos enumeration usados no projeto
*/

#ifndef __ENUMBOX_H__
#define __ENUMBOX_H__

/**
 * Enumeration para indicar se uma ação foi solicitada e se o arduino está executando
 */
enum eCodeExec {
    SemExecucao                 = 0,        // Estado inicial ou sem pedido de execução - Usado pelo Nextion
    NextionSolicitaExecucao     = 1,        // Screen solicitando Execução no Arduino   - Usado pelo Nextion
    ArduinoExecutando           = 2,        // Arduino Executando                       - Usado pelo Arduino
    ArduinoExecutado            = 3         // Execução finalizada pelo Arduino         - Usado pelo Arduino
};

enum eTipoDadoInfo {
    DataInfo                    = 1,
    TempoInfo                   = 2,
    AmbienteInfo                = 3,
    TempreraturaSysInfo         = 4
};

enum eTipoDataInfo {
    DiaInfo                     = 1,
    MesInfo                     = 2,
    AnoInfo                     = 3,
    DoWorkInfo                  = 4
};

enum eTipoTempoInfo {
    HoraInfo                    = 1,
    MinutoInfo                  = 2,
    SegundoInfo                 = 3
};

enum eTipoAmbienteInfo {
    TemperaturaInfo             = 1,
    UmidadeInfo                 = 2,
    LuminosidadeInfo            = 3
};


enum eTipoTemperaturaSysInfo {
    TemperaturaSysInfo          = 1
};

enum class eTipoTodos {
    DiaInfo                     = 1,
    MesInfo                     = 2,
    AnoInfo                     = 3,
    DoWorkInfo                  = 4,
    HoraInfo                    = 5,
    MinutoInfo                  = 6,
    SegundoInfo                 = 7,
    TemperaturaInfo             = 8,
    UmidadeInfo                 = 9,
    LuminosidadeInfo            = 10,
    TemperaturaSysInfo          = 11
};



#endif  // __ENUMBOX_H__
