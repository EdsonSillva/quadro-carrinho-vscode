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


#endif  // __ENUMBOX_H__
