void setupSD()
{
  //Initialize the SD Card Slot
  radio.print("Initializing SD card...");
  pinMode(chipSelect, OUTPUT); //For the SD Card to work
  if (SD.begin(chipSelect))
  {
    radio.println("initialization successful!");
    gpsfile = SD.open("gpsfile.csv", FILE_WRITE);
  }
  else
  {
    Serial.println("initialization failed!");
    return;
  }
}

void checkSD()
{
  if (!gpsfile)
  {
    radio.println(F("SD card failed!"));
 //   missionReady = false;
    state = SAMPLE_MISSION;
    return;
  }
  radio.print(F("SD card initialization confirmed and found files: "));
                                    //  if (DCAWS_Depth)
                                    //radio.print(F("DCAWS_Depth, "));
  if (gpsfile)
    radio.println(F("gpsfile"));
}
