#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>





Servo servo1;
Servo servo2;
#define MPU_ADDR 0x69 // I2C address of the MPU-6050
int led =9;
int servo_motor = 11;
int servo_secondmotor = 5;
int photo_resistor ;
int button = 10;
int secondbutton =6;
int led2 = 3;
int throttlevalue = 1500;
int potValue;
float kp =5.0;
float motorspeed;

MPU6050 mpu;


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Wire.begin();
  mpu.initialize();
   pinMode(led,OUTPUT);
   pinMode(led2,OUTPUT);
  pinMode(button,INPUT);
  pinMode(secondbutton,INPUT);
  servo1.attach(servo_motor);
  servo2.attach(servo_secondmotor);
  servo1.writeMicroseconds(1000);
  servo2.writeMicroseconds(1000);
 // Dabble.begin(9600, 0, 1);

  //mpu.setFullScaleAccelRange(ACCEL_FS_2G);
}
/*void Rc_drone(int state){
    
  switch(state){
      case 1:
      servo1.writeMicroseconds(1500);
     servo2.writeMicroseconds(1500);
      break;
  }


}
void ControlDrone(){
       // Dabble.processInput(); 
       if (GamePad.isUpPressed()){
        
        Rc_drone(1);
       
       }

*/


void loop() {
  potValue = analogRead(A0);
   
  int mapValue= map(potValue,0,1023,1000,2000);
  servo1.writeMicroseconds(mapValue);
  servo2.writeMicroseconds(mapValue);
 
  Serial.println(potValue);
  
  //servo1.writeMicroseconds(1000);
  if(digitalRead(button)==1){
     digitalWrite(led,1);
    delay(1000);
     digitalWrite(led,0);
     Serial.write(1);
     Serial.flush();
     delay(20);
     
  }

   else if(digitalRead(secondbutton)==1){
    digitalWrite(led2,1);
    delay(1000);
    digitalWrite(led2,0);
    Serial.print("led2");
     Serial.write(2);
     Serial.flush();
     delay(20);
  }
  
  photo_resistor =analogRead(A0);
 // if(photo_resistor >50){
    
    
  //}
  
  // Serial.print("value: ");
  //Serial.println(photo_resistor);
  int16_t gyroX, gyroY, gyroZ;

  
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);
  
  float pitchX = gyroX/10.0 ;  // Convert raw accelerometer values to G's
  //float accelY = ay / 16384.0;
  //float accelZ = az / 16384.0;
  motorspeed = mapValue + kp * (pitchX);
  

  servo1.writeMicroseconds(motorspeed);
  servo2.writeMicroseconds(motorspeed);

  
  /* if(accelX >0.5){
   }
  if(accelX >0.5){
    //for(int i=1000; i<2000;i+100){
     servo1.writeMicroseconds(1500);
     servo2.writeMicroseconds(1000);

    
  }
  
  
  else if( accelX < -0.5){
    //for(int i=2000; i>1000;i-100){
    servo1.writeMicroseconds(1000);
    servo2.writeMicroseconds(1500);

    
  } 
  */
  
  Serial.print("Accel X: ");
  Serial.print(pitchX);
  /*Serial.print(" g, Accel Y: ");
  Serial.print(accelY);
  Serial.print(" g, Accel Z: ");
  Serial.print(accelZ);
  Serial.println(" g");
  */
  delay(100);
}
