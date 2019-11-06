//
//  MPU6050 on ESP8266

#include <Wire.h>

#define MPU6050_ADDR 0x68
#define MPU6050_AX  0x3B
#define MPU6050_AY  0x3D
#define MPU6050_AZ  0x3F
#define MPU6050_TP  0x41    //  data not used
#define MPU6050_GX  0x43
#define MPU6050_GY  0x45
#define MPU6050_GZ  0x47

short int AccX, AccY, AccZ;
short int Temp;
short int GyroX, GyroY, GyroZ;

void setup() {
  //  serial for debugging
  Serial.begin(115200);
  Serial.println("*** started");
  //  i2c as a master
  Wire.begin();
  //  wake it up
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  //  send start address
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(MPU6050_AX);
  Wire.endTransmission();  
  //  request 14bytes (int16 x 7)
  Wire.requestFrom(MPU6050_ADDR, 14);
  //  get 14bytes
  AccX = Wire.read() << 8;  AccX |= Wire.read();
  AccY = Wire.read() << 8;  AccY |= Wire.read();
  AccZ = Wire.read() << 8;  AccZ |= Wire.read();
  Temp = Wire.read() << 8;  Temp |= Wire.read();  //  (Temp-12421)/340.0 [degC]
  GyroX = Wire.read() << 8; GyroX |= Wire.read();
  GyroY = Wire.read() << 8; GyroY |= Wire.read();
  GyroZ = Wire.read() << 8; GyroZ |= Wire.read();
  //  debug monitor
   AccX=int(AccX*0.001);
 AccY=int(AccY*0.001);
 AccZ=int(AccZ*0.001);
  Serial.print("  "); Serial.print(AccX);
  Serial.print("  "); Serial.print(AccY);
  Serial.print("  "); Serial.print(AccZ);
  Serial.println("");


  float acc = AccX*AccX + AccY*AccY + AccZ*AccZ;
   Serial.println(acc);
   if(abs(acc)>700){
      digitalWrite(13,HIGH);
      delay(500);
       digitalWrite(10,HIGH);
       
    }else{
            digitalWrite(13,LOW);
       digitalWrite(10,LOW);
      }
    
   
  delay(20);
}
