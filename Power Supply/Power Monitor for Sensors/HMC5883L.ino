#include <Wire.h>

//Data Output Rate: 75Hz
//Normal Measurement mode
//Gain: 1370 = +/- 0.88 Ga
// 01111100 : ConfigRegA
// 00000000 : ConfigRegB

//Value of scale found here: bildr.org/2012/02/hmc5883l_arduino/
float scale = 0.73;
int configRegA = 0x00;
int configRegB = 0x01;
int modeReg = 0x2;
int hmc5883l = 0x1E;
int dataX_MSB = 0x03;
int dataX_LSB = 0x04;
int dataZ_MSB = 0x05;
int dataZ_LSB = 0x06;
int dataY_MSB = 0x07;
int dataY_LSB = 0x08;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  setConfiguration();
}

void setConfiguration(){
  Wire.beginTransmission(hmc5883l);
  Wire.write(configRegA);
  Wire.write(0b01111100);
  Wire.write(configRegB);
  Wire.write(0x00);
  Wire.write(modeReg);
  Wire.write(0x00);
  Wire.endTransmission();
}

  
void readData(){
  int16_t x_MSB = 0;
  int16_t x_LSB = 0;
  int16_t y_MSB = 0;
  int16_t y_LSB = 0;
  int16_t z_MSB = 0;
  int16_t z_LSB = 0;
  Wire.beginTransmission(hmc5883l);
  Wire.write(dataX_MSB);

  Wire.requestFrom(hmc5883l,6);
  //Serial.print("Number of available bits: ");
  int available = Wire.available();
  if(6<= available){
    x_MSB = Wire.read() << 8;
    x_LSB = Wire.read();
    y_MSB = Wire.read() << 8;
    y_LSB = Wire.read();
    z_MSB = Wire.read() << 8;
    z_LSB = Wire.read();
  }
  float x_raw = (x_MSB | x_LSB);
  float y_raw = (y_MSB | y_LSB);
  float z_raw = (z_MSB | z_LSB);
  Serial.print("x: ");
  Serial.println(x_raw);
  Serial.print("y: ");
  Serial.println(y_raw);
  Serial.print("z: ");
  Serial.println(z_raw);

  float heading = atan2(y_raw, x_raw);

  if(heading < 0){
    heading += 2 * PI;
  }
  else if(heading > 2*PI){
    heading -= 2*PI;
  }
  float headingDegrees = heading * 180/M_PI;
  Serial.print("heading: ");
  Serial.println(headingDegrees);
  Wire.endTransmission(); 

  delay(200);



}
void loop() {
  // put your main code here, to run repeatedly:
  readData();
}
