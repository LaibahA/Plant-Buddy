#include <WiFi101.h>

const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "DEVID HERE"; //device ID on Pushingbox for our Scenario
const char* MY_SSID = "WIFI NAME HERE";
const char* MY_PWD =  "WIFI PASSWORD HERE";
int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
// check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
// attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(MY_SSID);
    //Connect to WPA/WPA2 network.Change this line if using open/WEP network
    status = WiFi.begin(MY_SSID, MY_PWD);
// wait 10 seconds for connection:
    delay(10000);
  }
Serial.println("Connected to wifi");
  printWifiStatus();
}
void loop() {
// Wait between measurements.
  delay(10000);
//prefer to use float, but package size or float conversion isnt working
  //will revise in future with a string fuction or float conversion function
float moistureHum = analogRead(A1); //this gets data from the analog pin we connect to with our wiring
  moistureHum = (1023 - moistureHum) * 100 /1023;
// Check if any reads failed and exit early (to try again).
  if (isnan(moistureHum))
  {
    Serial.println("Failed to read from sensor!");
    return;
  }
Serial.print("Soil Moisture ");
  Serial.print(moistureHum);
Serial.println("\nSending Data to Server...");
  // if you get a connection, report back via serial:
  WiFiClient client;  //Instantiate WiFi object, can scope from here or Globally
//API service using WiFi Client through PushingBox then relayed to Google
  if (client.connect(WEBSITE, 80))
  {
    client.print("GET /pushingbox?devid=" + devid
                 + "&moistureHum=" + (String) moistureHum
                );
// HTTP 1.1 provides a persistent connection, allowing batched requests
    // or pipelined to an output buffer
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(WEBSITE);
    client.println("User-Agent: MKR1000/1.0");
    //for MKR1000, unlike esp8266, do not close connection
    client.println();
    Serial.println("\nData Sent");
    client.stop();
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
