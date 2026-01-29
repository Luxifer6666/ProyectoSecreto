#include <Wire.h>

#define I2C_ADDR 0x10

volatile char ultimo = '?';

void setup() {
  Wire.begin(I2C_ADDR);
  Wire.onReceive(recibir);
  Wire.onRequest(enviar);
}

void loop() {}

void recibir(int n) {
  if (n < 1) return;

  byte cmd = Wire.read();

  if (cmd == 0x01 && Wire.available()) {
    ultimo = Wire.read();   // guardar dato
  }
}

void enviar() {
  Wire.write('O');
  Wire.write('K');
  Wire.write(':');
  Wire.write(ultimo);
}
