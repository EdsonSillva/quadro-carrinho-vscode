# Projeto Quadro de Carrinhos - Arduino Tela

## Objetivo

Esta parte do projeto trata das rotinas de comunicação com a tela **Nextion** recebendo informações da interação feita na tela e enviando informações de data, hora, temperatura, Umidade, luminosidade, etc.

Este arduino é responsável em geranciar estas interações e manter as informações atualizadas na tela. A comunicação é feita via UART (TX e RX).

### Definição códigos de retorno do Nextion

Formato 


01 - retorno com sucesso (01 FF FF FF)
66 - retorno de página (66 01 FF FF FF)
71 - retorno de valor numérico (71 01 00 00 00 FF FF FF)




</br>
</br>
