#include <DHT.h>

// sensor setup
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// pins
int fanPin = 7;
int redLED = 9;
int greenLED = 10;

// humidity limits
float highHum = 65.0;   // fan turns on
float lowHum = 62.0;    // fan turns off

bool fanOn = false;

void setup() {

  Serial.begin(9600);
  dht.begin();

  pinMode(fanPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // start with fan off and green light on
  digitalWrite(fanPin, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);

  Serial.println("Humidity system running...");
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if reading worked
  if (isnan(h) || isnan(t)) {
    Serial.println("error reading sensor");
    delay(2000);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%   Temp: ");
  Serial.println(t);

  // if humidity gets too high turn fan on
  if (fanOn == false && h >= highHum) {

    digitalWrite(fanPin, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    fanOn = true;

    Serial.println("humidity high, fan on");
  }

  // turn fan off when humidity drops
  if (fanOn == true && h <= lowHum) {

    digitalWrite(fanPin, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    fanOn = false;

    Serial.println("humidity normal, fan off");
  }

  delay(2000);   // read every 2 seconds
}