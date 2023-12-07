//librerias
#include <OneWire.h>
#include <DallasTemperature.h>

// Declaración de pines
float temperaturaC = 0; // Temperatura inicial en 0
const int oneWireBus = 5; // pin de lectura de temperatura

// Creación de objetos
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup() { 

  Serial.begin(9600);
  mySoftwareSerial.begin(4800);

  pinMode(19, OUTPUT); // pin de salida de temperatura
  pinMode(21, OUTPUT); // pin de salida de temperatura
  
  pinMode(4, INPUT); // pin de lectura fotoresitencia 1
  pinMode(22, OUTPUT); // pin de salida de fotoresistencia 1

  pinMode(27, INPUT); // pin de lectura de proximidad
  pinMode(13, OUTPUT); // pin de salida de proximidad
  pinMode(18, OUTPUT); // pin de salida de proximidad
}

void loop() {
  get_Temperature(); //Funcion para ejecutar la lectura de temperatura
  get_illumination(); //Funcion para ejecutar la lectura de Iliminacion
  get_proximity(); //Funcion para ejecutar la lectura de proximidad
  Serial.println("-----------------------------------------------------");
  delay(5000);
  
}

void get_proximity(){
  int prox = analogRead(27);
  if (prox > 1500) {
    digitalWrite(13, HIGH);  // Enciende el pin 13 si detecta un objeto
    digitalWrite(18, LOW);
    Serial.println("| Fuego Detectado!!!!!!!"); 
    Serial.println("  ___");
    Serial.println(" ('v')");
    Serial.println(" //-=\\");
    Serial.println(" \_=_/");
    Serial.println(" ^^ ^^");


    Serial.println(" Coyele Coyele !!!! "); 
  } else {
    digitalWrite(13, LOW);   // Apaga el pin 13 si no detecta un objeto
    digitalWrite(18, HIGH); 
  }
  

}

void get_illumination(){
  int illu = analogRead(4);
  if (illu < 1300) {
    digitalWrite(22, HIGH);  // Enciende el pin 22 si la luz es baja
    Serial.println("| Luces encendidas ");
  } else {
    digitalWrite(22, LOW);   // Apaga el pin 22 si la luz es alta
  }
  Serial.println("| Valor de la iluminación 1: " + String(illu) + "\n");
}

//Funcion para obtener la temperatura + muestra de temperatura
void get_Temperature() {
  sensors.requestTemperatures();
  temperaturaC = sensors.getTempCByIndex(0);
  if (temperaturaC > 20) {
    digitalWrite(19, HIGH);  // Enciende el pin 19 si la temperatura es alta
    digitalWrite(21, LOW);  
  } else {
    digitalWrite(19, LOW);   
    digitalWrite(21, HIGH); // Enciende el pin 19 si la temperatura es baja
  }
  Serial.println("| Temp. Celsius: " + String(temperaturaC) + "ºC \n");
}

