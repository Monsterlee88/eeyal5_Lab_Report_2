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

void loop() //WHERE THE CODE BEGINS
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
