from smbus2 import SMBus

ADDR = 0x10
bus = SMBus(1)

def send_speeds(vel_l, vel_r):
    vel_l = int(vel_l)
    vel_r = int(vel_r)

    data = [
        (vel_l >> 8) & 0xFF, vel_l & 0xFF,
        (vel_r >> 8) & 0xFF, vel_r & 0xFF
    ]

    bus.write_i2c_block_data(ADDR, 0x02, data)

    print(f"Enviado -> Vel L: {vel_l} | Vel R: {vel_r}")

print("Control Balboa por I2C")
print("Rango de velocidad: -400 a 400")
print("Formato: velL velR  (ej: 200 200)")
print("q para salir")

while True:
    entrada = input(">> ").strip()

    if entrada.lower() == 'q':
        send_speeds(0, 0)
        print("Saliendo...")
        break

    try:
        velL, velR = map(int, entrada.split())
        send_speeds(velL, velR)
    except:
        print("Entrada inválida. Ejemplo correcto: 150 150")
