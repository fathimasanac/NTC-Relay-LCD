#include <LiquidCrystal.h>

// LCD pins (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define NTC_PIN A0              // Analog pin connected to divider
#define RELAY_PIN 7             // Relay IN pin

#define NOMINAL_RESISTANCE 10000 // 10kΩ at 25°C
#define NOMINAL_TEMPERATURE 25   // 25°C
#define B_COEFFICIENT 3950       // Beta value (from datasheet)
#define SERIES_RESISTOR 10000    // The fixed 10k resistor

void setup() {

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF

  lcd.begin(16, 2);
  lcd.print("NTC Thermistor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(NTC_PIN);

  // Convert ADC to resistance
  float resistance = SERIES_RESISTOR / ((1023.0 / adcValue) - 1);

  // Steinhart equation
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;     // (R/Ro)
  steinhart = log(steinhart);                      // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                      // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                     // Invert
  steinhart -= 273.15;                             // Convert to °C


  lcd.clear();
  lcd.setCursor(0, 0);  //first column, first row
  lcd.print("Temp: ");
  lcd.print(steinhart, 1); // 1 decimal place
  lcd.print((char)223);    // ° symbol
  lcd.print("C");

  lcd.setCursor(0, 1); //first column , second row
  lcd.print("Relay: ");
  if (steinhart >= 38.0) {
    digitalWrite(RELAY_PIN, HIGH); // Relay ON
    lcd.print("ON");
  }
  else{
    digitalWrite(RELAY_PIN, LOW);  // Relay OFF
    lcd.print("OFF");
  }
  
  delay(1000);
}
