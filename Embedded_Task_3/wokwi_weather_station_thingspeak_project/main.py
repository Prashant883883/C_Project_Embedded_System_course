import network
import urequests
import time
from machine import Pin
import dht

API_KEY = "S7O0RSYO41OMAQB2"
CHANNEL_ID = "3200459"

WIFI_SSID = "iPhone"
WIFI_PASS = "12345678"

sensor = dht.DHT22(Pin(15))

print("Connecting to WiFi ", end="")
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(WIFI_SSID, WIFI_PASS)

while not wifi.isconnected():
    print(".", end="")
    time.sleep(0.5)

print("\nConnected!")
print("IP Address:", wifi.ifconfig()[0])

while True:
    try:
        sensor.measure()
        temperature = sensor.temperature()
        humidity = sensor.humidity()

        print("Temperature:", temperature, "°C  Humidity:", humidity, "%")

        url = (
            "http://api.thingspeak.com/update?"
            f"api_key={API_KEY}&field1={temperature}&field2={humidity}"
        )

       
        response = urequests.request("GET", url)

        print("ThingSpeak response:", response.text)

        response.close()

    except Exception as e:
        print("Error:", e)

    time.sleep(20)
