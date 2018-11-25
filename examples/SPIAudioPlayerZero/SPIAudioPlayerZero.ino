/*
  Simple Audio Player for Arduino Zero using SPI flash

 Demonstrates the use of the Audio library for the Arduino Zero

 Hardware required :
 * SPI flash connected to Arduino
 * A sound file named "test.wav" in the root directory of the SPI flash
 * An audio amplifier to connect to the DAC0 and ground
 * A speaker to connect to the audio amplifier

 
 Arturo Guadalupi <a.guadalupi@arduino.cc>
 Angelo Scialabba <a.scialabba@arduino.cc>
 Claudio Indellicati <c.indellicati@arduino.cc>

 This example code is in the public domain

 http://arduino.cc/en/Tutorial/SimpleAudioPlayerZero

*/

#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <AudioZero.h>

#define FLASH_CHIP_SELECT 6

void setup()
{
  // debug output at 115200 baud
  Serial.begin(115200);

  // Start SerialFlash
  if (!SerialFlash.begin(FLASH_CHIP_SELECT)) {
    while (1) {
      Serial.println ("Cannot access SPI Flash chip");
      delay (1000);
    }
  }
  Serial.println(" done.");

  // 44100kHz stereo => 88200 sample rate
  AudioZero.begin(2*44100);
}

void loop()
{
  int count = 0;

  // open wave file from sdcard
  SerialFlashFile myFile = SerialFlash.open("test.wav");
  if (!myFile) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening test.wav");
    while (true);
  }

  Serial.print("Playing");
  
  // until the file is not finished  
  AudioZero.play(myFile);

  Serial.println("End of file. Thank you for listening!");
  while (true) ;
}
