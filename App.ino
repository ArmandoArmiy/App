//librerias
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobotDFPlayerMini.h>

// Declaración de pines
float temperaturaC = 0; // Temperatura inicial en 0
const int oneWireBus = 5; // pin de lectura de temperatura

// Creación de objetos
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600); // Inicializar SoftwareSerial

  pinMode(19, OUTPUT); // pin de salida de 
  
  pinMode(4, INPUT); // pin de lectura fotoresitencia 1
  pinMode(21, OUTPUT); // pin de salida de fotoresistencia 1

  pinMode(27, INPUT); // pin de lectura de proximidad
  pinMode(18, OUTPUT); // pin de salida de proximidad
}

void loop() {
  get_Temperature(); //Funcion para ejecutar la lectura de temperatura
  get_illumination(); //Funcion para ejecutar la lectura de Iliminacion
  get_proximity(); //Funcion para ejecutar la lectura de proximidad
  Serial.println("-----------------------------------------------------");
  delay(2000);
  
}

void get_proximity(){
  int prox = analogRead(27);
  if (prox > 1500) {
    digitalWrite(18, HIGH);  // Enciende el pin 19 si detecta un objeto
  } else {
    digitalWrite(18, LOW);   // Apaga el pin 19 si no detecta un objeto
  }
  Serial.println("| Valor del sensor de proximidad: " + String(prox));

}

void get_illumination(){
  int illu = analogRead(4);
  if (illu < 1900) {
    digitalWrite(21, HIGH);  // Enciende el pin 16 si la luz es baja
  } else {
    digitalWrite(21, LOW);   // Apaga el pin 16 si la luz es alta
  }
  Serial.println("| Valor de la iluminación 1: " + String(illu) + "\n");
}

//Funcion para obtener la temperatura + muestra de temperatura
void get_Temperature() {
  sensors.requestTemperatures();
  temperaturaC = sensors.getTempCByIndex(0);
  if (temperaturaC > 20) {
    digitalWrite(19, HIGH);  // Enciende el pin 19 si la temperatura es alta
  } else {
    digitalWrite(19, LOW);   // Apaga el pin 19 si la temperatura es baja
  }
  Serial.println("| Temp. Celsius: " + String(temperaturaC) + "ºC \n");
}

