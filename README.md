🚀 IoT Bridge: ESP32 to Losant Cloud via MQTT
Proyek ini adalah sistem monitoring dan kontrol perangkat IoT berbasis ESP32 yang terhubung ke platform Losant Cloud. Sistem ini menggunakan skrip Python sebagai bridge (jembatan) untuk menghubungkan broker MQTT lokal dengan broker MQTT Losant.

🛠️ Fitur Utama
Real-time Monitoring: Membaca data suhu dan kelembaban dari sensor DHT11.
Dual-MQTT Bridge: Menghubungkan komunikasi lokal (ESP32) ke Cloud (Losant).
Local Display: Menampilkan status koneksi dan data sensor pada LCD I2C 16x2.
Remote Control: Mengontrol kipas (On/Off) langsung dari dashboard Losant.
Status Logic: Klasifikasi otomatis kondisi suhu (PANAS, NORMAL, DINGIN).

🏗️ Arsitektur Sistem
ESP32: Membaca sensor DHT11 dan mengirim data ke Broker MQTT Lokal.
Local MQTT Broker: Menjadi perantara pesan antara ESP32 dan Python Bridge.
Python Bridge (lolosa.py): Mengambil data dari Broker Lokal dan meneruskannya ke Losant Cloud, serta meneruskan perintah kontrol dari Losant kembali ke ESP32.
Losant Dashboard: Visualisasi data dan tombol kontrol.

⚠️ Bagian yang WAJIB Diganti
Supaya program ini jalan, ada beberapa baris kode yang harus di sesuaikan:
1. Di File nodemcu32_UTS_pak_zaman.ino
Cari baris berikut dan sesuaikan dengan koneksi

// Konfigurasi WiFi
const char* ssid = "NAMA_WIFI";           // Ganti dengan SSID WiFi
const char* password = "PASSWORD_WIFI";   // Ganti dengan Password WiFi

// Konfigurasi MQTT Broker Lokal
const char* mqtt_server = "IP_ADDRESS_RASPBERRY PI"; // Ganti dengan IP laptop yang menjalankan broker (misal: Mosquitto)

2. Di File lolosa.py
Sesuaikan kredensial perangkat Losant
# ===== LOSANT CONFIG =====
DEVICE_ID = "ID_DEVICE"
ACCESS_KEY = "KEY"
ACCESS_SECRET = "SECRET"
# ===== LOCAL MQTT =====
LOCAL_BROKER = "localhost" # Ganti dengan IP RASPBERRY PI jika broker tidak di komputer yang sama

Siap, Bro! Ini draft README.md yang udah gue susun supaya tampilan repositori GitHub lo kelihatan pro, rapi, dan informatif. Gue fokusin ke bagian konfigurasi supaya lo (atau orang lain) nggak bingung pas mau running ulang.

🚀 IoT Bridge: ESP32 to Losant Cloud via MQTT
Proyek ini adalah sistem monitoring dan kontrol perangkat IoT berbasis ESP32 yang terhubung ke platform Losant Cloud. Sistem ini menggunakan skrip Python sebagai bridge (jembatan) untuk menghubungkan broker MQTT lokal dengan broker MQTT Losant.

🛠️ Fitur Utama
Real-time Monitoring: Membaca data suhu dan kelembaban dari sensor DHT11.

Dual-MQTT Bridge: Menghubungkan komunikasi lokal (ESP32) ke Cloud (Losant).

Local Display: Menampilkan status koneksi dan data sensor pada LCD I2C 16x2.

Remote Control: Mengontrol kipas (On/Off) langsung dari dashboard Losant.

Status Logic: Klasifikasi otomatis kondisi suhu (PANAS, NORMAL, DINGIN).

🏗️ Arsitektur Sistem
ESP32: Membaca sensor DHT11 dan mengirim data ke Broker MQTT Lokal.

Local MQTT Broker: Menjadi perantara pesan antara ESP32 dan Python Bridge.

Python Bridge (lolosa.py): Mengambil data dari Broker Lokal dan meneruskannya ke Losant Cloud, serta meneruskan perintah kontrol dari Losant kembali ke ESP32.

Losant Dashboard: Visualisasi data dan tombol kontrol.

⚠️ Bagian yang WAJIB Diganti
Supaya program ini jalan di lingkungan lo, ada beberapa baris kode yang harus lo sesuaikan:

1. Di File nodemcu32_UTS_pak_zaman.ino
Cari baris berikut dan sesuaikan dengan koneksi lo:

C++
// Konfigurasi WiFi
const char* ssid = "NAMA_WIFI_LO";           // Ganti dengan SSID WiFi
const char* password = "PASSWORD_WIFI_LO";   // Ganti dengan Password WiFi

// Konfigurasi MQTT Broker Lokal
const char* mqtt_server = "IP_ADDRESS_LAPTOP"; // Ganti dengan IP laptop yang menjalankan broker (misal: Mosquitto)
2. Di File lolosa.py
Sesuaikan kredensial perangkat Losant lo:

Python
# ===== LOSANT CONFIG =====
DEVICE_ID = "ID_DEVICE_LO"
ACCESS_KEY = "KEY_LO"
ACCESS_SECRET = "SECRET_LO"

# ===== LOCAL MQTT =====
LOCAL_BROKER = "localhost" # Ganti dengan IP jika broker tidak di komputer yang sama
🚀 Cara Instalasi
Prerequisites
Python 3.x

Arduino IDE (dengan library: WiFi.h, PubSubClient, DHT.h, LiquidCrystal_I2C)

MQTT Broker (contoh: Mosquitto) terinstall di lokal.

Langkah-langkah
1. Clone Repositori:
   git clone https://github.com/username-lo/nama-repo.git
2. Install Library Python:
   pip install paho-mqtt
3. Upload Sketch:
   Buka file .ino di Arduino IDE, sesuaikan konfigurasi, dan upload ke ESP32.
4. Jalankan Bridge:
   Pastikan MQTT Broker lokal sudah jalan, lalu eksekusi:
   python lolosa.py

📊 Format Data
Sistem ini mengirimkan data dalam format JSON sebagai berikut:
{
  "data": {
    "suhu": 30.5,
    "kelembaban": 70,
    "status": "NORMAL",
    "kipas": "OFF"
  }
}

📝 Catatan Tambahan
Pin GPIO: Program ini menggunakan GPIO 27 untuk DHT11 dan GPIO 26 untuk Relay Kipas.


