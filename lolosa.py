import paho.mqtt.client as mqtt
import json
import time

# ===== LOSANT CONFIG =====
DEVICE_ID = "69dce1266d988936acb81a3a"
ACCESS_KEY = "38dddd09-5391-423d-9be4-3724700e1cd9"
ACCESS_SECRET = "c683afb5ab990402507303dbc89b98328ff6547d49add5be4db6af51bdaaedf8"

LOSANT_BROKER = "broker.losant.com"

# ===== LOCAL MQTT =====
LOCAL_BROKER = "localhost"

# =========================

kipas_state = "OFF"
data_esp = {
    "suhu": 0,
    "kelembaban": 0
}

# ===== LOSANT CALLBACK =====
def on_connect_losant(client, userdata, flags, reasonCode, properties=None):
    if reasonCode == 0:
        print("✅ Connected ke Losant")
        client.subscribe(f"losant/{DEVICE_ID}/command")
    else:
        print("❌ Gagal connect Losant")

def on_message_losant(client, userdata, msg):
    global kipas_state

    payload = json.loads(msg.payload.decode())

    if payload["name"] == "kipas":
        kipas_state = payload["payload"]["state"]

        print("📩 Dari Losant:", kipas_state)

        # forward ke ESP32
        local_client.publish("robot/cmd", kipas_state)

# ===== LOCAL MQTT CALLBACK =====
def on_connect_local(client, userdata, flags, rc):
    print("✅ Connected ke MQTT lokal")
    client.subscribe("robot/data")

def on_message_local(client, userdata, msg):
    global data_esp

    payload = json.loads(msg.payload.decode())
    data_esp = payload

    print("📡 Data dari ESP32:", data_esp)

# ==============================

# CLIENT LOSANT
losant = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, client_id=DEVICE_ID)
losant.username_pw_set(ACCESS_KEY, ACCESS_SECRET)
losant.on_connect = on_connect_losant
losant.on_message = on_message_losant
losant.connect(LOSANT_BROKER, 1883, 60)
losant.loop_start()

# CLIENT LOCAL
local_client = mqtt.Client()
local_client.on_connect = on_connect_local
local_client.on_message = on_message_local
local_client.connect(LOCAL_BROKER, 1883, 60)
local_client.loop_start()

print("🚀 Sistem bridge berjalan...")

try:
    while True:
        suhu = data_esp.get("suhu", 0)
        kelembaban = data_esp.get("kelembaban", 0)
        kipas_state = data_esp.get("kipas", 0)
        # logika
        if suhu > 36:
            status = "PANAS"
        elif suhu < 26:
            status = "DINGIN"
        else:
            status = "NORMAL"

        data = {
            "suhu": suhu,
            "kelembaban": kelembaban,
            "status": status,
            "kipas": kipas_state
        }

        payload = {
            "data": data
        }

        losant.publish(f"losant/{DEVICE_ID}/state", json.dumps(payload))

        print("☁️ Kirim ke Losant:", data)

        time.sleep(5)

except KeyboardInterrupt:
    print("STOP")

losant.loop_stop()
local_client.loop_stop()
