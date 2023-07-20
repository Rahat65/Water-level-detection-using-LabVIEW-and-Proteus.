
#include <LiquidCrystal.h>
//initialise the library with the numbers of the interface pins 
const int echo_ultrasonic = 12;
const int trigger_ultrasonic = 13;
int resval = 0;  // holds the value
int respin = A3; // sensor pin used
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  
 
void setup() { 
 Serial.begin(9600);
  pinMode(trigger_ultrasonic, OUTPUT); //  pin 13 as output in ultrasonic
  pinMode(echo_ultrasonic, INPUT); //  pin 12 as input in ultrasonic
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); 
  
  // Print a message to the LCD. 
  lcd.print("  WATER LEVEL : "); 
  lcd.setCursor(0,1);
  lcd.print("Here ");
  lcd.print("Tank size-500cm");
  delay(15);
} 
  
void loop() { 
  // set the cursor to column 0, line 1 
   lcd.setCursor(0, 1); 
   long time_scale;//Duration
   long measurement;//Tank measurement in centimeter

  //lcd.clear(); 
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
   
  if (resval<=100){ lcd.println("     Empty    "); } 
  else if (resval>100 && resval<=300){ lcd.println("       Low      "); }
  else if (resval>300 && resval<=330){ lcd.println("     Medium     "); } 
  else if (resval>330){ lcd.println("      High      "); }
  digitalWrite(trigger_ultrasonic, LOW);
  delayMicroseconds(5);

  digitalWrite(trigger_ultrasonic, HIGH);
  delayMicroseconds(15);

  digitalWrite(trigger_ultrasonic, LOW);
 time_scale = pulseIn(echo_ultrasonic, HIGH); //total time_scale
 measurement = microsecondsToCentimeters(time_scale); 

  Serial.print(resval);
  Serial.println();
  delay(1000); 
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
