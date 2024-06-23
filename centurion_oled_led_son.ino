#include <Adafruit_GFX.h>  // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display
#include <DHT.h>
#include "pitches.h"

Adafruit_SSD1306 display(128, 64);  // Create display

#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font
#include <Fonts/FreeMono9pt7b.h>  // Add a custom font

#define led 10 //13

unsigned long temps = 0;
unsigned long seconde = 0;
unsigned long minute = 0;

unsigned long timeOffset = 0; //5990000; POUR TESTER ANIMATION FIN

int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6
};
int compteur =0;


void setup()  // Start of setup
{
  
  pinMode(led, OUTPUT);
  delay(100);  // This delay is needed to let the display to initialize

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C

  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  // To override this behavior (so text will run off the right side of the display - useful for
  // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  // with setTextWrap(true).

  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)

  pinMode(7, OUTPUT);

}  // End of setup

void loop(){

  temps = millis()+timeOffset;
  seconde = (int)round(temps/1000);
  minute = temps/60000;

  display.clearDisplay();

  display.setTextSize(4);  // Set text size. We are using a custom font so you should always use the text size of 0

  display.setCursor(45 , 20);  // (x,y)
  display.print(minute);
  
  display.drawRoundRect(0, 0, 128, 14,4, WHITE);
  display.drawRoundRect(0, 50, 128, 14,4, WHITE);
  display.fillRoundRect(1, 1, round(seconde%60*126/60), 12,3, WHITE);
  display.fillRoundRect(1, 51, round(minute*126/100), 12,3, WHITE);
  display.display();

  if ((3+seconde)%60==0){
  digitalWrite(led, HIGH);
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  delay(500);
  acctualiseSec ();
  delay(500);
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  delay(500);
  acctualiseSec ();
  delay(500);
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  tone(8, melody[2], 500);//(8,note,duree)
  acctualiseSec ();
  delay(500);
  acctualiseSec ();
  delay(500);
  acctualiseSec ();
  display.fillRoundRect(1, 1, 126, 12,3, WHITE);
  display.display();
  tone(8, melody[5], 1500);//(8,note,duree)
  delay(1500);
  digitalWrite(led, LOW);
  }

  if (temps > 6000000){
    digitalWrite(led, HIGH);
    while(1==1){
      display.clearDisplay();
      compteur+=1;
      if (compteur%2==0){
        display.setTextColor(BLACK, WHITE);
      }else{
        display.setTextColor(WHITE, BLACK);
      }
      display.setCursor(28 , 20);  // (x,y)
      display.print("100");
      display.drawCircle(64, 32, (compteur%70), WHITE);
      display.drawCircle(64, 32, ((compteur+15)%70), WHITE);//  Draw circle (x,y,radius,color). X and Y are the coordinates for the center point
      display.drawCircle(64, 32, ((compteur+30)%70), WHITE);
      display.drawCircle(64, 32, ((compteur+45)%70), WHITE);
      display.display();
      tone(8, melody[compteur%8], 500);//(8,note,duree)
      delay(50);
    }
  }
  delay(100);
}

void acctualiseSec (){
  temps = millis()+timeOffset;
  seconde = (int)round(temps/1000);
  display.fillRoundRect(1, 1, round(seconde%60*126/60), 12,3, WHITE);
  display.display();
}
