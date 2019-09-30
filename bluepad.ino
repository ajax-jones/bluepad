/*
||
|| @file Button.pde
https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/ble-services
*/
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif
#include <Button.h>


    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"

// ---------------------------------
// Key definitions
#define BUTTON_KEY1 KEY_F13
#define BUTTON_KEY2 KEY_F14
#define BUTTON_KEY3 KEY_F15
#define BUTTON_KEY4 KEY_F16
#define BUTTON_KEY5 KEY_F17
#define BUTTON_KEY6 KEY_F18
#define BUTTON_KEY7 KEY_F19
#define BUTTON_KEY8 KEY_F20

// Pin definitions
#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 5
#define BUTTON_PIN4 6
#define BUTTON_PIN5 13
#define BUTTON_PIN6 10
#define BUTTON_PIN7 11
#define BUTTON_PIN8 12
#define F1 "3A"
#define F2 "3B"
#define F3 "3C"

#define RWD "04"    // a
#define FWD "16"    // s
#define INCUT "0C"  // i
#define OUTCUT "12" // o
#define IMPORT "3A" // F1
#define EXPORT "3B" // F2
#define CLEAR "13"  // p
#define FLIGHT "http://www.flightradar.com" // macro to go there...


// Create the bluefruit object, either software serial...uncomment these lines
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
// A small helper

void error(const __FlashStringHelper*err) {
 // Serial.println(err);
  while (1);
}




//create a Button object at pin 12

Button button1 = Button(2,PULLUP);
Button button2 = Button(3,PULLUP);
Button button3 = Button(5,PULLUP);
Button button4 = Button(6,PULLUP);

Button button5 = Button(13,PULLUP);
Button button6 = Button(10,PULLUP);
Button button7 = Button(11,PULLUP);
Button button8 = Button(12,PULLUP);

void setup(){


//  while (!Serial);  // required for Flora & Micro
//  delay(500);

//  Serial.begin(115200);
 // Serial.println(F("Adafruit Bluefruit HID Keyboard Example"));
//  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
//  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
//  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
 //   Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  /* Change the device name to make it easier to find */
//  Serial.println(F("Setting device name to 'Bluebutton Keypad': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Bluefruit Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
 // Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
//  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }

  
 // pinMode(13,OUTPUT); //debug to led 13
 //  Serial.begin(115200);
 //  Serial.println();
//  Serial.println("buttonbox v1.1");
  
}

void loop(){

 // for(int i = 0; i < NumButtons; i++){
 //   buttons[i].update();
 // }

  //Serial.println(NumButtons); 
  
  if(button1.uniquePress()){  
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(FWD);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
    };
  if(button2.uniquePress()){  
      Serial.println("Button pressed 2");   
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(OUTCUT);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
      };
  if(button3.uniquePress()){  Serial.println("Button pressed 3");   
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(INCUT);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
};
  if(button4.uniquePress()){  Serial.println("Button pressed 4"); 
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(RWD);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
  };

  if(button5.uniquePress()){  Serial.println("Button pressed 5");   ble.print("AT+BleKeyboard="); ble.println("F9");  };
  if(button6.uniquePress()){  
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(CLEAR);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
};
  if(button7.uniquePress()){  
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(EXPORT);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
 };
  if(button8.uniquePress()){  
    ble.print("AT+BLEKEYBOARDCODE=00-00-");
    ble.println(IMPORT);
    ble.println("AT+BLEKEYBOARDCODE=00-00");  
};
  

}
