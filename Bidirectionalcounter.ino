#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

#define MAX_LIMIT 10 //Maximum number of persons allowed in the hall or room

#define irPin1 8 //IR Sensor 1
#define irPin2 7 //IR sensor 2
#define led 9 //led pin
#define relay 3//relay module 

int count=0;
boolean state1 = true;
boolean state2 = false;
int i=1;
int j=1;

//Function to Display the count on LCD

void displayCount(int num){
char str[6]; //To hold count to be displayed
int i, rem, l = 0, n;

/*Convert integer (count) to string for displaying on LCD*/
n = num;
while (n != 0){
   l++;
   n /= 10;
}
for (i = 0; i < l; i++){
   rem = num % 10;
   num = num / 10;
   str[l-(i+1)] = rem + '0';
}
str[l] = '\0'; //Put NULL character to end the string

/*If count in room or hall is less than maximum limit of the hall or room,
then display the message on LCD to print Number of persons in room */

if(count<=0)
{
    lcd.clear();
    digitalWrite(relay, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("No Visitors    ");
}
if(count >0 && count < MAX_LIMIT){
   digitalWrite(relay, LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("No. of Persons");
   lcd.setCursor(0,1);
   lcd.print("in Room: ");
}

/*If number of persons in room is equal to MAX_LIMIT of the room,
then display the message as Room Full */
if(count==MAX_LIMIT){
   digitalWrite(relay, LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Room Full ");
   lcd.setCursor(0,1);
   lcd.print("No.of Persons:");
}

/*If number of persons in room is greater than MAX_LIMIT,
then display the message as Over Crowded Room and also turn on LED*/
if(count>MAX_LIMIT){
   digitalWrite(relay, LOW);
   digitalWrite(led, HIGH); //LED made ON
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Over CrowdedRoom");
   lcd.setCursor(0,1);
   lcd.print("No.of Persons:");
}
else{ //If count is less than or equal to MAX_LIMIT, the turnoff LED
   digitalWrite(led, LOW);
}

//Display the count on LCD
lcd.print(str);
}

//Setup function for initial setup
void setup(){
//IR sensor pins are made as input pins
   pinMode(irPin1, INPUT);
   pinMode(irPin2, INPUT);
   pinMode(relay, OUTPUT);
   digitalWrite(relay, HIGH);
   //LED pin is made as output pin
   pinMode(led, OUTPUT);

   // LED made ON for small duration to indicate start of the counting
   digitalWrite(led,HIGH);
   delay(1000);
   digitalWrite(led,LOW);
   delay(50);

   //Initial Message on LCD
   lcd.begin(16,2);
   lcd.print("Visitor Counter");
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Suriya_Sudharsan");
   lcd.setCursor(0,1);
   lcd.print("II-CSE-C");
   delay(2000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("NO VISITORS");
}

//Loop function
void loop(){
    if (digitalRead(irPin1)==LOW && i==1 && state1==true && state2==false){
     i++;
     delay(500);
     state1 = false;
     state2 = true;   
  }

   if (digitalRead(irPin2)==LOW && i==2 && state1==false && state2==true){
     i = 1 ;
     count=count+1;
     delay(500);
     displayCount(count);
     state1 = true;
     state2 = false;
  }
  if (digitalRead(irPin2)==LOW && j==1 && state1==true && state2==false ){
     j = 2 ;
     delay(500);
     state1 = false;
     state2 = true;
  }

  if (digitalRead(irPin1)==LOW && j==2 && state1==false && state2==true  ){
     count=count-1;
     delay(500);
     displayCount(count);
     j = 1;
     state1 = true;
     state2 = false;
  }  

}
