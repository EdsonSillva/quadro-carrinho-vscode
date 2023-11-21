# Projeto Quadro de Carrinhos - Arduino Tela

## Objetivo

Esta parte do projeto trata das rotinas de comunicação com a tela **Nextion** recebendo informações da interação feita na tela e enviando informações de data, hora, temperatura, Umidade, luminosidade, etc.

Este arduino é responsável em geranciar estas interações e manter as informações atualizadas na tela. A comunicação é feita via UART (TX e RX).

### Definição códigos de retorno do Nextion

Formato

01 - retorno com sucesso (01 FF FF FF)</br>
66 - retorno de página (66 01 FF FF FF)</br>
71 - retorno de valor numérico (71 01 00 00 00 FF FF FF)</br>

</br>

### Controle do Tema

Para guardar as informações dos box em cada tema foi utilizado a memória interna do arduino nano.

A estrutura definida foi:

- As 50 primeiras posições guarda o código do tema. Este intervalo foi batizado de  BAT (Box Alocation Table)
- O restante das posições são usadas para guardar os endereçoes dos box. Cada byte guarda a linha e coluna do box num formato de 0b00001111, onde os primeiros 4 bits (0000) representam a linha e os outros 4 bits (1111) representam a coluna. Nesta versão foi definido um tamanho de 20 bytes por tema, ou seja pode ser definido até 20 box para cada tema. A tela nextion está controlando a inclusão para este máximo.

Importante: Se for usado um <b>novo arduino nano</b>, a memória EEPROM interna deverá passar pela seguinte inicialização:

- As primeiras 50 posições (BAT) deverão ter o valor 0
- As posições restantes deverão ter o valor 255

Na pasta suporte deste projeto contêm um sketch que faz isso. Carregue-o no arduino nano e abra a serial para interagir e executar as inicializações.
