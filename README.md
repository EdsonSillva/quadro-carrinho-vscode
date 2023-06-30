# Projeto Quadro de Carrinhos

## Objetivo

Destacar a ilumunação de cada box em um quadro de **15x14** (CxL), onde coloquei carrinhos da hotwheels. A ideia é poder interagir com o quadro através de comandos em uma tela touch.
</br>
</br>

## Descrição do projeto

O projeto foi desenvolvido em 3 partes:

	> Tela;
	> Controle da tela;
	> Controle do quadro;

### Tela

Utilizado uma tela da **Nextion** por permitir desenvolvimento diretamente nela, sendo assim liberando o arduino do desenvolvimento da inteface.
</br>
</br>

### Controle da tela

Utiliado um **arduino nano** para interagir com a tela, atualizar com as informações dos periféricos *Buzzer, EEPROM, DHT11, LDR e DS3231*. Ele também é responsável em informar o arduino que controla o quadro de carrinhos qual comando foi selecionado.
</br>
</br>

### Controle do quadro

Utilizado um **arduino nano** para receber os comandos `#0969DA` selecionados e executar no quadro de carrinho.
</br>
</br>

## Hardware

- 2 Arduino nano;
- Screen Nextion modelo: NX3224T028;
- Sensor DHT11;
- Sensor LDR
- RTC DS3231;
- Memória EEPROM 256Kb
- Buzzer


## Desenho da solução em hardware

## Definição dos pinos usados

## Definição das soluções usadas





