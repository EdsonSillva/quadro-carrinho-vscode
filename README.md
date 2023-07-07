# Projeto Quadro de Carrinhos

## Objetivo

Destacar a iluminação de cada box em um quadro de **15x14** (CxL), onde coloquei carrinhos da hotwheels. A ideia é poder interagir com o quadro através de comandos em uma tela touch.
</br>
</br>

## Descrição do projeto

O projeto foi desenvolvido em 3 partes:

- Tela;
- Controle da tela e periféricos;
- Controle do quadro (box);

### Tela

Utilizado uma tela da **Nextion** por permitir desenvolvimento diretamente nela, sendo assim liberando o arduino do desenvolvimento da inteface. Este projeto foi desenvolvido na IDE **Nextion Editor**.

Diretório contendo o projeto: */Nextion*

Site: [Nexition](https://nextion.tech/)
</br>
</br>

### Controle da tela e periféricos

Utilizado um **arduino nano** para interagir com a tela, atualizar com as informações dos periféricos *Buzzer, EEPROM, DHT11, LDR e DS3231*. Ele também é responsável em informar o arduino que controla o quadro de carrinhos qual comando foi selecionado.

Diretório contendo o projeto: */Arduino/ControlScreen*
</br>
</br>

### Controle do quadro

Utilizado um **arduino nano** para receber os comandos selecionados e executar no quadro de carrinho.

Diretório contendo o projeto: */Arduino/ControlBox*
</br>
</br>

## Hardware

- 2 Arduino nano;
- Screen Nextion modelo: NX3224T028;
- Sensor DHT11;
- Sensor LDR
- RTC DS3231;
- Memória EEPROM 256Kb;
- Buzzer;

## Soluções de comunicação usadas

- I2C;
- UART;

## Mapa dos pinos usados

Nesta seção será descrito quais pinos foram utilizados em cada arduino nano e com quais periféricos/sensores.

### Arduino nano - (tela)

|Sensor/device|Pino|Observação|
|-------------|----|----------|
| Nextion| Tx e Rx | UART |
| LDR|A0| Utilizado um resistor de 470 ohms |
| DHT11| A1 | Módulo |
| DS3231| I2C - (A4) SDA    (A5) SCL | Módulo |
| EEPROM| I2C - (A4) SDA    (A5) SCL | Módulo compartilhado entre arduinos |
| Buzzer| 7 - digital | Comum |
| Led (indicação de uso da eeprom) | 11 - digital|Utilizado um resistor de 470 ohms |
| Led (indicação de ação)| 12 - digital | Utilizado um resistor de 470 ohms |
| Led (indicação de alerta eeprom) | 08 - digital |Utilizado um resistor de 470 ohms | |

</br>

### Arduino Nano - (box)

|Sensor/device|Pino|Observação|
|-------------|----|----------|
| EEPROM| I2C - (A4) SDA    (A5) SCL | Módulo compartilhado entre arduinos |
| Buzzer| 7 - digital | Comum |
| Fita de Leds | 13 - digital | Resistor interno |
| Led (indicação de uso da eeprom) | 11 - digital | Utilizado um resistor de 470 ohms |
| Led (indicação de ação) | 12 - digital|Utilizado um resistor de 470 ohms |
| Led (indicação de alerta eeprom) | 08 - digital | Utilizado um resistor de 470 ohms |

## Desenho da solução em hardware







