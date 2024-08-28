#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

void handleRoot();                //Handles the root URL request
void handleToggle();              //Handles the toggle button action

const char* ssid = "SkyNet";            // Replace with your WiFi SSID
const char* password = "A125-B040-C9271-D009";    // Replace with your WiFi password

// Static IP Configuration
IPAddress local_IP(192, 168, 50, 60);       // Set your desired static IP
IPAddress gateway(192, 168, 50, 1);          // Set your network's gateway
IPAddress subnet(255, 255, 255, 0);         // Set your subnet mask
IPAddress primaryDNS(8, 8, 8, 8);           // Optional: Set your preferred DNS server
IPAddress secondaryDNS(8, 8, 4, 4);         // Optional: Set a secondary DNS server

#define LED_PIN     15    // NeoPixel FeatherWing is on GPIO15
#define NUMPIXELS   32     // Number of NeoPixels on the FeatherWing
#define BRIGHTNESS  10    // Brightness level (0 - 255)

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
bool ledState = false;

void setup() {
  Serial.begin(115200);

  pixels.begin();         //intialize NeoPixel Featherwing
  pixels.setBrightness(BRIGHTNESS); //set brightness level
  pixels.clear();
  pixels.show();

  // Attempt to connect to Wi-Fi with a static IP
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    delay(1000);
    Serial.println("Attempting to connect...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html>\
  <head>\
    <style>\
      body { background-color: #222; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }\
      .button { background-color: #ff0000; color: white; font-size: 24px; padding: 20px 40px; border: none; border-radius: 10px; cursor: pointer; }\
    </style>\
  </head>\
  <body>\
    <button class='button' onclick='toggleLED()'>Toggle LED</button>\
    <script>\
      function toggleLED() {\
        var xhr = new XMLHttpRequest();\
        xhr.open('GET', '/toggle', true);\
        xhr.send();\
      }\
    </script>\
  </body>\
</html>";

  server.send(200, "text/html", html);
}

void handleToggle() {
  ledState = !ledState;

  if (ledState) {
    pixels.fill(pixels.Color(0, 150, 0)); // Green color
    pixels.show();
  } else {
    pixels.clear();
    pixels.show();
  }

  server.sendHeader("Location", "/", true);
  server.send(303);
}