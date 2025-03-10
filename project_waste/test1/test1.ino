#include <ESP32Servo.h>


#include <WiFi.h>
#include <HTTPClient.h>
Servo servo1;
Servo servo2;
Servo servo3;
int i = 0;

const char* ssid     ="Roshan";
const char* password ="roshan1234";

const char* serverName ="http://192.168.245.145:5000/test";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
const int echo = 22;
const int trig = 23;
int m1 = 21;
long duration = 0;
int distance = 0;
bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
bool sndflag = 0, aflag = 1;

void setup_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("CONNECTING.....");
  }
  Serial.println("CONNECTED");
}

void send_data(String A)
{
  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = String(A);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.println(httpResponseCode);
      if (httpResponseCode > 0)
      {
        String res = http.getString();
        Serial.println(res);
        if (res == "A")
        {
          flag1 = 1;
          aflag = 1;

        }
        if (res == "B")
        {
          flag2 = 1;
        }
        if (res == "C")
        {
          flag3 = 1;
        }
        if (res == "D")
        {
          flag4 = 1;
        }
      }
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void setup()
{
  Serial.begin(9600);
  setup_wifi();
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(m1, OUTPUT);
  servo1.attach(13);
  servo2.attach(12);
  servo3.attach(14);
  servo1.write(0);
  servo2.write(0);
  servo3.write(90);
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration * 0.034 / 2);
  Serial.print("Distance=");
  Serial.println(distance);
  delay(500);

  if (distance <= 20 && sndflag == 0) {
    sndflag = 1;
    aflag = 1;
    digitalWrite(m1, LOW);
    send_data("A");
  }
  else if (distance <= 20 && aflag == 1)
  {
    send_data("B");
  }
  else
  {
    sndflag = 0;
    digitalWrite(m1, HIGH);
  }

  if (flag1 == 1) {
    ///////////////////////////waste 1 started

    //down servo2
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    ///////PICK SERVO
    for (i = 90; i >= 0; i--) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////up servo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    /////////////////////rotate servo
    for (i = 0; i <= 130; i++) {
      Serial.println("opn");
      servo1.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////////////////down servo
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    ///////PLACE SERVO


    for (i = 0; i <= 90; i++) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);


    ///////////////////////////////upservo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ////////////////////rotate back servo
    for (i = 130; i >= 0; i--) {
      Serial.println("close");
      servo1.write(i);
      delay(10);
    }
    delay(1000);
    flag1 = 0;

    //////////////////////////waste 1 closed
  }

  if (flag2 == 1) {
    ///////////////////////////waste 2 started

    //down servo2
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    ///////PICK SERVO

    for (i = 90; i >= 0; i--) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////up servo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    /////////////////////rotate servo
    for (i = 0; i <= 110; i++) {
      Serial.println("opn");
      servo1.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////////////////down servo
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    ///////PLACE SERVO
    for (i = 0; i <= 90; i++) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////////////////////upservo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ////////////////////rotate back servo
    for (i = 110; i >= 0; i--) {
      Serial.println("close");
      servo1.write(i);
      delay(10);
    }
    delay(1000);
    flag2 = 0;
    //////////////////////////waste 2 closed
  }

  if (flag3 == 1) {
    ///////////////////////////waste 3 started

    //down servo2
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ///////PICK SERVO


    for (i = 90; i >= 0; i--) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);


    ///////////////up servo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    /////////////////////rotate servo
    for (i = 0; i <= 90; i++) {
      Serial.println("opn");
      servo1.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////////////////down servo
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ///////PLACE SERVO

    for (i = 0; i <= 90; i++) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);
    ///////////////////////////////upservo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ////////////////////rotate back servo
    for (i = 90; i >= 0; i--) {
      Serial.println("close");
      servo1.write(i);
      delay(10);
    }
    delay(1000);
    flag3 = 0;

    //////////////////////////waste 3 closed
  }
  if (flag4 == 1) {
    ///////////////////////////waste 4 started

    //down servo2
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    /////////////PICK SERVO

    for (i = 90; i >= 0; i--) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);
    ///////////////up servo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);

    /////////////////////rotate servo
    for (i = 0; i <= 70; i++) {
      Serial.println("opn");
      servo1.write(i);
      delay(10);
    }
    delay(1000);

    ///////////////////////////down servo
    for (i = 0; i <= 50; i++) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ///////PLACE SERVO

    for (i = 0; i <= 90; i++) {
      Serial.println("opn");
      servo3.write(i);
      delay(10);
    }
    delay(1000);


    ///////////////////////////////upservo
    for (i = 50; i >= 0; i--) {
      Serial.println("opn");
      servo2.write(i);
      delay(10);
    }
    delay(1000);
    ////////////////////rotate back servo
    for (i = 70; i >= 0; i--) {
      Serial.println("close");
      servo1.write(i);
      delay(10);
    }
    delay(1000);
    flag4 = 0;
  }
}
