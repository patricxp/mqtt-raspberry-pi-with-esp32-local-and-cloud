🚀 IoT Bridge System (ESP32 ↔ MQTT Lokal ↔ Losant)

Sistem ini adalah implementasi IoT bridge antara perangkat ESP32 (NodeMCU-32) dengan platform cloud Losant menggunakan protokol MQTT.

Arsitektur utamanya:

ESP32 → MQTT Lokal → Python Bridge → Losant Cloud
                           ↑
                     Command dari Cloud
🧠 Gambaran Sistem

Sistem terdiri dari 2 program utama:

1. 📟 ESP32 (Arduino - .ino)

Berfungsi sebagai:

Sensor reader (suhu & kelembaban)
Publisher data ke MQTT lokal
Subscriber command (contoh: ON/OFF kipas)
2. 🐍 Python Bridge (lolosa.py)

Berfungsi sebagai:

Penghubung antara MQTT lokal dan Losant
Forward data dari ESP32 → Losant
Forward command dari Losant → ESP32
Menambahkan logika sederhana (status suhu)
⚙️ Cara Kerja Sistem

ESP32 kirim data ke topic:

robot/data

Python menerima data → proses → kirim ke:

losant/{DEVICE_ID}/state

Jika ada command dari Losant:

losant/{DEVICE_ID}/command

Python forward ke:

robot/cmd
ESP32 eksekusi command (misalnya nyalakan kipas)
📦 Struktur Data
Data dari ESP32
{
  "suhu": 30,
  "kelembaban": 70,
  "kipas": "OFF"
}
Data ke Losant
{
  "data": {
    "suhu": 30,
    "kelembaban": 70,
    "status": "NORMAL",
    "kipas": "OFF"
  }
}
🔧 Konfigurasi yang WAJIB Diganti

Jangan asal jalanin — ini bagian yang sering bikin orang nyangkut 👇

🔑 Di lolosa.py
1. Losant Credential
DEVICE_ID = "GANTI_INI"
ACCESS_KEY = "GANTI_INI"
ACCESS_SECRET = "GANTI_INI"

👉 Ambil dari dashboard Losant.

2. MQTT Broker Lokal
LOCAL_BROKER = "localhost"

Kalau:

pakai PC sendiri → tetap localhost
pakai Raspberry Pi / server lain → isi IP:
LOCAL_BROKER = "192.168.1.10"
📡 Di ESP32 (.ino)

Yang biasanya perlu lo ubah:

1. WiFi
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
2. MQTT Broker
const char* mqtt_server = "IP_BROKER";

⚠️ Harus sama dengan LOCAL_BROKER di Python

3. Topic MQTT (kalau mau custom)
"robot/data"
"robot/cmd"

Kalau diubah di ESP32 → HARUS diubah juga di Python

🧪 Logika Tambahan (Python)

Di sini ada sedikit “otak” sistem:

if suhu > 36:
    status = "PANAS"
elif suhu < 26:
    status = "DINGIN"
else:
    status = "NORMAL"

👉 Ini bisa lo kembangkan jadi:

fuzzy logic
AI classification
trigger alarm
auto control kipas
▶️ Cara Menjalankan
1. Jalankan MQTT Broker

Contoh:

mosquitto
2. Jalankan Python
python lolosa.py
3. Upload ESP32
Pastikan sudah connect ke WiFi & broker
📚 Dependency Python

Install dulu:

pip install paho-mqtt
⚠️ Catatan Penting
Sistem ini real-time tapi polling-based (5 detik)
Kalau delay terasa → kurangi time.sleep(5)
Tidak ada retry handling (kalau koneksi putus → bye 😄)
💡 Ide Pengembangan (Kalau Lo Mau Naik Level)

Kalau cuma segini, jujur masih “skripsi aman”. Mau lebih niat?

Tambah buffer data (queue)
Gunakan async MQTT (non-blocking)
Implementasi fuzzy logic (cocok sama project lo)
Tambah dashboard lokal (Flask / Node-RED)
Integrasi ke multiple ESP32 (multi-node system)
