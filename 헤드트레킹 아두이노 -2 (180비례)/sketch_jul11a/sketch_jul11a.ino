#include <SPI.h>
#include <WiFiNINA.h>
#include <Servo.h>

// WiFi network information
char ssid[] = "network";        // your network SSID (name)
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

// Servo objects
Servo myservox;  // create Servo object to control a servo
Servo myservoy;  // create Servo object to control a servo

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);      // initialize serial communication
  
  // attach the servos to pins
  myservox.attach(6);  // attaches the servo on pin 6 to the Servo object
  myservoy.attach(5);  // attaches the servo on pin 5 to the Servo object

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
  printWifiStatus();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // send a standard HTTP response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<html><body>");
            client.print("<button onclick=\"location.href='/RH'\">Red ON</button>");
            client.print("<button onclick=\"location.href='/RL'\">Red OFF</button>");
            client.print("<button onclick=\"location.href='/GH'\">Green ON</button>");
            client.print("<button onclick=\"location.href='/GL'\">Green OFF</button>");
            client.print("<button onclick=\"location.href='/BH'\">Blue ON</button>");
            client.print("<button onclick=\"location.href='/BL'\">Blue OFF</button>");
            client.print("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // LED control
        if (currentLine.endsWith("GET /RH")) {
          digitalWrite(LEDR, HIGH);
        }
        if (currentLine.endsWith("GET /RL")) {
          digitalWrite(LEDR, LOW);
        }
        if (currentLine.endsWith("GET /GH")) {
          digitalWrite(LEDG, HIGH);
        }
        if (currentLine.endsWith("GET /GL")) {
          digitalWrite(LEDG, LOW);
        }
        if (currentLine.endsWith("GET /BH")) {
          digitalWrite(LEDB, HIGH);
        }
        if (currentLine.endsWith("GET /BL")) {
          digitalWrite(LEDB, LOW);
        }

        // Servo control
        if (currentLine.startsWith("GET /X")) 
        {
          int indexX = currentLine.indexOf('X') + 1;
          int indexY = currentLine.indexOf('Y');
          int posx = currentLine.substring(indexX, indexY).toInt();
          int posy = currentLine.substring(indexY + 1).toInt();
          myservox.write(posx);
          myservoy.write(posy);
        }
      }
    }
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
