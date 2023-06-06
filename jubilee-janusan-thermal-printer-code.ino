/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
// #include "adalogo.h"
// #include "adaqrcode.h"

// Here's the new syntax when using SoftwareSerial (e.g. Arduino Uno) ----
// If using hardware serial instead, comment out or remove these lines:

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
// Then see setup() function regarding serial & printer begin() calls.

// Here's the syntax for hardware serial (e.g. Arduino Due) --------------
// Un-comment the following line if using hardware serial:

//Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.

// -----------------------------------------------------------------------

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();        // Init printer (same regardless of serial type)

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.

  // Font options
  // printer.setFont('B');
  // printer.println("FontB");
  // printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  // printer.setFont('A');
  // printer.println("FontA (default)");
  // printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  // // Test inverse on & off
  // printer.inverseOn();
  // printer.println(F("Inverse ON"));
  // printer.inverseOff();

  // // Test character double-height on & off
  // printer.doubleHeightOn();
  // printer.println(F("Double Height ON"));
  // printer.doubleHeightOff();

  // // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  // printer.justify('R');
  // printer.println(F("Right justified"));
  // printer.justify('C');
  // printer.println(F("Center justified"));
  // printer.justify('L');
  // printer.println(F("Left justified"));

  // Test more styles
  // printer.boldOn();
  // printer.println(F("Bold text"));
  // printer.boldOff();

  // printer.underlineOn();
  // printer.println(F("Underlined text"));
  // printer.underlineOff();

  // printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  // printer.println(F("Large"));
  // printer.setSize('M');
  // printer.println(F("Medium"));
  // printer.setSize('S');
  // printer.println(F("Small"));

  // printer.justify('C');
  // printer.println(F("normal\nline\nspacing"));
  // printer.setLineHeight(50);
  // printer.println(F("Taller\nline\nspacing"));
  // printer.setLineHeight(); // Reset to default
  // printer.justify('L');

  // Barcode examples:
  // CODE39 is the most common alphanumeric barcode:
  // printer.printBarcode("vedant", CODE128);
  // printer.setBarcodeHeight(100);
    // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault();        // Set printer to defaults
  printer.setBarcodeHeight(50); // Restore printer to defaults
}



void loop() {
    if (Serial.available()) {
      String myString = Serial.readString();
      const char* myCharPtr = myString.c_str();
      printer.boldOn();
      printer.justify("C");
      printer.println(myCharPtr);
      printer.boldOff();

      printer.feed(1);

      //printer.println("A study demonstrated that African American and Asian faces had a misidentification rate up to 100 times higher than that of white faces, with Native Americans experiencing the highest rate of false positives.");
printer.println("Research from the University of Essex in the UK showed that the technology they tested was accurate in just 19% of cases.");
//printer.println("Facial recognition technology they tested performed the worst when recognizing Black faces— especially Black women’s faces.");
//printer.println("You are identified as white, you are 100 times less likely to be misidentified.");
printer.println("You are identified as black you're up to 100 times more likely to be misientified.");
//printer.println("You are identified as Asian and are 100 times more likely to be misidentified than white faces");

      // printer.print(F("CODE128:"));
      // printer.printBarcode(myCharPtr, CODE128);

      printer.feed(2);

      printer.sleep();      // Tell printer to sleep

      printer.wake();       // MUST wake() before printing again, even if reset
      printer.setDefault(); // Restore printer to defaults
    }

}
