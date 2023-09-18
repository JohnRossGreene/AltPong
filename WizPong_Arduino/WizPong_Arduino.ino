// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.
#include "Keyboard.h"
#include <Keyboard.h>
#include <Wire.h>



//Setting up LEDs on board
// #define LED_LB 2
// #define LED_LT 3
// #define LED_RB 4
// #define LED_RT 5

// Setting up microphone
const int microphonePin = A0;


bool pressed_W = false;
bool pressed_S = false;
bool pressed_A = false;
bool pressed_D = false;
//Floating direction var
int dir = -1;

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  //Light Output
  Serial.begin(9600);
  // pinMode(LED_LB, OUTPUT);
  // pinMode(LED_LT, OUTPUT);
  // pinMode(LED_RB, OUTPUT);
  // pinMode(LED_RT, OUTPUT);
  // digitalWrite(LED_LB, LOW);
  // digitalWrite(LED_LT, LOW);
  // digitalWrite(LED_RB, LOW);
  // digitalWrite(LED_RT, LOW);

  //LCD INITIALIZATION
  // lcd.init();
  // lcd.backlight();  

  //Starting i2c to acccel
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Keyboard.begin();
}
void loop() {
  Keyboard.press("S");
  delay(100);
  Keyboard.releaseAll();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();

  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 100; ++i) {
    int val = analogRead(microphonePin);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;

  Serial.println(delta);
  
  if (accelerometer_y > 0 && accelerometer_z < -3500){
    // digitalWrite(LED_LB, LOW);
    // digitalWrite(LED_RB, LOW);
    // digitalWrite(LED_LT, HIGH);
    // digitalWrite(LED_RT, HIGH);
    dir = 0;
  }

  else if (accelerometer_y < -10000 && accelerometer_z > 2500){
    // digitalWrite(LED_LB, HIGH);
    // digitalWrite(LED_RB, HIGH);
    // digitalWrite(LED_LT, LOW);
    // digitalWrite(LED_RT, LOW);
    dir = 1;
  }
  else if (accelerometer_y < -8500 && accelerometer_z < -6000){
    // digitalWrite(LED_LB, HIGH);
    // digitalWrite(LED_RB, LOW);
    // digitalWrite(LED_LT, HIGH);
    // digitalWrite(LED_RT, LOW);
    dir = 2;
  }
  else if (accelerometer_y > -3000 && accelerometer_z > 7000){
    // digitalWrite(LED_LB, LOW);
    // digitalWrite(LED_RB, HIGH);
    // digitalWrite(LED_LT, LOW);
    // digitalWrite(LED_RT, HIGH);
    dir = 3;
  }
  else{
      dir=4;
    }
  if (dir == 0)
    {
    // lcd.setCursor(1, 0);
    // lcd.print("DOWN");
    // lcd.setCursor(1,3);
    // lcd.print(delta);
    if(pressed_S == false){
      Keyboard.releaseAll();
      pressed_S = true;
      pressed_W = false;
      pressed_A = false;
      pressed_D = false;
    }
    Serial.println("DOWN");
    Keyboard.press('S');
    delay(300);
    Keyboard.releaseAll();
    }
  if (dir == 1)
    {
    // lcd.setCursor(1, 0);
    // lcd.print("UP");
    // lcd.setCursor(1,3);
    if(pressed_W == false){
      Keyboard.releaseAll();
      pressed_S = false;
      pressed_W = true;
      pressed_A = false;
      pressed_D = false;
    }
      Serial.println("UP");
      Keyboard.press('W');
      delay(300);
      Keyboard.releaseAll();

    }
  if (dir == 2){
    // lcd.setCursor(1, 0);
    // lcd.print("LEFT");
    // lcd.setCursor(1,3);
    // lcd.print(delta);
    if(pressed_A == false){
      Keyboard.releaseAll();
      pressed_S = false;
      pressed_W = false;
      pressed_A = true;
      pressed_D = false;
    }
      Serial.println("LEFT");
      Keyboard.press('A');
      delay(300);
      Keyboard.releaseAll();

  }
  if (dir == 3){
    // lcd.setCursor(1, 0);
    // lcd.print("RIGHT");
    // lcd.setCursor(1,3);
    // lcd.print(delta);
    if(pressed_D == false){
      Keyboard.releaseAll();
      pressed_S = false;
      pressed_W = false;
      pressed_A = false;
      pressed_D = true;
    }
    Serial.println("RIGHT");
      Keyboard.press('D');
      delay(300);
      Keyboard.releaseAll();
  }
  if (dir == 4){
    Serial.println("neutral");
    Keyboard.releaseAll();
    pressed_S = false;
    pressed_W = false;
    pressed_A = false;
    pressed_D = false;

  }
  if (delta > 20)
  {
    Keyboard.press(' ');
    delay(50);
    Keyboard.release(' ');
  }

  // // delay
  // Serial.println(delta);
  // lcd.clear();
}