#include <stdbool.h>
// Pin connections to board



// Light
const int light = 12;
// Fan Off
const int foff = 11;
// Fan Low
const int low = 10;
// Fan Medium
const int med = 9;
// Fan High
const int high = 8;

// Fan 4 (bedroom)
const int f4 = 7;
// Fan 3 (office)
const int f3 = 6;
// Fan 2 (dinig room)
const int f2 = 5;
// Fan 1 (living room)
const int f1 = 4;

// Stores serial input one character at a time
byte input = 0;
byte command = 0;

// Fan selector
int fan = 0;

// Serial input for which feeder is selected (in hexidecimal)
char* controlchar = "0";

void setup() {
    // Baud rate
    Serial.begin(9600);
    // Set outputs to be used for Fan and light controls
    pinMode(light, OUTPUT);
    digitalWrite(light, HIGH);
    pinMode(med, OUTPUT);
    digitalWrite(med, HIGH);
    pinMode(high, OUTPUT);
    digitalWrite(high, HIGH);
    pinMode(low, OUTPUT);
    digitalWrite(low, HIGH);
    pinMode(foff, OUTPUT);
    digitalWrite(foff, HIGH);
    
    // Fan Selectors
    pinMode(f4, OUTPUT);
    digitalWrite(f4, HIGH);
    pinMode(f3, OUTPUT);
    digitalWrite(f3, HIGH);
    pinMode(f2, OUTPUT);
    digitalWrite(f2, HIGH);
    pinMode(f1, OUTPUT);
    digitalWrite(f1, HIGH);
    delay(300);      
          
    // Make sure Fan is off
    digitalWrite(low, LOW);
    digitalWrite(foff, LOW);
    delay(300);
    digitalWrite(foff, HIGH);
    digitalWrite(low, HIGH);
    delay(300);
          
    Serial.print("Board Initialized and Reset.\n");
    
}

int val = 0;

// Main Program
void loop() {
  // Check to see if Arduino serial port is available
  if (Serial.available() > 0) {
    // Get command switch
    do{
      command = Serial.read();
      delay(10);
      command = command - '0';
      Serial.print(command);
      Serial.print("\n");
      // Set fan
      switch(command){
        case 1:
          fan = f1;
          break;
        case 2:
          fan = f2;
          break;
        case 3:
          fan = f3;
          break;
        case 4:
          fan = f4;
          break;
        default:
          fan = 0;
          break;
      }
      // Reset Fans
      digitalWrite(f4, HIGH);
      digitalWrite(f3, HIGH);
      digitalWrite(f2, HIGH);
      digitalWrite(f1, HIGH);
      delay(300);  
      
      
      Serial.print("Fan ");
      Serial.print(fan);
      Serial.print(" selected...\n");
      digitalWrite(fan, LOW);
      delay(300);
      
      input = Serial.read();
      
      if(input == 's'){
          Serial.print("Toggle light...\n");
          digitalWrite(light, LOW);
          delay(300);
          digitalWrite(light, HIGH);
          delay(300);
        }
      if(input == 'o'){
          Serial.print("Toggle off...\n");
          digitalWrite(low, LOW);
          digitalWrite(foff, LOW);
          delay(300);
          digitalWrite(foff, HIGH);
          digitalWrite(low, HIGH);
          delay(300);
        }
        if(input == 'l'){
          Serial.print("Toggle low...\n");
          digitalWrite(low, LOW);
          delay(300);
          digitalWrite(low, HIGH);
          delay(300);
        }
        if(input == 'm'){
          Serial.print("Toggle med...\n");
          digitalWrite(med, LOW);
          delay(300);
          digitalWrite(med, HIGH);
          delay(300);
        }
        if(input == 'h'){
          Serial.print("Toggle high...\n");
          digitalWrite(high, LOW);
          delay(300);
          digitalWrite(high, HIGH);
          delay(300);
        }
    }while(!EOF);
}
}
