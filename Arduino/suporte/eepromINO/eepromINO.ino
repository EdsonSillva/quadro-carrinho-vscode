#include <EEPROM.h>


int     address                     = 0;
int     size_EEPROM                 = 1024;
byte    value                       = 0;

int     batAddressIni               = 0;                                // Endereço inicial da Bat (Box Alocation Table)
byte    batTamanho                  = 50;                               // Tamnho da Bat (Box Alocation Table)
int     addressIniBoxes             = batAddressIni + batTamanho;       // Endereço inicial da área de dados dos Boxes (Cada byte indica Linha e Coluna)
byte    bat[50]                     = {0};                              // Box Alocation Table (cada posição é um tema)

char BoxesNextion[120]              = {0};                              // Cada 6 posição indica uma linha e coluna Ex.: 00:00; 000;00;000;00;00;

void setup()
{
	
    Serial.begin(9600);
    while(!Serial);
	EEPROM.begin();

    Serial.print(F("\nTrabalhando com a Memoria EEPROM do Arduino\n\n"));
    Serial.print(F("\nMemoria EEPROM do Arduino com\t"));
    Serial.print(EEPROM.length()), Serial.print(F(" Bytes\n\n"));

}

void loop()
{

    Serial.print(F("\n(I)-Inicializa enderecos da memoria | (l) lista os enderecos da memoria \n\n"));

    while(!Serial.available());

    char Dado = Serial.read();

    if (Dado == 'i' || Dado == 'I') {


        Serial.print(F("\nInforma a quantidade de bytes: "));
        while(!Serial.available());
        int Bytes = Serial.parseInt();

        Serial.print(F("\nInforma qual dado entre (0 a 255): "));
        while(!Serial.available());
        byte DadoByte = Serial.parseInt();

        Serial.print(F("\nInicializando as 50 primeiras posicoes com 0x00\n\n"));

        for (int i = 0; i < Bytes; i++)
            gravarInfo(i, DadoByte);

    } else if(Dado == 'l' || Dado == 'L')
    {

        Serial.print(F("\nInforma a quantidade de bytes: "));

        while(!Serial.available());

        int Bytes = Serial.parseInt();

        Serial.print(F("\nLendo a Memoria EEPROM do Arduino\n\n"));

        for ( address = 0; address < Bytes; address++)
        {
            value  =    EEPROM.read(address);

            Serial.print(F("\n\tAddress.ino:\t")),         Serial.print(address);
            Serial.print(F("\tbyte:\t")),                  Serial.print(value);
            Serial.print(F("\tL:")),                       Serial.print(numLinha(value));
            Serial.print(F("|C:")),                        Serial.print(numColuna(value));
            Serial.print(F("\tchar:\t")),                  Serial.print((char)value);
            delay(10);
        }
        
        Serial.print(F("\n\nFinalizado a leiturada Memoria EEPROM do Arduino\n\n\n"));
        // delay(5000);

    }


}

void gravarInfo(int Endereco, byte valor) {

    Serial.print(F("\nGravando na EEPROM do Arduino"));
    Serial.print(F("\tno Address:\t")),    Serial.print(Endereco);
    Serial.print(F("\tvalor em byte:\t")),   Serial.print(valor);

    EEPROM.write(Endereco, valor);

}


#pragma region Metodos de conversão de Linha, Coluna e LinhaColuna

/*
    @brief Conversão de dois bytes em um, onde os primeiros 4 bits é a represetação das 14 linhas no quadro
           e os outros 4 bits representa as 15 colunas no quadro.

           Ex. 0b11110000, onde 1111: as 14 linhas do quadro, 
                                0000: as 15 colunas do quadro.

    @param Linha: Informar um númenro entre 1 a 14. Este númenro representa uma linha do quadro de carrinhos.
    @param Coluna: Informar um númenro entre 1 a 15. Este númenro representa uma coluna do quadro de carrinhos.

    @return Um número onde representa a linha e coluna do quadro. Utilizar os metodos numLimha() e numColuna()
            para extarir a informação correta
*/
byte converteLinhaColuna(byte Linha, byte Coluna) {
    return (Linha << 4) | Coluna;
}

/*
    @brief Retira o número da Linha do número informado.

    @param LinhaColuna: Este número tem que ter sido convertido pelo método converteLinhaColuna()

    @return Um número onde representa a linha do quadro.
*/
byte numLinha(byte LinhaColuna) {
    return (byte)LinhaColuna >> 4;
}

/*
    @brief Retira o número da Coluna do número informado.

    @param LinhaColuna: Este número tem que ter sido convertido pelo método converteLinhaColuna()

    @return Um número onde representa a coluna do quadro.
*/
byte numColuna(byte LinhaColuna) {
    //return 0b00001111 & LinhaColuna; 
    return 0x0f & LinhaColuna;
}

#pragma endregion


