#include <Arduino.h>
#include <bitset>
#include <string>
#include <DHT.h>

#define BIN16PIN 32
#define BIN8PIN 33
#define BIN4PIN 25
#define BIN2PIN 26
#define BIN1PIN 27
#define DHT11PIN 14
#define CONTROLPIN 12
DHT dht(DHT11PIN, DHT11);

int BIN_PIN_ARRAY[] = {BIN16PIN, BIN8PIN, BIN4PIN, BIN2PIN, BIN1PIN};

void setup()
{
  pinMode(BIN16PIN, OUTPUT);
  pinMode(BIN8PIN, OUTPUT);
  pinMode(BIN4PIN, OUTPUT);
  pinMode(BIN2PIN, OUTPUT);
  pinMode(BIN1PIN, OUTPUT);
  pinMode(CONTROLPIN, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}
void loop()
{

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  std::bitset<5> x(temp);
  std::bitset<7> y(humi);
  digitalWrite(CONTROLPIN, HIGH);

  for (int i = 0; i < 5; i++)
  {
    if (x[i] == 1)
    {
      digitalWrite(BIN_PIN_ARRAY[i], HIGH);
    }
    else
    {
      digitalWrite(BIN_PIN_ARRAY[i], LOW);
    }
    // digitalWrite(BIN_PIN_ARRAY[i], HIGH);
  }

  delay(3000);
  digitalWrite(CONTROLPIN, LOW);

  for (int i = 0; i < 5; i++)
  {
    if (y[i] == 1)
    {
      digitalWrite(BIN_PIN_ARRAY[i], HIGH);
    }
    else
    {
      digitalWrite(BIN_PIN_ARRAY[i], LOW);
    }
    // digitalWrite(BIN_PIN_ARRAY[i], HIGH);
  }

  std::string temp_str = x.to_string<char, std::string::traits_type, std::string::allocator_type>();
  std::string humi_str = y.to_string<char, std::string::traits_type, std::string::allocator_type>();
  Serial.print("Temperature: ");
  Serial.write(temp_str.c_str());
  Serial.print(" - ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.print(humi_str.c_str());
  Serial.print(" - ");
  Serial.print(humi);
  delay(3000);
}