//***********************************//
// ALEX LEE. EEYAL5                  //
// UNI OF NOTTINGHAM EEE             //
// 20459944                          //
//***********************************//

#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04  // 4 in hexadecimal

//PINS FOR EACH IR SENSOR
#define WHITE 13 
#define PURPLE 35
#define GREEN 14
#define BLUE 34
#define PINK 27
#define YELLOW 33

void setup() 
{
  Wire.begin(); // join i2c bus (address optional for the master) - on the Arduino NANO the default I2C pins are A4 (SDA), A5 (SCL)        
  Serial.begin(9600);
  pinMode(YELLOW,INPUT);
  pinMode(PURPLE,INPUT);
  pinMode(BLUE,INPUT);
  pinMode(PINK,INPUT);
  pinMode(GREEN,INPUT);
  pinMode(WHITE,INPUT);
}

//A FUNCTION CREATED TO OBTAIN ALL SENSOR VALUES
void GetIRdata()
{
  Serial.print(analogRead(GREEN));
  Serial.print(",");
  Serial.print(analogRead(BLUE));
  Serial.print(",");
  Serial.print(analogRead(PURPLE));    
  Serial.print(",");
  Serial.print(analogRead(YELLOW));    
  Serial.print(",");
  Serial.print(analogRead(PINK));
  Serial.print(",");
  Serial.print(analogRead(WHITE));
  Serial.println();
  delay(11);
}

//A FUNCTION CREATED TO MOVE THE CAR THAN HAVING TO KEEP COPYING PASTING THIS CODE.
//ALSO SENDS DATA TO ARDUINO TO TURN THE MOTORS ON OR OFF AND SET THE SERVO ANGLE
void moveCar(int leftMotor_speed, int rightMotor_speed, int servoAngle) 
{
  Wire.beginTransmission(I2C_SLAVE_ADDR); 
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF)); 
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  Wire.endTransmission();
  delay(100);
}

void loop() //WHERE THE CODE BEGINS
{
  GetIRdata(); // CALLS THE FUNCTION TO GET ALL THE IR SENSORS DATA FROM 0 TO 4095

  if(analogRead(PURPLE) < 3500 || analogRead(YELLOW) < 3500)
  {
    moveCar(90,90,90); //MOVE FORWARDS
    delay(5);
  }
  else if(analogRead(PURPLE) > 3500 && analogRead(YELLOW) > 3500)
  {
   moveCar(0,0,90); //STOP CAR
   delay(2);
    if(analogRead(PINK) < 3500)
    {
      moveCar(110,110,115); //TURN RIGHT SLIGHTLY
      delay(3);
    }
    else if(analogRead(BLUE) < 3500)
    {
      moveCar(110,110,75); //TURN LEFT SLIGHTLY
      delay(3);
    }
    else if(analogRead(YELLOW) > 3500 && analogRead(PINK) > 3500 && analogRead(BLUE) > 3500)
    {
      moveCar(-95,-95,90); //REVERSE CAR
      delay(5);
    }
  }
}
