//***********************************//
// ALEX LEE. EEYAL5                  //
// UNI OF NOTTINGHAM EEE             //
// 20459944                          //
//***********************************//

//PROGRAM WHICH SENDS MESSAGES FROM THE ESP32 TO R-PI WHICH IS THEN DISPLAYED ONTO THE NODE-RED DASHBOARD
//USE THE MPU-6050 GYRO-ANGLE Z VALUE

//Add sensors or component libraries here
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

const int led = 4;

// Add MQTT Broker IP address 
const char* mqtt_server = "192.168.2.1";
const char* ssid = "tonyTable";
const char* password = "brazillostlol";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
float angle;

// Sets up the script
void setup() 
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  pinMode(led, OUTPUT);
}

// Sets up the WiFi connection
void setup_wifi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//A function which acts on the data which is received from the MQTT server and Node-RED
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp32/output") 
  {
    Serial.print("Changing output to ");
    if(messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(led, HIGH);
    }
    else if(messageTemp == "off") 
    {
      Serial.println("off");
      digitalWrite(led, LOW);
    }
  }
}

void reconnect() // Loop until its reconnected to the MQTT server
{
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) 
    {
      Serial.println("connected");
      
       // Add your subscribe topics here to subscribe to the topics
      client.subscribe("esp32/Angle");
      client.subscribe("esp32/output");
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() 
{
  mpu6050.update();
  
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) 
  {
    lastMsg = now;
    
    angle = mpu6050.getAngleZ();
    
    // Convert the value to a char array
    char tempString[8];
    dtostrf(angle, 1, 2, tempString);
    Serial.print("Angle: ");
    Serial.println(tempString);
    client.publish("esp32/Angle", tempString);
  }
}
