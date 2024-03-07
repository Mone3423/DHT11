#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <DHT.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
#define DHTPIN 2 // Cambiar a tu pin digital seleccionado
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

    // Inicializar la primera pantalla OLED con dirección I2C 0x3C
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display(); // Mostrar el contenido (cargar el buffer)
  delay(2000); // Esperar 2 segundos
  
  // Inicializar sensor DHT
  dht.begin();

  // Limpiar la pantalla antes de mostrar los datos
  display.clearDisplay();
  display.display();
}

void loop() {
  // Leer la temperatura y la humedad del sensor DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Verificar si la lectura del sensor es válida
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Error al leer la temperatura o humedad"));
    return;
  }
  
  // Limpiar la pantalla antes de mostrar los nuevos datos
  display.clearDisplay();
  temperature=temperature;
  // Mostrar la temperatura y la humedad en la pantalla OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 10);
  display.print("Humedad: ");
  display.print(humidity);
  display.println(" %");

  // Actualizar la pantalla para mostrar los nuevos datos
  display.display();

  // Esperar un tiempo antes de tomar la siguiente lectura
  delay(5000);
}
