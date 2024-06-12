#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>

// Dirección I2C de la pantalla LCD (puedes cambiar esto según la dirección real de tu pantalla)
#define LCD_ADDRESS 0x27
// Configuración de la pantalla LCD (puedes cambiar esto según las dimensiones de tu pantalla)
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Inicialización de la pantalla LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  // Inicialización de la pantalla LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // Populate temp and humidity objects with fresh data
  
  // Imprime los valores de temperatura y humedad en el monitor serial
  Serial.print("Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" degrees C");
  Serial.print("Humidity: "); 
  Serial.print(humidity.relative_humidity); 
  Serial.println("% rH");
  
  // Borra el contenido previo de la pantalla LCD
  lcd.clear();

  // Imprime los valores de temperatura y humedad en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp.temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity.relative_humidity);
  lcd.print("%");

  // Espera 500 milisegundos antes de repetir el proceso
  delay(500);
}
