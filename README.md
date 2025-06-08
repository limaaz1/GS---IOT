**Link do Projeto:**
https://wokwi.com/projects/433059990569150465

****Monitoramento de Vibração e Temperatura com ESP32****

Este projeto tem como objetivo monitorar vibração e temperaturas elevadas utilizando o ESP32, um sensor de vibração, um sensor de temperatura (simulado via pino analógico), um botão de emergência e um buzzer. As informações são enviadas via MQTT, e tudo pode ser simulado diretamente no Wokwi.

**Funcionalidades**:

Leitura de vibração com sensor analógico.

Conversão do valor de vibração para uma escala sísmica (semelhante à Escala Richter).

Classificação da intensidade do tremor com mensagens de alerta (de "Muito leve" a "Extremo").

Leitura da temperatura e verificação de risco de incêndio.

Acionamento do buzzer em caso de risco elevado.

Botão de emergência que força o envio imediato de alerta.

Envio de dados formatados em JSON para um tópico MQTT.

**Como funciona**:

O ESP32 realiza leituras constantes dos sensores de vibração e temperatura. A vibração é convertida para uma escala sísmica para facilitar a interpretação do nível de risco. Se a temperatura ultrapassar 120 graus Celsius ou o botão for pressionado, o buzzer é ativado e um alerta é disparado.

As informações são publicadas no tópico MQTT a cada 2 segundos, contendo:

valor da vibração

temperatura atual

nível estimado do tremor

se o botão foi pressionado

se o buzzer foi ativado

**Resultados**:

Durante os testes, foi possível observar a leitura dos sensores no monitor serial. Quando a vibração simulada ultrapassou certos limites ou a temperatura ficou acima de 120 °C, o sistema ativou o buzzer e enviou o alerta com sucesso para o broker MQTT. O botão de emergência também disparou o envio de dados imediatamente.

**Tecnologias usadas:**

Simulador Wokwi 

ESP32

Sensor de vibração analógico (simulado)

Sensor de temperatura (simulado)

Botão de emergência

Buzzer

Protocolo MQTT

Broker público HiveMQ (broker.hivemq.com)

Arduino IDE

**Bibliotecas**:

WiFi.h

PubSubClient.h

ArduinoJson.h

**Integrantes do grupo**:

Guilherme Jesus Lima / RM: 555002
Jean Roberto Gomes / RM: 94418
Lucas de Melo Pinheiro Pinho / RM: 558791
