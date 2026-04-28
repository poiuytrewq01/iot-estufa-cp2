#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

// ── Configurações Wi-Fi ──────────────────────────────────────
const char* ssid     = "Wokwi-GUEST";   // rede padrão do Wokwi
const char* password = "";

// ── Broker MQTT (HiveMQ público) ────────────────────────────
const char* mqtt_server = "broker.hivemq.com";
const int   mqtt_port   = 1883;
const char* client_id   = "estufa_esp32_wokwi";

// ── Tópicos MQTT ─────────────────────────────────────────────
const char* topic_temp     = "estufa1/temperatura";
const char* topic_hum      = "estufa1/umidade";
const char* topic_status   = "estufa1/status";
const char* topic_alerta   = "estufa1/alerta";

// ── Sensor DHT22 ─────────────────────────────────────────────
#define DHTPIN  4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ── Objetos de rede ──────────────────────────────────────────
WiFiClient   espClient;
PubSubClient client(espClient);

// ── Temporização ─────────────────────────────────────────────
unsigned long lastMsg = 0;
const long    interval = 5000;   // publica a cada 5 segundos

// ─────────────────────────────────────────────────────────────
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ─────────────────────────────────────────────────────────────
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect(client_id)) {
      Serial.println("conectado!");
      client.publish(topic_status, "online");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" – tentando novamente em 5s");
      delay(5000);
    }
  }
}

// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("Sistema de monitoramento de estufa iniciado!");
}

// ─────────────────────────────────────────────────────────────
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg >= interval) {
    lastMsg = now;

    float temperatura = dht.readTemperature();
    float umidade     = dht.readHumidity();

    if (isnan(temperatura) || isnan(umidade)) {
      Serial.println("Erro ao ler o sensor DHT22!");
      return;
    }

    // ── Publicar temperatura ──────────────────────────────
    char tempStr[8];
    dtostrf(temperatura, 5, 2, tempStr);
    client.publish(topic_temp, tempStr);
    Serial.print("Temperatura publicada: ");
    Serial.println(tempStr);

    // ── Publicar umidade ──────────────────────────────────
    char humStr[8];
    dtostrf(umidade, 5, 2, humStr);
    client.publish(topic_hum, humStr);
    Serial.print("Umidade publicada: ");
    Serial.println(humStr);

    // ── Alertas automáticos ───────────────────────────────
    if (temperatura > 35.0) {
      client.publish(topic_alerta, "ALERTA: Temperatura alta na estufa!");
      Serial.println("⚠ Alerta de temperatura alta enviado!");
    }
    if (umidade < 40.0) {
      client.publish(topic_alerta, "ALERTA: Umidade baixa na estufa!");
      Serial.println("⚠ Alerta de umidade baixa enviado!");
    }

    Serial.println("─────────────────────────────");
  }
}
