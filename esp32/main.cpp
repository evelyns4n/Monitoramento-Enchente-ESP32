/*
 * Monitoramento de Enchente
 * ESP8266 + HC-SR04 + LEDs + buzzer
 *
 * Reconstrução funcional do projeto original.
 *
 * O sensor ultrassônico mede a distância entre o sensor e a superfície
 * da água. Quanto menor a distância, maior o nível de água.
 *
 * Pinagem reconstruída:
 * HC-SR04 TRIG -> D1
 * HC-SR04 ECHO -> D2
 * LED verde    -> D5
 * LED amarelo  -> D6
 * LED vermelho -> D7
 * Buzzer       -> D8
 *
 * IMPORTANTE:
 * A pinagem acima é uma reconstrução funcional. Se a montagem física
 * original utilizava outros GPIOs, basta alterar as constantes abaixo.
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* WIFI_SSID = "SEU_WIFI";
const char* WIFI_PASSWORD = "SUA_SENHA";

// -------------------- PINOS --------------------

const uint8_t TRIG_PIN = D1;
const uint8_t ECHO_PIN = D2;

const uint8_t LED_VERDE = D5;
const uint8_t LED_AMARELO = D6;
const uint8_t LED_VERMELHO = D7;
const uint8_t BUZZER = D8;

// -------------------- LIMITES --------------------
// Distância entre o sensor e a água.
// Maior distância = nível mais baixo.
// Menor distância = nível mais alto.

const float LIMITE_ATENCAO = 30.0;
const float LIMITE_ALERTA = 15.0;

ESP8266WebServer server(80);

float distanciaAtual = -1.0;
String estadoAtual = "Aguardando leitura";

// --------------------------------------------------

float lerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Timeout evita que o ESP fique travado caso não haja eco.
  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duracao == 0) {
    return -1.0;
  }

  // Velocidade do som: aproximadamente 0,0343 cm/us.
  // Divide por 2 porque o som vai até a água e retorna.
  return (duracao * 0.0343) / 2.0;
}

void atualizarIndicadores(float distancia) {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(BUZZER, LOW);

  if (distancia < 0) {
    estadoAtual = "Sem leitura";
    return;
  }

  if (distancia > LIMITE_ATENCAO) {
    estadoAtual = "Normal";
    digitalWrite(LED_VERDE, HIGH);
  }
  else if (distancia > LIMITE_ALERTA) {
    estadoAtual = "Atenção";
    digitalWrite(LED_AMARELO, HIGH);
  }
  else {
    estadoAtual = "Alerta";
    digitalWrite(LED_VERMELHO, HIGH);

    // Alarme sonoro quando a água chega à faixa de alerta.
    digitalWrite(BUZZER, HIGH);
  }
}

void handleDados() {
  distanciaAtual = lerDistancia();
  atualizarIndicadores(distanciaAtual);

  String json = "{";
  json += "\"distancia\":" + String(distanciaAtual, 1) + ",";
  json += "\"estado\":\"" + estadoAtual + "\"";
  json += "}";

  if (distanciaAtual < 0) {
    server.send(503, "application/json", json);
  } else {
    server.send(200, "application/json", json);
  }
}

void handleRoot() {
  String mensagem;
  mensagem += "Monitoramento de Enchente\\n";
  mensagem += "ESP8266 conectado\\n";
  mensagem += "Use /dados para consultar a leitura.";
  server.send(200, "text/plain", mensagem);
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(BUZZER, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/dados", HTTP_GET, handleDados);

  server.begin();

  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  server.handleClient();
}
