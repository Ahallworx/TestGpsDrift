void setupRadio()
{
  radio.begin(115200);
}

void checkRadio(void)
{
  char key = 'n';
  while(key != 'C')
  {
    radio.println(F("Press 'C' to confirm DCAWS to Radio comms"));
    char key = (char)radio.read();
    if (key == 'C')
    {
      radio.println(F("Comms confirmed"));
      break;
    }
    else
    {
      radio.println(F("Either a key other than 'C' was pressed or unable to confirm comms!"));
//      missionReady = false;
    }
  }
}
