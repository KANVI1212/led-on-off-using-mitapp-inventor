#include <ESP8266WiFi.h>
 
const char* ssid = "kanvi";
const char* password = "12345678910";
 

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600); //Default Baud Rate for NodeMCU
  delay(10);
 
 
  pinMode(16, OUTPUT);  // Connect Relay to NodeMCU's D0 Pin
  digitalWrite(16, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  int val;
  if (req.indexOf("ON") != -1)
    val = 0;
  else if (req.indexOf("OFF") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
 
  // Set GPIO2 according to the request
  digitalWrite(16, val);
  
  client.flush();
 
}
