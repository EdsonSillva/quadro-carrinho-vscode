/*
    Módulo para guardar as informações de atualização da tela do Nextion
    
    Desenvolvido por Edson Silva
    Date: 10/07/23

*/

#ifndef __INFOS_H__
#define __INFOS_H__

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef __TYPEDEFSCREEN_H__
#include "../typedef/typedefScreen.h"
#endif

#ifndef __ENUMBOX_H__
#include "../enum/enumBox.h"
#endif


namespace Infos {

    class InfoScreen {
        
        private:

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

            bool setBitChange(bool mudou, uint8_t dado);


        public:

            InfoScreen();
            ~InfoScreen();

            void setInfoScreen(dados_t *info);
            bool existeAlteracao();
            
            bool foiAlterado(eTipoDadoInfo tipo);

            bool valorAlterado(/*tipo com todos os tipos*/);
            byte getvalor(/*tipo com todos os tipos*/);

    };


    class infoSys : public dadosSistema_t
    {

    private:


    public:

        infoSys();
        ~infoSys();


    };



};



#endif  // __INFOS_H__
