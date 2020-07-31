#include <VirtualWire.h>

const int receive_pin = 11;
const int led_pin = 7;
char moistureChar[10];
char moist_percentChar[10];
const int p_pin1=10;
const int p_pin2=9;
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
    vw_set_rx_pin(receive_pin);
    vw_setup(500);   // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    pinMode(led_pin, OUTPUT);
    pinMode(p_pin1, OUTPUT);
    pinMode(p_pin2, OUTPUT);
}
void loop()
{   uint8_t buf[sizeof(data)];
    uint8_t buflen = sizeof(data);
  
    vw_get_message(buf, &buflen);
    memcpy(&data,&buf,buflen);
    Pump();
    for(int i=0;i<2;i++){
      Serial.print("Moisture value for sensor ");
      Serial.print(i+1);
      Serial.print(" : ");
      Serial.println(data.moisture[i]);
      Serial.print("Moisture percentage value for sensor ");
      Serial.print(i+1);
      Serial.print(" : ");
      Serial.println(data.moisture_percentage[i]);
     }
      Serial.print("Distance : ");
      Serial.println(data.distance);
     if(data.distance<10){
       digitalWrite(led_pin, HIGH);
     }
     else{
       digitalWrite(led_pin, LOW);
     }
    delay(3000);
  }
  void Pump(){
  if(data.moisture_percentage[0]<5){
    digitalWrite(p_pin1, HIGH);
  }else{
    digitalWrite(p_pin1, LOW);
  }
   if(data.moisture_percentage[1]<5){
    digitalWrite(p_pin2, HIGH);
  }else{
    digitalWrite(p_pin2, LOW);
  }
}
