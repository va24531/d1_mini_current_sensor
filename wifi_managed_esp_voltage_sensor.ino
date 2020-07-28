/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager


const int ACPin = A0;
#define AC_Detection_Range 10;    //set Non-invasive AC Current Sensor detection range (5A,10A,20A)
#define VREF 3.3

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

const int resetswitch = 14;

void setup() {
  Serial.begin(115200);
  pinMode(resetswitch, INPUT_PULLUP);
  
  Serial.print("SWITCH = ");  Serial.println(digitalRead(resetswitch));
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  if (digitalRead(resetswitch) == 0){ Serial.println("Reset Detected!"); wifiManager.resetSettings(); }
    
  wifiManager.autoConnect();
  
  Serial.println("Connected. Your device IP address is "); Serial.println(WiFi.localIP());
  server.begin();
}


void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {  }
            else if (header.indexOf("GET /5/off") >= 0) { }
            
            // Display the HTML web page
           // client.println("<!DOCTYPE html><html>");
           // client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
           // client.println("<link rel=\"icon\" href=\"data:,\">");
           // client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
           // client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
           // client.println("</style></head>");
            
            // Web Page Heading
           // client.println("<body><h1>ESP8266 Web Server</h1>");

            float ACCurrentValue = readACCurrentValue(); //read AC Current Value
              Serial.print("A,");Serial.print(ACCurrentValue); Serial.print(","); Serial.print("W,");Serial.print(ACCurrentValue * 120);Serial.println(",*");
                            
              client.print("A,");client.print(ACCurrentValue); client.print(","); client.print("W,");client.print(ACCurrentValue * 120);client.println(",*");
              
              
            //float aref = analogRead(ACPin) * (VREF/1023.0);
            //  Serial.print(" REFV: ");              Serial.println(aref);
            //  client.print(" REFV: ");              client.println(aref);

           //     client.print("<b><h2>* * * "); client.print(sensorValue); client.print(" * * *</h2></b>");
           // client.println("</body></html>");
            
            //client.println();
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}





      float readACCurrentValue()
      {
        float AC_Current_Value = 0;
        float peakVoltage = 0;  
          float voltageVirtualValue = 0;  //Vrms
            for (int i = 0; i < 5; i++) { peakVoltage += analogRead(ACPin); delay(1); }
            peakVoltage = peakVoltage / 5;   
            voltageVirtualValue = peakVoltage * 0.707;
            /*The circuit is amplified by 2 times, so it is divided by 2.*/
            voltageVirtualValue = (voltageVirtualValue / 1024 * VREF ) / 2;  
            AC_Current_Value = voltageVirtualValue * AC_Detection_Range;
          return AC_Current_Value;
      }
