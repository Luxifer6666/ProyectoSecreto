#include <Wire.h>
#include <Balboa32U4.h>

#define I2C_ADDR 0x10

Balboa32U4Motors motors;

volatile char comando = 'x';

void setup() {
  Wire.begin(I2C_ADDR);
  Wire.onReceive(recibir);

  motors.setSpeeds(0, 0); // motores apagados
}

void loop() {
  ejecutarComando();
}

// -------- I2C --------
void recibir(int n) {
  if (n < 2) return;

  byte cmd = Wire.read();   // comando I2C
  if (cmd == 0x01 && Wire.available()) {
    comando = Wire.read(); // letra recibida
  }
}

// -------- CONTROL MOTORES --------
void ejecutarComando() {
  int vel = 150; // velocidad base (0–400)

  switch (comando) {
    case 'w': // adelante
      motors.setSpeeds(vel, vel);
      break;

    case 's': // atrás
      motors.setSpeeds(-vel, -vel);
      break;

    case 'a': // izquierda
      motors.setSpeeds(-vel, vel);
      break;

    case 'd': // derecha
      motors.setSpeeds(vel, -vel);
      break;

    case 'x': // stop
    default:
      motors.setSpeeds(0, 0);
      break;
  }
}
