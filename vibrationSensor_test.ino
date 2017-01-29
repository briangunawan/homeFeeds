
/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using a WiFi shield.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Circuit:
 * WiFi shield attached
 
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#include <SPI.h>
#include <WiFi.h>


char ssid[] = "Cambs_Hack"; //  your network SSID (name) 
char pass[] = "";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

// RYAN VIBRATION SENSORS
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
//END


int status = WL_IDLE_STATUS;

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)

char server[] = "api.private-beta-1.pusherplatform.com";

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);
  
    // wait 10 seconds for connection:
    delay(5000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via sexrial:
}

void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
    sensorValue = analogRead(analogInPin);
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
    if (outputValue > 127) {
      system("curl -k -v -X POST  https://api.private-beta-1.pusherplatform.com:443/apps/5f737f80-56f4-4927-8254-61d2bd9517f1/feeds/homeFeed -d '{\"items\": [\"Someone is at the door.\"]}'");
      delay(10000);
    }
    else {
      delay(20);
    }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





