#define BLINKER_WIFI
#include <Blinker.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <math.h>
#include <Ticker.h>

//以下信息请自行完善
#define auth ""       //blinker密钥
#define ssid ""       //WIFI名称
#define pswd ""       //WIFI密码
#define buttonName "" //按钮名称
#define irCode 0x0000 //开关机的红外编码

int power = 4;
int irPin = 14;

bool powerLightFlag = true;
bool flag = true;
double ledCount = 0;

BlinkerButton Button1(buttonName);
IRrecv irrecv(irPin);
decode_results results;
Ticker flipper;

void normalShutdown()
{
  digitalWrite(power, LOW);
  delay(500);
  digitalWrite(power, HIGH);
}

void forceShutdown()
{
  digitalWrite(power, LOW);
  delay(8000);
  digitalWrite(power, HIGH);
}

void changeButton()
{
  Button1.print("on");
}

void button1_callback(const String &state)
{
  BLINKER_LOG("get button state: ", state);
  changeButton();
  normalShutdown();
}

void dataRead(const String &data)
{
  BLINKER_LOG("Blinker readString: ", data);
}
void setup()
{
  pinMode(power, OUTPUT);
  digitalWrite(power, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);

  Serial.print("\n connecting to the wifi ... \n ");
  wifiMulti.addAP(ssid, pswd);
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }
  Serial.print("\n");

  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  Blinker.attachData(dataRead);
  Button1.attach(button1_callback);

  irrecv.enableIRIn();
  flipper.attach(0.01, changeLed);
}

void loop()
{
  Blinker.run();
  if (irrecv.decode(&results))
  {
    if (results.value == irCode)
    {
      normalShutdown();
    }
    irrecv.resume();
  }
}

void changeLed()
{
  analogWrite(2, 256 - (abs(int(sin(ledCount) * 1024))) / 3);
  ledCount += 0.01;
}
