#include <Wire.h>

//Data Output Rate: 75Hz
//Normal Measurement mode
//Gain: 1370
// 01111100 : ConfigRegA
// 00000000 : ConfigRegB
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
  int x_MSB = 0;
  int x_LSB = 0;
  int y_MSB = 0;
  int y_LSB = 0;
  int z_MSB = 0;
  int z_LSB = 0;
  Wire.beginTransmission(hmc5883l);
  Wire.write(dataX_MSB);

  Wire.requestFrom(hmc5883l,6);
  Serial.print("Number of available bits: ");
  int available = Wire.available();
  if(6<= available){
    Serial.println(available);
    x_MSB = Wire.read() << 8;
    x_LSB = Wire.read();
    y_MSB = Wire.read() << 8;
    y_LSB = Wire.read();
    z_MSB = Wire.read() << 8;
    z_LSB = Wire.read();
  }
  Serial.print("x: ");
  Serial.println(x_MSB | x_LSB);
  Serial.print("y: ");
  Serial.println(y_MSB | y_LSB);
  Serial.print("z: ");
  Serial.println(z_MSB | z_LSB);
  Wire.endTransmission(); 

  delay(250);



}
void loop() {
  // put your main code here, to run repeatedly:
  readData();
}
