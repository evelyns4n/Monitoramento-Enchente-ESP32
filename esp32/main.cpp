/*
 * Monitoramento de Enchente - ESP32
 *
 * Reconstrução inicial do projeto original.
 *
 * Fluxo previsto:
 * sensor -> ESP32 -> Wi-Fi -> painel web
 *
 * ATENÇÃO:
 * O modelo exato do sensor original não foi preservado.
 * A função lerDistancia() permanece isolada para que a leitura possa
 * ser adaptada depois da identificação e do teste do sensor.
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* WIFI_SSID = "SEU_WIFI";
const char* WIFI_PASSWORD = "SUA_SENHA";

WebServer server(80);

// Referência registrada no projeto original.
const int SENSOR_SIGNAL_PIN = 5; // D1 / GPIO 5

float lerDistancia() {
  /*
   * A leitura real depende do modelo do sensor.
   *
   * Não foi mantida uma implementação específica aqui para evitar
   * atribuir ao projeto um protocolo de leitura que não possa ser
   * confirmado.
   */
  return NAN;
}

void handleDados() {
  float distancia = lerDistancia();

  if (!isfinite(distancia)) {
    server.send(503, "application/json",
                "{\"erro\":\"Leitura do sensor ainda não configurada\"}");
    return;
  }

  String json = "{\"distancia\":" + String(distancia, 1) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_SIGNAL_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("ESP32 conectado. IP: ");
  Serial.println(WiFi.localIP());

  server.on("/dados", HTTP_GET, handleDados);
  server.begin();

  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  server.handleClient();
}
