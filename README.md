# Monitoramento de Enchente com ESP8266

Projeto de IoT para monitoramento do nível de água utilizando **ESP8266, sensor ultrassônico, LEDs e buzzer**.

## Funcionamento

O sensor ultrassônico mede a distância entre o sensor e a superfície da água.

Quanto menor a distância medida, maior o nível da água.

**Fluxo:**

Sensor ultrassônico → ESP8266 → Wi-Fi → painel web

Além do painel, o protótipo utiliza indicadores locais:

- 🟢 **LED verde:** nível normal
- 🟡 **LED amarelo:** atenção
- 🔴 **LED vermelho:** alerta
- 🔊 **Buzzer:** acionado na situação de alerta

## Componentes

- ESP8266
- Sensor ultrassônico HC-SR04
- Protoboard
- LED verde
- LED amarelo
- LED vermelho
- Buzzer
- Resistores para os LEDs
- Jumpers
- Fonte/alimentação para o ESP8266

## Pinagem reconstruída

| Componente | ESP8266 |
|---|---|
| HC-SR04 TRIG | D1 |
| HC-SR04 ECHO | D2 |
| LED verde | D5 |
| LED amarelo | D6 |
| LED vermelho | D7 |
| Buzzer | D8 |

> **Observação:** esta é a pinagem utilizada na reconstrução funcional do código. Caso a montagem física original utilizasse outros pinos, eles podem ser alterados nas constantes de `esp32/main.cpp`.

## Faixas de monitoramento

A reconstrução utiliza inicialmente:

| Distância até a água | Estado | Indicador |
|---|---|---|
| > 30 cm | Normal | LED verde |
| 15–30 cm | Atenção | LED amarelo |
| ≤ 15 cm | Alerta | LED vermelho + buzzer |

Esses valores são **limites iniciais de reconstrução** e devem ser calibrados de acordo com a posição real do sensor e a estrutura utilizada no protótipo.

## Estrutura

```
Monitoramento-Enchente-ESP32/
├── README.md
├── esp32/
│   └── main.cpp
├── painel/
│   ├── index.html
│   ├── style.css
│   └── script.js
└── circuito/
    └── README.md
```

## Programação

O código do microcontrolador está em:

`esp32/main.cpp`

Ele realiza:

1. Inicialização dos pinos.
2. Conexão do ESP8266 à rede Wi-Fi.
3. Medição da distância com o HC-SR04.
4. Classificação do nível em Normal, Atenção ou Alerta.
5. Acionamento dos LEDs.
6. Acionamento do buzzer em situação de alerta.
7. Disponibilização dos dados por HTTP no endpoint `/dados`.

## Painel web

O painel está em `painel/` e foi estruturado para receber a distância medida pelo dispositivo e apresentar o estado do monitoramento.

## Estado da reconstrução

Este repositório está sendo reconstruído porque os arquivos locais do projeto original não foram preservados.

Por isso, a documentação diferencia o que foi recuperado das informações disponíveis e o que ainda precisa ser validado fisicamente.

O código atual é uma **reconstrução funcional**, não uma afirmação de que este seja byte a byte o código original utilizado no projeto.

## Próximas validações

- conferir a pinagem física;
- testar o HC-SR04 com o ESP8266;
- confirmar a alimentação adequada do sensor;
- testar LEDs e buzzer;
- validar a comunicação Wi-Fi;
- integrar o endpoint do ESP8266 ao painel web;
- fotografar o protótipo e adicionar as imagens ao repositório.
