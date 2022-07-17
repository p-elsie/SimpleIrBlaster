/*
 * SimpleIrBlaster.cpp
 *
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *  
 *  The copyrighted code has been significantly modified by p-elsie. 
 *  
 *  
 *  Vizio TV code reference: https://github.com/probonopd/irdb/blob/master/codes/Vizio/Unknown_VX37L/4%2C-1.csv 
 *  Samsung TV code reference: https://github.com/probonopd/irdb/blob/master/codes/Samsung/TV/7%2C7.csv
 *  LG TV code reference: https://github.com/probonopd/irdb/blob/master/codes/LG/TV/4%2C-1.csv
 *  
 *
 *  MIT License
 */
#include <Arduino.h>

//#define SEND_PWM_BY_TIMER
//#define USE_NO_SEND_PWM
//#define NO_LED_FEEDBACK_CODE // saves 418 bytes program memory

#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>

void setup() {
    Serial.begin(115200);

    #if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
        delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
    #endif

    //Print usage to Serial monitor
    usage();

    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    Serial.setTimeout(100);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
   
    // if not a digit 
    if (Serial.peek() < 48 || Serial.peek() > 57) {
      Serial.readStringUntil('\n');
      Serial.println();
      usage();
    }
    else {
      // look for four valid integers in the incoming serial stream:
      uint8_t  type = Serial.parseInt(SKIP_NONE); //returns 0 after timeout, if an integer is not found
      Serial.read();
      uint16_t sAddress = Serial.parseInt(SKIP_NONE);
      Serial.read();
      uint8_t  sCommand = Serial.parseInt(SKIP_NONE);
      Serial.read();
      uint8_t  sRepeats = Serial.parseInt(SKIP_NONE);
  
      // look for the newline. That's the end of your sentence:
      if (Serial.read() == '\n') 
      {
            Serial.print(F("type="));
            Serial.print(type);
            Serial.print(F(", address="));
            Serial.print(sAddress);
            Serial.print(F(", command="));
            Serial.print(sCommand);
            Serial.print(F(", repeats="));
            Serial.print(sRepeats);    
            Serial.print(F(", type maps to "));
            switch (type) {      
            case 1:
              Serial.println(F("NEC"));
              IrSender.sendNEC(sAddress, sCommand, sRepeats);
              break;
            case 2:
              Serial.println(F("Samsung"));
              IrSender.sendSamsung(sAddress, sCommand, sRepeats);
              break;
            case 3:
              Serial.println(F("Sony"));
              IrSender.sendSony(sAddress, sCommand, sRepeats);
              break;
            case 4:
              Serial.println(F("Panasonic"));
              IrSender.sendPanasonic(sAddress, sCommand, sRepeats);
              break;              
            case 5:
              Serial.println(F("RC5"));
              IrSender.sendRC5(sAddress, sCommand, sRepeats);
              break;
            case 6:
              Serial.println(F("RC6"));
              IrSender.sendRC6(sAddress, sCommand, sRepeats);
              break;
            case 7:
              Serial.println(F("Sharp"));
              IrSender.sendSharp(sAddress, sCommand, sRepeats);
              break;
            case 8:
              Serial.println(F("LG"));
              IrSender.sendLG(sAddress, sCommand, sRepeats);
              break;
            case 9:
              Serial.println(F("JVC"));
              IrSender.sendJVC(sAddress, sCommand, sRepeats);
              break;
            case 10:
              Serial.println(F("Onkyo"));
              IrSender.sendOnkyo(sAddress, sCommand, sRepeats);
              break;
            case 11:
              Serial.println(F("Apple"));
              IrSender.sendApple(sAddress, sCommand, sRepeats);
              break;
            default:
              // if nothing else matches, do the default
              Serial.println("NONE!!!");
              usage();
          }
      }      
    }
  
    Serial.flush();
    delay(100);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
  }
}

void usage() {
  Serial.println();
  Serial.print(F("Usage:\n\n"));
  Serial.print(F("  type address command repeats\n\n"));
  Serial.print(F("  The above input, should be four integer values, delimited with a space or comma character.\n\n"));
  Serial.print(F("  These are the supported types:\n\n"));
  Serial.println("    1 NEC");
  Serial.println("    2 Samsung");
  Serial.println("    3 Sony");
  Serial.println("    4 Panasonic");
  Serial.println("    5 RC5");
  Serial.println("    6 RC6");
  Serial.println("    7 Sharp");
  Serial.println("    8 LG");
  Serial.println("    9 JVC");
  Serial.println("    10 Onkyo");  
  Serial.println("    11 Apple");  
  Serial.println();
  Serial.println(F("IRDB code reference: https://github.com/probonopd/irdb"));
  Serial.println(F("Source code reference: https://github.com/p-elsie"));
  // Know which program is running on my Arduino
  Serial.println(F("Source code info: " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE)); 
  delay(1000); 
}
