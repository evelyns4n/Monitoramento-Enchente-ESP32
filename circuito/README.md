# Circuito

## Ligação reconstruída

Na versão reconstruída do projeto, o sensor é tratado como um dispositivo com três conexões:

- **VCC** — alimentação;
- **GND** — referência;
- **SIG** — sinal.

Durante a reconstrução, a referência registrada para o sinal foi **D1 / GPIO 5**.

### Importante

O modelo exato do sensor precisa ser confirmado antes de considerar esta ligação definitiva. A forma de leitura depende do tipo de saída do sensor.

Portanto, esta documentação registra a configuração lembrada do projeto original sem afirmar que ela já foi novamente testada.

## Próxima validação

- confirmar o modelo do sensor;
- confirmar tensão de alimentação;
- confirmar se o sinal é analógico, digital ou outro protocolo;
- conferir a ligação do GPIO;
- realizar teste de leitura no ESP32;
- calibrar a relação entre leitura e nível de água.
