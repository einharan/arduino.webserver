#include <Arduino.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Wifi@Home";
const char* password = "02062000";
const int port = 80;

AsyncWebServer server(port);

void flashSystem(const char* _file)
{
	if (!LittleFS.begin())
	{
		Serial.println("[error] failed to mount LittleFS");
		return;
	}

	File file = LittleFS.open(_file, "r");
	if (!file)
	{
		Serial.println("[error] failed to open file");
		return;
	}

	Serial.println("file content: ");
	while (file.available())
	{
		Serial.write(file.read());
	}
	file.close();


}

String processor(const String& var)
{
	Serial.println(var);
	return String();
}
 
void setup()
{
	Serial.begin(115200);
	flashSystem("/sample.txt");

	// Connect to Wi-Fi
  	WiFi.begin(ssid, password);
  	while (WiFi.status() != WL_CONNECTED)
	{
    	delay(1000);
    	Serial.println("Connecting to WiFi..");
  	}

  	Serial.println(WiFi.localIP());

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		request->send(LittleFS, "index.html");
	});

	server.begin();
}

void loop()
{

}