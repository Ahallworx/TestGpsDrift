
// include libraries
#include <Adafruit_GPS.h>
#include <SD.h>

// declare serial constants
#define GPS_Serial Serial3
#define radio Serial2

// declare GPS
Adafruit_GPS GPS(&GPS_Serial);

// declare pin constants
#define chipSelect BUILTIN_SDCARD


//Declare constants
#define GPS_DRIFT_TIME 60000             // desired duration of drift state in milliseconds
#define MAX_GPS_TIME 120000               // 2min cutoff for GPS to recieve new signal
#define WINSZ_GPS 100                    // window size used for GPS of 100
#define MIN_GPS_NUM  10                  // Minimum number of good gps readings taken during GPS_DRIFT to consider successful
#define GPS_SEND_FREQ 50000

//Declare variables
File DCAWS_GPS;                          // Create file on the sd card to log GPS
bool newGPS = false;
int goodGPSCount = 0;
bool avgInitGPS = true;
bool initGPS = true;
double avgLat;
double avgLon;

//declare elapsed timer to use for gpsTimeout
elapsedMillis gpsTimeout;

void setup() {
//initialize components
  setupRadio();
  checkRadio();
  setupGPS();
  delay(1000);
  setupSD();
  checkSD();
  
}

//create timer for mission
elapsedMillis sinceStart;
elapsedMillis sinceGPS;


void loop() 
{
  if (sinceStart < GPS_DRIFT_TIME)
  {
    getGPS();
    if (newGPS)
    {
      // Calculate the moving average and set the init flag to false
      mvavgGPS((double) GPS.latitude, (double) GPS.longitude, avgInitGPS);
      avgInitGPS = false;
      if (initGPS)
      {
        sendGPS();
        initGPS = false;
        sinceStart = 0;
      }
      logGPS();
      newGPS = false;
    }
  }
  else if (sinceStart > GPS_DRIFT_TIME && (initGPS || (goodGPSCount < MIN_GPS_NUM)))
  {
                 //state = ABORT;
      radio.println(F("Timed out without getting first value or too few good values."));
  }
  else
  {
    getGPS();
    if (newGPS)
      sendGPS();
    
                //    state = SAMPLE_MISSION;
                //    checkSafetySensors();
  }
}
