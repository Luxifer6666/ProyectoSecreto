from smbus2 import SMBus
import time

ADDR = 0x10
bus = SMBus(1)

while True:
    # 1️⃣ Enviar comando + dato
    bus.write_i2c_block_data(ADDR, 0x01, [ord('A')])
    print("Enviado: A")

    time.sleep(0.1)   # tiempo REALISTA para el slave

    # 2️⃣ Leer respuesta
    data = bus.read_i2c_block_data(ADDR, 0x02, 4)
    resp = ''.join(chr(b) for b in data)
    print("Recibido:", resp)

    time.sleep(1)
