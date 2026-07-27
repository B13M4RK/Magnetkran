#include <Arduino.h>
#include <IRremote.hpp>

int EmpfaengerPin = A0;
bool magnetIsPowered = false;



void turnLeft() {
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);

  delay(100);

  digitalWrite(12, LOW);
}

void turnRight() {
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);

  delay(100);

  digitalWrite(13, LOW);
}

void turnDown() {
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);

  delay(100);

  digitalWrite(8, LOW);
}

void turnUp() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);

  delay(100);

  digitalWrite(9, LOW);
}

void turnForward() {

  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);

  delay(100);

  digitalWrite(10, LOW);

}

void turnBackward() {

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);

  delay(100);

  digitalWrite(11, LOW);
}

void toggleMagnet() {

  if (!magnetIsPowered) {

    digitalWrite(A1, HIGH); // LED
    Serial.println("magnet turned on");
    magnetIsPowered = true;
    digitalWrite(A2, HIGH);

  } else {

    digitalWrite(A1, LOW); // LED
    Serial.println("magnet turned off");
    magnetIsPowered = false;
    digitalWrite(A2, LOW);

  }
  
}

void checkIrSignal() {
  if (IrReceiver.decode()) {

    int cmd = IrReceiver.decodedIRData.command; // Tastencode speichern
    bool isRepeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

    IrReceiver.resume(); // Empfänger zurücksetzen

    // ❗ Magnet: nur echte neue Taste, KEIN Repeat
    if (cmd == 18) {
      if (isRepeat) return;   // <- verhindert togglen beim Halten
      Serial.println("magnet_toggle");
      toggleMagnet();
      return;
    }

    if (cmd > 0 && cmd < 95) { // Gültigkeit


      Serial.print("Dezimalwert: ");
      Serial.print(cmd);
      Serial.print(" -> ");

      switch (cmd) {

        //case 18: Serial.println("magnet_toggle"); toggleMagnet(); break;
        case 20: Serial.println("left_arrow"); turnLeft(); break;
        case 24: Serial.println("right_arrow"); turnRight(); break;
        case 26: Serial.println("forward_arrow"); turnForward(); break;
        case 27: Serial.println("up_arrow"); turnUp(); break;
        case 30: Serial.println("backward_arrow"); turnBackward(); break;
        case 31: Serial.println("down_arrow"); turnDown(); break;

        default: // nicht deklarierter Befehl
          Serial.println("Unbekannte Taste");
          break;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  for (int pin = 2; pin <= 5; pin++) {
    pinMode(pin, OUTPUT);
  }

  Serial.begin(9600);

  IrReceiver.begin(EmpfaengerPin);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
}

void loop() {

  checkIrSignal();

  
}
