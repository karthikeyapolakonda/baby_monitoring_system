#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (I2C address 0x27, 16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
int gyroPin = A0;        // Gyro sensor analog pin
int tempPin = A1;        // Temperature sensor analog pin
int buzzerPin = D5;      // Buzzer pin

// Variables
int movementValue = 0;
float temperature = 0;

// Threshold values
int movementThreshold = 500;
float tempThreshold = 35.0;

void setup() {
Serial.begin(9600);

pinMode(buzzerPin, OUTPUT);

lcd.begin();
lcd.backlight();

lcd.setCursor(0, 0);
lcd.print("Smart Cradle");
delay(2000);
lcd.clear();
}

void loop() {

  // Read gyro sensor (movement)
movementValue = analogRead(gyroPin);

  // Read temperature sensor (convert to Celsius)
  int tempRaw = analogRead(tempPin);
  temperature = (tempRaw * 5.0 * 100.0) / 1024.0;

  // Display values on LCD
lcd.setCursor(0, 0);
lcd.print("Temp:");
lcd.print(temperature);
lcd.print(" C ");

lcd.setCursor(0, 1);
lcd.print("Move:");
lcd.print(movementValue);
lcd.print("   ");

  // Check abnormal conditions
  if (movementValue>movementThreshold || temperature >tempThreshold) {
digitalWrite(buzzerPin, HIGH);  // Turn ON buzzer
  } else {
digitalWrite(buzzerPin, LOW);   // Turn OFF buzzer
  }

  // Serial Monitor (for debugging)
Serial.print("Temp: ");
Serial.print(temperature);
Serial.print(" | Move: ");
Serial.println(movementValue);

delay(1000); // 1 second delay
}
