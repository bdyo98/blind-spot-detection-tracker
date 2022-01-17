#include <WiFi.h>
#include <PubSubClient.h>
#include<SoftwareSerial.h>
SoftwareSerial front(2, 3);
SoftwareSerial right(4, 5);
SoftwareSerial left(7, 6);
SoftwareSerial back(8, 9);



const char* ssid = "bsters";
const char* password = "bsters";


//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "broker.emqx.io:8083";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


int dist;
int strength;
int check;
int uart[9];
int i;
const int HEADER = 0x59;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  front.begin(115200);
  right.begin(115200);
  left.begin(115200);
  //  back.begin(115200);
}

void loop()
{
  readCamOn();
  front.begin(115200);
  if (front.available()) {
    if (front.read() == HEADER) {
      uart[0] = HEADER;
      if (front.read() == HEADER) {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {
          uart[i] = front.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
          if (dist < 150)
          {
            digitalWrite(13, HIGH);
            digitalWrite(12, HIGH);
            delay(100);
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);
            delay(100);
            digitalWrite(13, HIGH);
            digitalWrite(12, HIGH);

          }
          else
            digitalWrite(13, LOW);
            digitalWrite(12, LOW);
        }
      }
    }
    front.end();
  }
  right.begin(115200);
  if (right.available())
  {
    if (right.read() == HEADER)
    {
      uart[0] = HEADER;
      if (right.read() == HEADER)
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)
        {
          uart[i] = right.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))
        {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
          if (dist < 80)
          {
            digitalWrite(12, HIGH);
            delay(100);
            digitalWrite(12, LOW);
            delay(100);
            digitalWrite(12, HIGH);
          }
          else
            digitalWrite(12, LOW);
        }
      }
    }
    right.end();
  }
  left.begin(115200);
  if (left.available())
  {
    left.listen();
    if (left.read() == HEADER)
    {
      uart[0] = HEADER;
      if (left.read() == HEADER)
      {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)
        {
          uart[i] = left.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))
        {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
          if (dist < 80)
          {
            digitalWrite(13, HIGH);
            delay(100);
            digitalWrite(13, LOW);
            delay(10);
            digitalWrite(13, HIGH);
          }
          else
            digitalWrite(13, LOW);
        }
      }
    }
    left.end();
    
  }
  //  if (back.available())
  //  {
  //    back.listen();
  //    if (back.read() == HEADER)
  //    {
  //      uart[0] = HEADER;
  //      if (back.read() == HEADER)
  //      {
  //        uart[1] = HEADER;
  //        for (i = 2; i < 9; i++)
  //        {
  //          uart[i] = back.read();
  //        }
  //        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
  //        if (uart[8] == (check & 0xff))
  //        {
  //          dist = uart[2] + uart[3] * 256;
  //          strength = uart[4] + uart[5] * 256;
  //          if (dist < 150)
  //          {
  //            digitalWrite(12, HIGH);
  //            delay(10);
  //            digitalWrite(12, LOW);
  //            delay(10);
  //            digitalWrite(12, HIGH);
  //          }
  //          else
  //            digitalWrite(12, LOW);
  //        }
  //      }
  //    }
  //  }
}
