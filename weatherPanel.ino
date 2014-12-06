//////////////////////
// Library Includes //
//////////////////////
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

/////////////////////
// Hardware Hookup //
/////////////////////
// R0, G0, B0, R1, G1, B1 should be connected to pins 
// 2, 3, 4, 5, 6, and 7 respectively. Their pins aren't defined,
// because they're controlled directly in the library. These pins
// can be moved (somewhat):
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3 // Comment this line out if you're using a 32x16
// CLK can be moved but must remain on PORTB(8, 9, 10, 11, 12, 13)
#define CLK 11  // MUST be on PORTB!

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  Serial.begin(9600);    // send temperature data via sx
  pinMode(A4,INPUT);     // use A4 as analoge input pin for the sensor
  
  matrix.begin();
}

void loop() {
   matrix.fillScreen(0);
 
   int tempSensValue = analogRead(A4);
   float voltage = tempSensValue * 5.0;				// voltage at pin in volt
   voltage /= 1024.0; 						// voltage = sensorValue x (5/1024)
   float temperature = (voltage - 0.5) * 100; 
   
   printTemperature(temperature);
   
   delay(2000);
}

void printTemperature(float temp) {
  matrix.setCursor(1, 4);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);  
  
  char sign = temp <0? '-' : '+';
  int dd = floor(temp / 10);
  int d = floor( (temp - dd*10) );
  int _d = floor( ( temp -(dd*10 + d )) * 10 );
 
  matrix.setTextColor(matrix.Color333(255,0,0));
  matrix.print(sign);
  
  if ( dd > 0 )
    matrix.print((char)(48+dd));
  else 
    matrix.print(' ');  
  matrix.print((char)(48+d));
  
  if ( _d != 0 ) {
    matrix.print('.');
    matrix.print((char)(48+_d));  
  }
  
  Serial.print("TEMP: (");
  Serial.print(temp);
  Serial.print(") ");
  Serial.print(dd);
  Serial.print(d);
  Serial.print(".");
  Serial.print(_d);
  Serial.print("\n"); 
}
