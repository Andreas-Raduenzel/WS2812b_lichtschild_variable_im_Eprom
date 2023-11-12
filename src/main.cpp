 // NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 5 // Popular NeoPixel ring size
#define PIXEL_PIN    0  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 5  // Number of NeoPixels
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels

int x;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)


pinMode(1,INPUT);// Pin 1 als Eingang
digitalWrite(1,HIGH);//aktiviert PULL-Up-Widerstand
strip.show();  // Initialize all pixels to 'off'

}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {
    if (digitalRead(1) == LOW) {
                  break;}// Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2.  ..
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    if (digitalRead(1) == LOW) {
                  break;}
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {
     if (digitalRead(1) == LOW) {
                  break;}// Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void  loop() {
x=EEPROM.get(0,x);              
              /***********************************
              ***************WEISS****************
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x<=1) {
              //pixels.clear(); // Set all pixel colors to 'off'
            
              // The first NeoPixel in a strand is #0, second is 1, all the way up
              // to the count of pixels minus one.
              for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
            
                // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
                // Here we're using a moderately bright white color:
                pixels.setPixelColor(i, pixels.Color(127, 127, 127));//weiss
            
                pixels.show();   // Send the updated pixel colors to the hardware.
                delay(DELAYVAL); // Pause before next pass through loop
                
              }
              if (digitalRead(1) == LOW) {
                
                  
                  x=2;
                    EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              delay(1);
              /***********************************
              ***************ROT******************
              ***********************************/
              while (digitalRead(1) == HIGH&&x==2) {
              //pixels.clear(); // Set all pixel colors to 'off'
            
              // The first NeoPixel in a strand is #0, second is 1, all the way up
              // to the count of pixels minus one.
              for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
            
                // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
                // Here we're using a moderately bright red color:
                pixels.setPixelColor(i, pixels.Color(125, 0, 0));//rot
            
                pixels.show();   // Send the updated pixel colors to the hardware.
                delay(DELAYVAL); // Pause before next pass through loop
                
              }
              if (digitalRead(1) == LOW) {
                  x=3;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ***************GRUEN****************
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH && x==3) {
              //pixels.clear(); // Set all pixel colors to 'off'
            
              // The first NeoPixel in a strand is #0, second is 1, all the way up
              // to the count of pixels minus one.
              for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
            
                // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
                // Here we're using a moderately bright green color:
                pixels.setPixelColor(i, pixels.Color(0, 127, 0));//grün
            
                pixels.show();   // Send the updated pixel colors to the hardware.
            
                delay(DELAYVAL); // Pause before next pass through loop
                
              }
              if (digitalRead(1) == LOW) {
                  x=4;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ***************BLAU*****************
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH && x==4) {
              //pixels.clear(); // Set all pixel colors to 'off'
            
              // The first NeoPixel in a strand is #0, second is 1, all the way up
              // to the count of pixels minus one.
              for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
            
                // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
                // Here we're using a moderately bright blue color:
                pixels.setPixelColor(i, pixels.Color(0, 0, 127));//blau
            
                pixels.show();   // Send the updated pixel colors to the hardware.
            
                delay(DELAYVAL); // Pause before next pass through loop
                
              }
              if (digitalRead(1) == LOW) {
                  x=5;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ***************ORANGE***************
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH && x==5) {
              //pixels.clear(); // Set all pixel colors to 'off'
            
              // The first NeoPixel in a strand is #0, second is 1, all the way up
              // to the count of pixels minus one.
              for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
            
                // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
                // Here we're using a moderately bright orange color:
                pixels.setPixelColor(i, pixels.Color(127, 33, 0));//orange
            
                pixels.show();   // Send the updated pixel colors to the hardware.
            
                delay(DELAYVAL); // Pause before next pass through loop
               
              }
               if (digitalRead(1) == LOW) {
                  x=6;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ********theaterChaseWhite***********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==6) {
              theaterChase(strip.Color(127, 127, 127), 50); // White
                
              
              if (digitalRead(1) == LOW) {
                  x=7;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ********theaterChaseRot***********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==7) {
              theaterChase(strip.Color(127, 0, 0), 50); // Red
                
              
              if (digitalRead(1) == LOW) {
                  x=8;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ********theaterChaseGren***********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==8) {
              theaterChase(strip.Color(0, 127, 0), 50); // Green
                
              
              if (digitalRead(1) == LOW) {
                  x=9;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ********theaterChaseBlau***********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==9) {
              theaterChase(strip.Color(0, 0, 127), 50); // Blau
                
              
              if (digitalRead(1) == LOW) {
                  x=10;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
               /***********************************
              ********theaterChaseOrange***********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==10) {
              theaterChase(strip.Color(127, 33, 0), 50); // Blau
                
              
              if (digitalRead(1) == LOW) {
                  x=11;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ***************RAINBOW**************
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==11) {
              rainbow(10);// <Zahl=schnellerer Farbwechsel
                
              
              if (digitalRead(1) == LOW) {
                  x=12;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }
              /***********************************
              ********theaterChaseRainbow*********
              ***********************************/
              delay(1);
              while (digitalRead(1) == HIGH&&x==12) {
              theaterChaseRainbow(50);
                
              
              if (digitalRead(1) == LOW) {
                  x=1;
                   EEPROM.put(0, x);//Variable X im EEprom speichern 
                }
              }


 

  
}//loop Ende

