#include <RTCDue.h>

#include <Adafruit_GFX.h>
#include <ArducamSSD1306.h>

// LED pin defs
#define red1 (30)
#define red2 (31)
#define green1 (34)
#define green2 (35)
#define blue1 (32)
#define blue2 (33)

// LCD defs
#define OLED_RESET  16
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

ArducamSSD1306 display(OLED_RESET); // FOR I2C

const int pump_level = A8; // analog sensor 
const int hygrometer = A9; // analog sensor 
// set initial upper and bounds  for water level
// init as dry plant bc thats what we got
int isWet = 47;
int isDry = 5;
int h_value, w_value;
int current_day = 1;
int days = 10;
char h_char[20];
char w_char[20];

char read_gui;

RTCDue rtc(XTAL);
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Set 3v3 on 52 and 53
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);

  // Set LED pins
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(blue1,OUTPUT);
  pinMode(blue2,OUTPUT);

  // SSD1306 Init
  display.begin();  // Switch OLED
  display.setTextSize(1);
  // Text color is dependent on which line the text is on
  display.setTextColor(LIT);
  display.clearDisplay();
  display.display();

 // Motor init
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);

  //Initalize RTC
  rtc.begin();
  rtc.setDate(1, 1, 2000);
  rtc.setHours(00);
  rtc.setMinutes(00);
  rtc.setSeconds(00);
}

void loop() {

  // Update values from sensors
  h_value = analogRead(hygrometer);
  h_value = constrain(h_value, 0, 1023);
  h_value = map(h_value, 0, 1023, 100, 0);

  w_value = analogRead(pump_level);
  w_value = constrain(w_value, 0, 1023);
  w_value = map(w_value, 0, 1023, 100, 0);

/*
  Serial.print("Soil humidity: ");
  Serial.print(h_value);
  Serial.println();
  Serial.print("Container: ");
  Serial.print(w_value);
  Serial.println();
*/
  
// Update LEDS
  if (h_value>=isWet)
  {
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    strcpy(h_char,"wet");
  }
  else if (h_value<=isDry)
  {
    digitalWrite(green2, LOW);
    digitalWrite(red2, HIGH);
    strcpy(h_char,"dry");
  }
  else
  {
    digitalWrite(green2, HIGH);
    digitalWrite(red2, HIGH);
    strcpy(h_char,"moist");
  }

    if (w_value>=40)
  {
    digitalWrite(red1, LOW);
    digitalWrite(green1, HIGH);
    strcpy(w_char,"full");
  }
  else if (w_value<=20)
  {
    digitalWrite(green1, LOW);
    digitalWrite(red1, HIGH);
    strcpy(w_char,"empty");
  }
  else
  {
    digitalWrite(green1, HIGH);
    digitalWrite(red1, HIGH);
    strcpy(w_char,"half");
  }

  // Update display with new values
  display.clearDisplay();
  display.setCursor(0,20);
  display.print("Soil is ");
  display.println(h_char);
  display.print("Container ");
  display.print("is ");
  display.println(w_char);
  display.print(current_day);
  display.print(" days since watered ");
 
  display.display();

  current_day = rtc.getDay() - 1;
  if ((days <= (current_day)) && strcmp("dry",h_char) == 0) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.display();
    digitalWrite(23,HIGH);
    delay(3000);
    digitalWrite(23,LOW);
    rtc.setDay(1);
    rtc.setHours(00);
    rtc.setMinutes(00);
    rtc.setSeconds(00);
    display.setCursor(21,0);
    display.println("Watered");
    display.display();
  }
  delay(2000);
  
}

void serialEvent()
{
// GUI CODE
  while (Serial.available()>0){
    read_gui = Serial.read();
    switch(read_gui){
      case '0':       // Desert
        days = 14;
        isWet = 47;
        isDry = 5;
        break;
      case '1':       // Midwest
        days = 10;
        isWet = 57; //TODO: EDIT VALUES
        isDry = 20;
        break;
      case '2':       // London
        days = 5;
        isWet = 67;
        isDry = 30;
        break;
      case '3':     // check water amnt
      if (Serial.availableForWrite() > 0)
      {
        Serial.write(current_day);
        break;
      }
      case '4':
        days = 5;
        rtc.setDay(5);
        rtc.setMonth(1);
        rtc.setYear(2000);
        rtc.setHours(23);
        rtc.setMinutes(59);
        rtc.setSeconds(55);
    }
  }
 }
