#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Konfigurasi WiFi & MQTT
const char* ssid = "mqttits";
const char* password = "12345678";
const char* mqtt_server = "10.244.178.128";

WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konfigurasi DHT
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

String kipas = "OFF";

// ===== FUNGSI UPDATE LCD UNTUK DEBUGGING =====
void updateLCD(float t, float h, String statusMQTT) {
  // Baris 1: Sensor Data
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 1);
  lcd.print("C ");  // T untuk Temp
  lcd.setCursor(9, 0);
  lcd.print("H:");
  lcd.print(h, 0);
  lcd.print("%  ");  // H untuk Humid

  // Baris 2: Debugging Status
  lcd.setCursor(0, 1);
  lcd.print("F:");
  lcd.print(kipas);  // F untuk Fan status
  lcd.print("   ");  // Menghapus sisa karakter
}

// ===== CALLBACK (TERIMA COMMAND) =====
void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  if (String(topic) == "robot/cmd") {
    kipas = msg;
    if (kipas == "ON") {
      digitalWrite(26, LOW);
    } else {
      digitalWrite(26, HIGH);
    }
    // Langsung update LCD saat ada perintah masuk
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    updateLCD(t, h, "OK");
  }
}

// ===== RECONNECT MQTT =====
void reconnect() {
  while (!client.connected()) {
    lcd.setCursor(0, 1);
    lcd.print("MQTT Conn...    ");

    if (client.connect("ESP32_Client")) {
      client.subscribe("robot/cmd");
      lcd.setCursor(0, 1);
      lcd.print("MQTT Connected  ");
      delay(1000);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("MQTT Fail:");
      lcd.print(client.state());
      delay(2000);
    }
  }
  lcd.clear();
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(26, OUTPUT);
  digitalWrite(26, HIGH);

  // STEP 1: WiFi Connection Status
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.clear();
  lcd.print("WiFi: OK");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
  lcd.clear();

  // STEP 2: MQTT Setup
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Baca Sensor
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  // Update Tampilan LCD
  updateLCD(suhu, kelembaban, "OK");

  // Kirim Data MQTT
  String payload = "{\"suhu\":" + String(suhu) + ",\"kelembaban\":" + String(kelembaban) + ",\"kipas\":\"" + kipas + "\"}";
  client.publish("robot/data", payload.c_str());

  delay(2000);
}
