#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char* TOPICO_ALERTA = "evacuacao/zona1/alerta";

const int PIN_VIB = 35;
const int PIN_TEMP = 34;   
const int PIN_BTN = 15;
const int PIN_BUZZER = 4;

const float TEMP_LIMITE_INCENDIO = 60.0; 

WiFiClient espClient;
PubSubClient MQTT(espClient);

void initWiFi() {
  Serial.print("Conectando à rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado com sucesso!");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}

void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
  }
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    if (MQTT.connect("esp32_alerta_client")) {
      Serial.println("MQTT conectado!");
    } else {
      delay(1000);
    }
  }
}

float mapParaEscalaRichter(int valor) {
  return valor * 12.0 / 4095.0;
}

String descreverNivelTerremoto(float escala) {
  if (escala < 3.5) return "Muito leve (Não há riscos)";
  if (escala < 5.5) return "Leve (Não há riscos)";
  if (escala < 6.0) return "Moderado (Mantenha-se em casa)";
  if (escala < 7.0) return "Forte (Procure um abrigo seguro)";
  if (escala < 8.0) return "Muito forte (Evacue a área imediatamente)";
  if (escala < 9.0) return "Grande (Evacuação urgente e busque assistência)";
  if (escala <= 12.0) return "Extremo (Destruição total - acione equipes de resgate)";
  return "Valor fora do esperado";
}

float lerTemperatura(int valorAnalogico) {
  
  float tensao = valorAnalogico * (3.3 / 4095.0);  
  float temperatura = (tensao - 0.5) * 100.0; 
  return temperatura;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_VIB, INPUT);
  pinMode(PIN_TEMP, INPUT);    
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  noTone(PIN_BUZZER);

  initWiFi();
  initMQTT();
}

void loop() {
  reconnectWiFi();
  reconnectMQTT();
  MQTT.loop();

  int leituraVibracao = analogRead(PIN_VIB);
  int leituraTemp = analogRead(PIN_TEMP);

  float escalaRichter = mapParaEscalaRichter(leituraVibracao);
  String nivelTerremoto = descreverNivelTerremoto(escalaRichter);

  float temperatura = lerTemperatura(leituraTemp);

  bool botaoPressionado = digitalRead(PIN_BTN) == LOW;
  bool alertaRichter = escalaRichter >= 6.0;
  bool alertaTemperatura = temperatura > TEMP_LIMITE_INCENDIO;
  bool alertaManual = botaoPressionado;

  bool alerta = alertaRichter || alertaManual || alertaTemperatura;

  if (alerta) {
    tone(PIN_BUZZER, 1000);
  } else {
    noTone(PIN_BUZZER);
  }

  Serial.print("Leitura Vibração: ");
  Serial.print(leituraVibracao);
  Serial.print(" | Richter: ");
  Serial.print(escalaRichter, 1);
  Serial.print(" | Nível: ");
  Serial.print(nivelTerremoto);
  Serial.print(" | Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C");
  Serial.print(" | Botão: ");
  Serial.print(botaoPressionado ? "PRESSIONADO" : "solto");
  Serial.print(" | ALERTA: ");
  Serial.println(alerta ? "ATIVO" : "NORMAL");

  StaticJsonDocument<256> doc;
  doc["vibracao_raw"] = leituraVibracao;
  doc["richter"] = escalaRichter;
  doc["descricao_terremoto"] = nivelTerremoto;
  doc["temperatura_celsius"] = temperatura;
  doc["alerta_temperatura"] = alertaTemperatura;
  doc["botao"] = botaoPressionado;
  doc["alerta"] = alerta;

  char mensagem[256];
  serializeJson(doc, mensagem);
  MQTT.publish(TOPICO_ALERTA, mensagem);

  delay(2000);
}
