# Monitoramento de Enchente com ESP32

Projeto de monitoramento de nível de água desenvolvido a partir de uma proposta de IoT para acompanhamento de risco de enchentes.

## Visão geral

A ideia do projeto é realizar a leitura de um sensor de nível/distância conectado a um ESP32, disponibilizar o valor pela rede Wi-Fi e apresentar os dados em um painel web.

**Fluxo previsto:**

Sensor → ESP32 → Wi-Fi → Painel web → indicação do nível

## Estrutura

- `esp32/` — código do microcontrolador.
- `painel/` — interface web para visualização dos dados.
- `circuito/` — documentação da ligação do sensor e observações de montagem.
- `imagens/` — espaço reservado para fotos do protótipo e do circuito.

## Estado da reconstrução

Este repositório está sendo reconstruído a partir do projeto original, pois os arquivos locais não foram preservados.

Por isso, é importante diferenciar:

- **Reconstituído:** estrutura do projeto, painel web e organização inicial.
- **A confirmar:** detalhes exatos do modelo do sensor e a ligação física usada na montagem original.
- **A testar novamente:** leitura real do sensor, comunicação ESP32 ↔ painel e calibração dos limites de alerta.

Durante a reconstrução, não são atribuídos ao projeto testes ou resultados que não possam ser confirmados.

## Tecnologias

- ESP32
- Wi-Fi
- HTML
- CSS
- JavaScript
- IoT
- Monitoramento de nível de água

## Próximos passos

1. Confirmar o modelo exato do sensor utilizado.
2. Revalidar a ligação elétrica.
3. Testar a leitura no ESP32.
4. Integrar a leitura real ao painel.
5. Calibrar as faixas **Normal**, **Atenção** e **Alerta**.
6. Adicionar fotos, esquema do circuito e evidências do protótipo.
