# Sistema de Irrigação Automática com Arduino

Projeto em C para Arduino que controla a rega de uma planta. São **3 entradas** (umidade do solo, luz e botão) e **2 saídas** (bomba d'água e LED de alerta).

A bomba liga sozinha quando o solo está seco, não rega sob sol forte e pode ser acionada manualmente pelo botão.

## Entradas e saídas

| Tipo      | Componente                                    | Pino |
|-----------|-----------------------------------------------|------|
| Entrada 1 | Sensor de umidade do solo (ou potenciômetro)  | A0   |
| Entrada 2 | LDR (sensor de luz) + resistor 10 kΩ          | A1   |
| Entrada 3 | Botão (push button)                           | D2   |
| Saída 1   | Bomba d'água (relé) ou LED azul + 220 Ω       | D8   |
| Saída 2   | LED vermelho de alerta + 220 Ω                | D9   |

## Materiais

- 1 Arduino Uno
- 1 protoboard e jumpers
- 1 potenciômetro (ou sensor de umidade do solo)
- 1 LDR + 1 resistor de 10 kΩ
- 1 botão
- 2 LEDs + 2 resistores de 220 Ω (ou 1 LED + 1 módulo relé para a bomba)

## Ligação

- **Potenciômetro:** pontas no 5V e GND, pino do meio no A0
- **LDR:** uma perna no 5V, outra no A1; resistor de 10 kΩ entre A1 e GND
- **Botão:** um lado no D2, outro no GND (usa o pull-up interno, sem resistor)
- **LEDs:** D8 / D9 → resistor 220 Ω → LED (+) → LED (−) no GND

## Como funciona

| Solo seco (< 30%) | Sol forte (LDR > 700) | Bomba       | LED de alerta |
|-------------------|-----------------------|-------------|---------------|
| Sim               | Não                   | Liga        | Aceso         |
| Sim               | Sim                   | Desliga     | Piscando      |
| Não               | Não                   | Desliga ao chegar em 60% | Apagado |
| Não               | Sim                   | Desliga     | Apagado       |

- **Histerese:** a bomba liga abaixo de 30% e só desliga a partir de 60%. Isso evita que ela fique ligando e desligando sem parar.
- **Modo manual:** enquanto o botão estiver pressionado, a bomba fica ligada, independente dos sensores.
- **Monitor Serial (9600 baud):** mostra umidade, luz, botão e estado da bomba a cada 200 ms.

```
Umidade: 25% | Luz: 400 | Manual: NAO | Bomba: LIGADA
```

## Como executar

**No Tinkercad (sem hardware):**
1. Acesse [tinkercad.com](https://www.tinkercad.com) → Circuits → Criar novo circuito
2. Monte o circuito conforme a seção de ligação
3. Em *Code*, mude para *Text* e cole o código do arquivo `main.c`
4. Clique em *Iniciar simulação* e abra o Monitor Serial

**No Arduino físico:**
1. Abra o código na [Arduino IDE](https://www.arduino.cc/en/software)
2. Selecione a placa *Arduino Uno* e a porta correta
3. Clique em *Carregar* e abra o Monitor Serial em 9600 baud

## Ajustes

Os limites ficam no topo do código e podem ser alterados:

| Constante         | Padrão | Descrição                         |
|-------------------|--------|-----------------------------------|
| `UMIDADE_LIGA`    | 30     | % abaixo da qual a bomba liga     |
| `UMIDADE_DESLIGA` | 60     | % a partir da qual a bomba desliga |
| `LUZ_FORTE`       | 700    | Leitura do LDR considerada sol forte |

## Autor

Kevin Loran
