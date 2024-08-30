#include <ESP8266WiFi.h>           // Include library for Wi-Fi functionality
#include <ESP8266WebServer.h>      // Include library for creating a web server
#include <Adafruit_NeoPixel.h>     // Include library for controlling NeoPixel LEDs

void handleRoot();                // Function prototype to handle root URL requests
void handleToggle();              // Function prototype to handle toggle button action

const char* ssid = "WIFI_SSID";            // Replace with your Wi-Fi SSID
const char* password = "WIFI_PASSWORD";    // Replace with your Wi-Fi password

// Static IP Configuration
IPAddress local_IP(192, 168, 50, 60);       // Set desired static IP address for the device
IPAddress gateway(192, 168, 50, 1);          // Set the gateway IP address of the network
IPAddress subnet(255, 255, 255, 0);         // Set the subnet mask of the network
IPAddress primaryDNS(8, 8, 8, 8);           // Optional: Set the primary DNS server
IPAddress secondaryDNS(8, 8, 4, 4);         // Optional: Set the secondary DNS server

#define LED_PIN     15    // Pin number where NeoPixel FeatherWing is connected (GPIO15)
#define NUMPIXELS   32     // Number of NeoPixels in the FeatherWing
#define BRIGHTNESS  10    // Brightness level for NeoPixels (0 - 255)

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800); // Initialize NeoPixel strip
ESP8266WebServer server(80);        // Create a web server instance listening on port 80
bool ledState = false;              // Variable to keep track of LED state (on/off)

void setup() {
  Serial.begin(115200);             // Start serial communication at 115200 baud rate

  Serial.print("SSID: ");           // Print SSID to serial monitor
  Serial.println(ssid);
  Serial.print("Password: ");       // Print password to serial monitor
  Serial.println(password);

  pixels.begin();                   // Initialize NeoPixel FeatherWing
  pixels.setBrightness(BRIGHTNESS); // Set brightness level for NeoPixels
  pixels.clear();                   // Clear all NeoPixels (turn them off)
  pixels.show();                    // Update NeoPixels to reflect changes

  // Attempt to configure Wi-Fi with a static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure"); // Print error if configuration fails
  }

  WiFi.begin(ssid, password);      // Start connecting to Wi-Fi network with given credentials

  // Wait until connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);                   // Wait 1 second before retrying
    Serial.println("Connecting to WiFi..."); // Print connection status
  }

  Serial.println("Connected to WiFi"); // Print success message when connected
  Serial.print("IP Address: ");       // Print the assigned IP address
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);        // Define handler function for root URL
  server.on("/toggle", handleToggle); // Define handler function for toggle URL

  server.begin();                   // Start the web server
  Serial.println("HTTP server started"); // Print message indicating the server has started
}

void loop() {
  server.handleClient();            // Handle incoming client requests
}

void handleRoot() {
  // Create HTML content for the root URL
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

  server.send(200, "text/html", html); // Send the HTML content to the client with a 200 OK status
}

void handleToggle() {
  ledState = !ledState;              // Toggle the LED state (on/off)

  if (ledState) {                   // If LED state is true (on)
    pixels.fill(pixels.Color(0, 150, 0)); // Set NeoPixels to green color
    pixels.show();                 // Update NeoPixels to reflect changes
  } else {                         // If LED state is false (off)
    pixels.clear();                // Turn off all NeoPixels
    pixels.show();                 // Update NeoPixels to reflect changes
  }

  server.sendHeader("Location", "/", true); // Redirect to root URL
  server.send(303);                        // Send HTTP 303 See Other response
}
