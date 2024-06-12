import paho.mqtt.client as mqtt
import time
import random
client = mqtt.Client(callback_api_version = mqtt.CallbackAPIVersion.VERSION1)
client.connect("test.mosquitto.org", 1883, 60)

def downlink(data):
    random_number = random.randint(1, 10000)
    id = str(random_number)
    msg = "[{\"macAddr\":\"0000000020200005\",\"data\":\"" + data + "\",\"id\":\"" + id + "\",\"extra\":{\"port\":2,\"txpara\":\"2\"}}]"
    client.publish("GIOT-GW/DL/000080029c0ff65e", msg)
    print("downlink success " + data)

def string_to_hex(s):
    hex_string = ''.join(format(ord(char), '02x') for char in s)
    return hex_string

goods_name = input("請輸入商品名稱: ")
goods_price = input("請輸入商品價格: ")
# goods_status = input("請輸入商品狀態(0: 缺貨中, 1: 正常上架, 2: 特價中): ")

hex_name = string_to_hex(goods_name)
hex_price = string_to_hex(goods_price)

hex_message = f"{hex_name}7c{hex_price}"    # 7c(|) is the separator between name and price

while(1):
    downlink(hex_message)
    time.sleep(5)
