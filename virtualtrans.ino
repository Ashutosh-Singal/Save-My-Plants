#include <VirtualWire.h>
const int transmit_pin = 12;
const int ms_pin1 = A0;
const int ms_pin2 = A1;
const int trigPin = 7;
const int echoPin = 6;
long duration;

struct package
{
  int moisture[2] ;
  int moisture_percentage[2] ;
  int distance;
};
typedef struct package Package;
Package data;

void setup()
{   Serial.begin(9600);
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(500);       // Bits per sec
    pinMode(ms_pin1, INPUT);
    pinMode(ms_pin2, INPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}
void loop()
{
  MoistureReadSensor(ms_pin1,0);
  MoistureReadSensor(ms_pin2,1);
  UltrasonicReadSensor();
  vw_send((uint8_t *)&data, sizeof(data));
  vw_wait_tx(); // Wait until the whole message is gone
  delay(2000);  
}
void MoistureReadSensor(int val,int ind)
{
 data.moisture[ind] = analogRead(val);
 data.moisture_percentage[ind] = ( 100 - ( (data.moisture[ind]/1023.00) * 100 ) );
 Serial.print("Moisture value for sensor ");
 Serial.print(ind+1);
 Serial.print(" : ");
 Serial.println(data.moisture[ind]);
 Serial.print("Moisture percentage value for sensor ");
 Serial.print(ind+1);
 Serial.print(" : ");
 Serial.println(data.moisture_percentage[ind]);
}
void UltrasonicReadSensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  data.distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.print(data.distance);
  Serial.println(" cm");
  
}
