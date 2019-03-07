void setupSD()
{
  //Initialize the SD Card Slot
  radio.print("Initializing SD card...");
  pinMode(chipSelect, OUTPUT); //For the SD Card to work
  if (SD.begin(chipSelect))
  {
    radio.println("initialization successful!");
    DCAWS_GPS = SD.open("DCAWS_GPS.csv", FILE_WRITE);
  }
  else
  {
    Serial.println("initialization failed!");
    return;
  }
}

void checkSD()
{
  if (!DCAWS_GPS)
  {
    radio.println(F("SD card failed!"));
 //   missionReady = false;
    return;
  }
  radio.print(F("SD card initialization confirmed and found files: "));
                                    //  if (DCAWS_Depth)
                                    //radio.print(F("DCAWS_Depth, "));
  if (DCAWS_GPS)
    radio.println(F("DCAWS_GPS"));
}
