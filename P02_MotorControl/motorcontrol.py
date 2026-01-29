from smbus2 import SMBus

ADDR = 0x10
bus = SMBus(1)

print("Control Balboa")
print("w=adelante | s=atras | a=izq | d=der | x=stop | q=salir")

while True:
    tecla = input(">> ").strip().lower()

    if not tecla:
        continue

    if tecla == 'q':
        bus.write_i2c_block_data(ADDR, 0x01, [ord('x')])
        print("Saliendo...")
        break

    if tecla in ['w', 'a', 's', 'd', 'x']:
        bus.write_i2c_block_data(ADDR, 0x01, [ord(tecla)])
        print("Enviado:", tecla)
    else:
        print("Comando no válido")
