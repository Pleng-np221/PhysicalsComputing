#include <WiFi.h>
#include <WiFiSSLClient.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// const char* ssid = "amAUN";                // Replace with your Wi-Fi SSID
// const char* password = "aunaunaun";        // Replace with your Wi-Fi password

const char* ssid = "Noey";                // Replace with your Wi-Fi SSID
const char* password = "987654321";        // Replace with your Wi-Fi password

const char* telegramBotToken = "8121376124:AAH9M41wg_qjkMlj77Z8FjYU_KIyY_ljB-8"; // Replace with your Telegram bot token
const char* chatId = "5912496981";                // Replace with your chat ID

WiFiSSLClient wifiClient; // Create a secure WiFiSSLClient object
#define         MQ_PIN                       (0)
#define         TEMP_PIN                     (1)
#define         FLAME_PIN                    (7)
#define         BUZZER_PIN                   (8)
#define         PUMP_PIN                     (13)

#define         RL_VALUE                     (5)     //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,

#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
//cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
//normal operation

/**********************Application Related Macros**********************************/
#define         GAS_LPG                      (0)
#define         GAS_CO                       (1)
#define         GAS_SMOKE                    (2)

/*****************************Globals***********************************************/
float LPGCurve[3]  =  {2.3, 0.21, -0.47}; //two points are taken from the curve.
//with these two points, a line is formed which is "approximately equivalent"
//to the original curve.
//data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59)
float COCurve[3]  =  {2.3, 0.72, -0.34};  //two points are taken from the curve.
//with these two points, a line is formed which is "approximately equivalent"
//to the original curve.
//data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15)
float SmokeCurve[3] = {2.3, 0.53, -0.44}; //two points are taken from the curve.
//with these two points, a line is formed which is "approximately equivalent"
//to the original curve.
//data format:{ x, y, slope}; point1: (lg200, 0.53), point2: (lg10000,  -0.22)
float Ro =  10; //Ro is initialized to 10 kilo ohms

//flameSensor
int flameState = 0;

/////////////////์NOEY
byte image[8][12] = {
  // { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
  // { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
  // { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
  // { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  // { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  // { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  // { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  // { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

bool displayState = false; // สถานะปัจจุบันของการแสดงผล//

// ฟังก์ชันสำหรับอัพเดตการแสดงผลบน LED matrix
void updateDisplay() {
  // กำหนดค่าให้กับ image ตามสถานะ
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 12; x++) {
      image[y][x] = displayState ? 1 : 0; // หาก displayState เป็น true ให้แสดง 1, ถ้าเป็น false ให้แสดง 0
    }
  }

  // แสดงผล Bitmap
  matrix.renderBitmap(image, 8, 12);
}
/////////////////////

void setup()
{
  Serial.begin(115200);///NOEY
  matrix.begin();///NOEY

  pinMode(FLAME_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps

  Serial.print("Calibrating...\n");
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air
  //when you perform the calibration
  Serial.print("Calibration is done...\n");
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  
  // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
  flameState = digitalRead(FLAME_PIN);

  if (flameState == HIGH) {
    Serial.println("No flame detected");
    turnOffPump(100);
  } else {
    //put alert here
    displayState = !displayState;
    updateDisplay();
    delay(500);
      ///////
    tone(BUZZER_PIN, 1319, 10000);
    delay(500);
    Serial.println("Flame detected");
    turnOnPump(100);
    sendTelegramMessage("FIRE DETECTED!");
  }

  float LPGppm = MQGetGasPercentage(MQRead(MQ_PIN) / Ro, GAS_LPG);
  float COppm = MQGetGasPercentage(MQRead(MQ_PIN) / Ro, GAS_CO);
  float SMOKEppm = MQGetGasPercentage(MQRead(MQ_PIN) / Ro, GAS_SMOKE);

  if ((LPGppm>=1000)||(COppm>=70)||(SMOKEppm>=10)) {
    //put alert here
    displayState = !displayState;
    updateDisplay();
    delay(500);
      ///////
    tone(BUZZER_PIN, 1319, 10000);
    delay(500);
    turnOnPump(1000);
    sendTelegramMessage("HIGH GAS DETECTED!");
    String alarmMessage = "LPG: " + String(LPGppm) + " ppm  CO: " + String(COppm) + " ppm  SMOKE: " + String(SMOKEppm) + " ppm";
    sendTelegramMessage(alarmMessage);
  } else {
    turnOffPump(1000);
  }

  Serial.print("LPG: ");
  Serial.print(LPGppm);
  Serial.print(" ppm  CO: ");
  Serial.print(COppm);
  Serial.print(" ppm  SMOKE: ");
  Serial.print(SMOKEppm);
  Serial.println(" ppm");

  int sensorValue = analogRead(TEMP_PIN);
  float voltage = sensorValue * (5.0 / 1023.0); // แปลงค่า Analog เป็น Voltage
  float temperatureC = (voltage * 100 - 32) * 5 / 9; // แปลง Voltage เป็น อุณหภูมิ (Celsius)
  
  if (temperatureC >= 70) {
    //put alert here
    displayState = !displayState;
    updateDisplay();
    delay(500);
      ///////
    tone(BUZZER_PIN, 1319, 10000);
    delay(500);
    turnOnPump(1000);
    sendTelegramMessage("HIGH TEMPERATURE DETECTED!");
    String alarmMessage = "Temperature: " + String(temperatureC);
    sendTelegramMessage(alarmMessage);
  } else {
    turnOffPump(1000);
  }

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  delay(3000);
  
}

void turnOnPump(float delayTime)
{
  Serial.println("Turning pump ON");
  digitalWrite(PUMP_PIN, HIGH);
  delay(delayTime);
}
void turnOffPump(float delayTime)
{
  digitalWrite(PUMP_PIN, LOW);
  delay(delayTime);
}

float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE * (1023 - raw_adc) / raw_adc));
}

float MQCalibration(int mq_pin)
{
  int i;
  float val = 0;

  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {      //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val / CALIBARAION_SAMPLE_TIMES;                 //calculate the average value

  val = val / RO_CLEAN_AIR_FACTOR;                      //divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet

  return val;
}

float MQRead(int mq_pin)
{
  int i;
  float rs = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs / READ_SAMPLE_TIMES;

  return rs;
}

int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
    return MQGetPercentage(rs_ro_ratio, LPGCurve);
  } else if ( gas_id == GAS_CO ) {
    return MQGetPercentage(rs_ro_ratio, COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
    return MQGetPercentage(rs_ro_ratio, SmokeCurve);
  }

  return 0;
}

int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10, ( ((log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));
}
void sendTelegramMessage(const String& message) {
    // Format the Telegram API URL
    String url = "/bot" + String(telegramBotToken) + "/sendMessage?chat_id=" + String(chatId) + "&text=" + message;

    // Connect to Telegram server
    if (wifiClient.connect("api.telegram.org", 443)) {
        // Send the GET request
        wifiClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                         "Host: api.telegram.org\r\n" +
                         "Connection: close\r\n\r\n");

        // Wait for response
        while (wifiClient.connected() || wifiClient.available()) {
            if (wifiClient.available()) {
                String response = wifiClient.readStringUntil('\n');
                Serial.println(response);
            }
        }

        wifiClient.stop();
    } else {
        Serial.println("Connection failed");
    }
}