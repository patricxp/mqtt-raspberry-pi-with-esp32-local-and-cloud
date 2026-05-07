# 🚀 IoT Bridge: ESP32 to Losant Cloud via MQTT

Proyek ini adalah sistem monitoring dan kontrol perangkat IoT berbasis **ESP32** yang terhubung ke platform **Losant Cloud**. Sistem ini menggunakan skrip Python sebagai *bridge* (jembatan) untuk menghubungkan broker MQTT lokal dengan broker MQTT Losant secara dua arah.

---

## 🏗️ Arsitektur Sistem
Sistem ini menggunakan skema komunikasi dual-broker:
1.  **ESP32**: Membaca sensor dan mengirim data ke broker lokal.
2.  **Python Bridge (`losant.py`)**: Menghubungkan data dari broker lokal ke cloud Losant.
3.  **Losant Cloud**: Platform untuk visualisasi data dan pengiriman perintah kontrol.

---

## 🛠️ Fitur Utama
* **Monitoring Real-time**: Pembacaan suhu dan kelembaban via sensor DHT11.
* **Dual-MQTT Bridge**: Integrasi broker lokal (misal: Mosquitto) dengan Losant.
* **Local Display**: Debugging status dan data sensor pada LCD I2C 16x2.
* **Remote Control**: Mengaktifkan kipas via perintah dari dashboard Losant.
* **Logika Status**: Klasifikasi otomatis kondisi suhu (PANAS, NORMAL, DINGIN) di sisi Python.

---

## ⚠️ Bagian yang WAJIB Diganti
Pastikan Anda menyesuaikan konfigurasi berikut agar program berjalan di lingkungan Anda:

### 1. Konfigurasi pada `nodemcu32_losant.ino`
* **WiFi**: Ganti `ssid` dan `password` sesuai jaringan Anda.
* **MQTT Server**: Ganti `mqtt_server` dengan IP address broker lokal (misal: IP laptop atau Raspberry Pi).

### 2. Konfigurasi pada `lolosa.py`
* **Losant Credentials**: Masukkan `DEVICE_ID`, `ACCESS_KEY`, dan `ACCESS_SECRET` milik Anda.
* **Local Broker**: Ganti `LOCAL_BROKER` jika broker lokal tidak berada di `localhost`.

---

## 🔌 Koneksi Hardware
| Komponen | Pin ESP32 | Keterangan |
| :--- | :--- | :--- |
| **Sensor DHT11** | `GPIO 27` | Data pin sensor |
| **Relay Kipas** | `GPIO 26` | Kontrol On/Off |
| **LCD I2C** | `SDA/SCL` | Address: `0x27` |

---
# logika
if suhu > 36:
status = "PANAS"
elif suhu < 26:
status = "DINGIN"
else:
status = "NORMAL"
---

## 🚀 Cara Penggunaan
1.  Jalankan broker MQTT lokal (contoh: Mosquitto).
2.  Unggah kode `.ino` ke ESP32 setelah menyesuaikan IP broker.
3.  Jalankan skrip Python: `python losant.py`.
4.  Pantau data pada LCD dan dashboard Losant.
