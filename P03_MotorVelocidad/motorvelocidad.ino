#include <Wire.h>
#include <Balboa32U4.h>

#define I2C_ADDR 0x10

Balboa32U4Motors motors;

void setup() {
  Serial.begin(115200);     
  Wire.begin(I2C_ADDR);       
  Wire.onReceive(recibir);

  motors.setSpeeds(0, 0);

  Serial.println("Balboa listo. Esperando datos I2C...");
}

void loop() {
  // Todo se maneja por I2C
}

void recibir(int n) {
  if (n != 5) {
    Serial.print("Error: bytes recibidos = ");
    Serial.println(n);
    return;
  }

  byte cmd = Wire.read();

  if (cmd == 0x02) {   
    int velL = (Wire.read() << 8) | Wire.read();
    int velR = (Wire.read() << 8) | Wire.read();

    // Seguridad: limitar rango
    velL = constrain(velL, -300, 300);
    velR = constrain(velR, -300, 300);

    Serial.print("Recibido -> Vel L: ");
    Serial.print(velL);
    Serial.print(" | Vel R: ");
    Serial.println(velR);

    motors.setSpeeds(velL, velR);
  }
}
