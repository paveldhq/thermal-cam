/* OTAWebUpdater.ino Example from ArduinoOTA Library
 * Rui Santos
 * Complete Project Details https://randomnerdtutorials.com
 */
// https://github.com/me-no-dev/ESPAsyncWebServer
//https://github.com/me-no-dev/AsyncTCP

#include "ESPAsyncWebServer.h"
#include <WiFi.h>
#include <WiFiClient.h>
//#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "SPIFFS.h"

 
const char* host = "esp32";
const char* ssid = "esp_test";
const char* password = "12345679";
 

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//WebServer server(80);
 
/*
 * Login page
 */
//const char* loginIndex = "";
/*
 * Server Index Page
 */
 
//const char* serverIndex = "";
 
/*
 * setup function
 */
void setup(void) {
  Serial.begin(115200);
 if(!SPIFFS.begin(true)){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
}
  // Connect to WiFi network
  //WiFi.begin(ssid, password);
 WiFi.softAP(ssid, password);
  Serial.println("");
 
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */

 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/login.html", "text/html");
  });

   server.on("/server.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/server.html", "text/html");
  });


  /*handling uploading firmware file */
  /*
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html);
    response->addHeader("Connection", "close");
    
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // flashing firmware to ESP
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
*/
  
  server.begin();
}
 
void loop(void) {
  //server.handleClient();
  //delay(1);
}
