//librerias
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobotDFPlayerMini.h>

// Declaración de pines
float temperaturaC = 0; // Temperatura inicial en 0
const int oneWireBus = 5; // pin de lectura de temperatura
//static const uint8_t PIN_MP3_TX = 25; // Conectado al RX del módulo
//static const uint8_t PIN_MP3_RX = 26; // Conectado al TX del módulo
//SoftwareSerial mySerial(PIN_MP3_RX, PIN_MP3_TX); // Configurar una instancia de SoftwareSerial

// Creación de objetos
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // Inicializar SoftwareSerial
  pinMode(19, OUTPUT); // pin de salida de temperatura
  pinMode(4, INPUT); // pin de lectura fotoresitencia 1
  pinMode(21, OUTPUT); // pin de salida de fotoresistencia 1
  pinMode(2, INPUT); // pin de lectura fotoresitencia 2
  pinMode(12, OUTPUT); // pin de salida de fotoresistencia 2
  pinMode(27, INPUT); // pin de lectura de proximidad
  pinMode(18, OUTPUT); // pin de salida de proximidad

  if (player.begin(Serial2)) {
    Serial.println("OK");
    // Establecer el volumen al máximo (0 a 30).
    player.volume(20);
    // Reproducir el primer archivo MP3 en la tarjeta SD
    player.play(1);
  } else {
    Serial.println("¡Error al conectar con DFPlayer Mini!");
  }
}

void loop() {
  get_Temperature(); //Funcion para ejecutar la lectura de temperatura
  get_illumination(); //Funcion para ejecutar la lectura de Iliminacion
  get_proximity(); //Funcion para ejecutar la lectura de proximidad
  //Serial.println("-----------------------------------------------------");
  //delay(2000);
  
}

void get_proximity(){
  int prox = analogRead(27);
  if (prox > 1500) {
    digitalWrite(18, HIGH);  // Enciende el pin 19 si detecta un objeto
    player.next();
  } else {
    digitalWrite(18, LOW);   // Apaga el pin 19 si no detecta un objeto
  }
  //Serial.println("Valor del sensor de proximidad: " + String(prox));

}

void get_illumination(){
  int illu = analogRead(4);
  if (illu < 1900) {
    digitalWrite(21, HIGH);  // Enciende el pin 16 si la luz es baja
  } else {
    digitalWrite(21, LOW);   // Apaga el pin 16 si la luz es alta
  }
  //Serial.println("Valor de la iluminación 1: " + String(illu) + "\n");

  int illu2 = analogRead(2);
  if (illu2 < 1900) {
    digitalWrite(12, HIGH);  // Enciende el pin 16 si la luz es baja
  } else {
    digitalWrite(12, LOW);   // Apaga el pin 16 si la luz es alta
  }
  //Serial.println("Valor de la iluminación 2: " + String(illu2) + "\n");
}

//Funcion para obtener la temperatura + muestra de temperatura
void get_Temperature() {
  sensors.requestTemperatures();
  temperaturaC = sensors.getTempCByIndex(0);
  if (temperaturaC > 20) {
    digitalWrite(19, HIGH);  // Enciende el pin 18 si la temperatura es alta
  } else {
    digitalWrite(19, LOW);   // Apaga el pin 18 si la temperatura es baja
  }
  //Serial.println("Temp. Celsius: " + String(temperaturaC) + "ºC \n");
}

