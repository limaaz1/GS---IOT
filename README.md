**Link do Projeto:**
https://wokwi.com/projects/433059990569150465

****Monitoramento de Vibração e Temperatura com ESP32****

Este projeto tem como objetivo monitorar vibração e temperaturas elevadas utilizando o ESP32, um sensor de vibração, um sensor de temperatura (simulado via pino analógico), um botão de emergência e um buzzer. As informações são enviadas via MQTT, e tudo pode ser simulado diretamente no Wokwi.

**Descrição completa da solução:**

O sistema simula um cenário de segurança para ambientes onde tremores e temperaturas altas possam indicar risco de acidentes ou incêndios. Os sensores coletam dados em tempo real e enviam para um broker MQTT. Um botão de emergência permite o envio manual de alerta, e um buzzer é ativado em caso de situações críticas.

A aplicação se divide nas seguintes partes:

Leitura da vibração: converte o sinal analógico em uma escala equivalente à Escala Richter.

Classificação de risco: avalia o nível de perigo com base na vibração medida.

Leitura da temperatura: detecta valores acima de 120 °C como possíveis riscos de incêndio.

Alerta sonoro: o buzzer é acionado automaticamente em caso de perigo.

Envio de dados: todas as leituras e estados são enviados via MQTT em formato JSON.

**Instruções de configuração, execução e testes:**

Acesse o projeto no Wokwi (link do projeto a ser inserido).

Configure os tópicos MQTT no broker público HiveMQ (broker.hivemq.com).

Instale as bibliotecas necessárias na Arduino IDE: WiFi, PubSubClient e ArduinoJson.

Faça o upload do código no ESP32.

Abra o monitor serial para acompanhar as leituras.

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
