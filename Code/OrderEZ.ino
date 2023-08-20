#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <EthernetClient.h>
#include <ArduinoJson.h>
#include "source.h" // All Web Pages are written here
#include "DFRobotDFPlayerMini.h"
#include <HardwareSerial.h>


HardwareSerial Serial2(PA3,PD5);

// Create the Player object
DFRobotDFPlayerMini player;

int flag=0;

IPAddress ip(192,168,1,7);

// Define Ethernet Client parameters
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);              // Server declaring on port 80

DynamicJsonDocument jsonDoc(1024);
String jsonStr;
                      
void setup()
{

    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    Serial2.begin(9600);
     if (player.begin(Serial2)) // Checking the df player mini and speaker
    {
     Serial.println("OK");
      player.volume(30);
      player.play(1);
    }
  else
  {
    Serial.println("Error");
  }

    // by default, the local IP address will be 192.168.1.7
    Ethernet.begin(mac,ip);
    
    // start the web server on port 80
    server.begin();

   
    
}

void loop()
{
    int t;
    char c;
    // compare the previous AP status to the current status
    IPAddress ip = Ethernet.localIP();
    
    // Wifi Server check
    EthernetClient client = server.accept(); // listen for incoming clients
    if (client) { // if you get a client,
        Serial.println("new client"); // print a message out the serial port
        String currentLine = ""; // make a String to hold incoming data from the client
        while (client.connected()) { // loop while the client's connected
            if (client.available()) { // if there's bytes to read from the client,
                c = client.read(); // read a byte, then
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.println(index_first); // Index page will be loaded
                        client.println(index_sec);
                        client.println(index_third);
                        client.println(index_fourth);
                        client.println(index_fifth);
                        client.println(index_sixth);
                        delay(10);
                        break;
                    }
                    else {
                        // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                }
                else if (c != '\r') { // if you got anything else but a carriage return character,
                    currentLine += c; // add it to the end of the currentLine
                }

                // Check to see if the client request was a post
                if (currentLine.endsWith("POST /order")) {
                    currentLine = "";
                    while (client.connected()) {
                        if (client.available()) {
                            c = client.read(); // read a byte, then
                            if (c == '\n') { // if the byte is a newline character
                                //if (currentLine.length() == 0) break; // no length:  end of data request
                                currentLine = ""; // if you got a newline, then clear currentLine:
                            }
                            else if (c != '\r') currentLine += c; // if you got anything else but a carriage return character, add to string
                            if (currentLine.startsWith("cartItems=")){
                                if (currentLine.endsWith("%3B")){
                                    Serial.println(currentLine);
                                    client.println("HTTP/1.1 200 OK");
                                    client.println("Content-type:text/html");
                                    client.println();
                                    client.println(res); // Response page will be loaded
                                    client.stop();
                                    int delimiterIndex = currentLine.indexOf('=');
                                    if (delimiterIndex != -1) {
                                        String key = currentLine.substring(0, delimiterIndex);
                                        String value = currentLine.substring(delimiterIndex + 1);
                                        
                                        Serial.println("Key: " + key);
                                        Serial.println("Value: " + value);
                                        if (value.endsWith("%3B")) {
                                            value = value.substring(0, value.length() - 3);
                                        }
                                    
                                        // Extract table_id from input value
                                        int tableIdIndex = value.indexOf("table_id");
                                        if (tableIdIndex != -1) {
                                            String tableIdStr = value.substring(tableIdIndex + 11);
                                            Serial.println(tableIdStr);
                                            int tableId = tableIdStr.toInt();
                                            Serial.println("Table: " + String(tableId));
                                            
                                            // Create or get the JSON array using table_id as the key
                                            JsonArray orderItems = jsonDoc.createNestedArray(String(tableId));
                                            
                                            int startPos = 0;
                                            while (startPos < value.length()) {
                                                int colonIndex = value.indexOf("%3A", startPos);
                                                int commaIndex = value.indexOf("%2C", startPos);
                                                
                                                if (colonIndex == -1) {
                                                    break;
                                                }
                                                
                                                String itemName = value.substring(startPos, colonIndex);
                                                String itemCount = value.substring(colonIndex + 3, commaIndex != -1 ? commaIndex : value.length());
                                                
                                                JsonObject item = orderItems.createNestedObject();
                                                item["name"] = itemName;
                                                item["count"] = itemCount.toInt();
                                                
                                                startPos = commaIndex != -1 ? commaIndex + 3 : value.length();
                                            }
                                            
                                            // Serialize JSON to string
                                            jsonStr = "";
                                            serializeJson(jsonDoc, jsonStr);
                                            Serial.println("JSON Data: " + jsonStr);
                                            player.play(1); // Playing sound
                                        }
                                        else{
                                            Serial.println("? not found");
                                        }
                                        
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    delay(10);
                } 

                if (currentLine.endsWith("GET /admin")) {
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println();
                  client.println(admin_first);
                  client.println("const orders = "+ jsonStr+";");
                  client.println(admin_second);
                  client.stop();
                }

               if (currentLine.endsWith("POST /delete")) {
                    currentLine = "";
                    while (client.connected()) {
                        if (client.available()) {
                            c = client.read(); // read a byte, then
                            if (c == '\n') { // if the byte is a newline character
                                //if (currentLine.length() == 0) break; // no length:  end of data request
                                currentLine = ""; // if you got a newline, then clear currentLine:
                            }
                            else if (c != '\r') currentLine += c; // if you got anything else but a carriage return character, add to string
                            if (currentLine.startsWith("table_id")){
                              if (currentLine.endsWith("%3B")){
                                int StartIndex = currentLine.indexOf('=');
                                String table_id = currentLine.substring(StartIndex + 1, currentLine.length() - 3); // Extract table_id
                                Serial.println("Table ID to Remove: " + table_id);
           
                                jsonDoc.remove(table_id);
                                jsonStr="";
                                serializeJson(jsonDoc, jsonStr);
                                Serial.println(jsonStr);
                       
                              client.println("HTTP/1.1 200 OK");
                              client.println("Content-type:text/html");
                              client.println();
                              //client.println(res); // Response page will be loaded
                              client.stop();
                              }
                            }
                        }
                    }
               }
                
            } 
        }

        // close the connection:
        client.stop();
        Serial.println(" client disconnected");
    }
}
