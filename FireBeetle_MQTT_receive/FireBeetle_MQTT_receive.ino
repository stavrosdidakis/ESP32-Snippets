//This example demonstrates how to utilize FireBeetle & MQTT
//for receiving messages over the network, which are published
//on a specific topic.

//*********************************** Setup MQTT
//Import libraries needed for MQTT
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//Replace the next variables with your SSID (WiFi)/Password combination
const char* ssid = "GalaxyS20";     // "GalaxyS20"  | "nyushanghai-iot" 
const char* password = "kaik3445";  // "kaik3445"   | ""

//---- MQTT Broker settings
const char* mqtt_server = "b69080e9018d4acfbd1949753ae15101.s1.eu.hivemq.cloud";
const char* mqtt_username = "stv01";
const char* mqtt_password = "stvddk01";
const int mqtt_port = 8883;

WiFiClientSecure espClient;
PubSubClient client(espClient);

const char inTopic[] =  "/MQTT-14/";   //The incoming topic

//This certificate is used for authenticating with HiveMQ
static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";
//***********************************

///////////////////////////////////// Adafruit Neopixel Settings
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN   D2
#define LED_COUNT 16
Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t col;
/////////////////////////////////////

//This variable will store the incoming values from the MQTT broker
int valueFromMQTT;

//Setup function
void setup() {
  //Begin a serial communication
  Serial.begin(9600);

  //Function responsible for the WiFi connection, setting the MQTT server,
  //and defining the callback
  setup_wifi();
  while (!Serial) delay(1);
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  //Settings for the LED pixels
  leds.begin();           // INITIALIZE NeoPixel leds object (REQUIRED)
  leds.show();            // Turn OFF all pixels ASAP
  leds.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  //Set a purple color for the LEDs on start
  col = leds.Color(255,   0,   255);
}

//Function responsible for the WiFi connection
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Main program loop
void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  
  //Our routine for controlling the LED ring
  //In this instance, we use the valueFromMQTT variable (defined in callback)
  //Since the receiving value is from 0 to 16 (as assigned in the
  //rotEnc() function), we use this number to control the number of open LEDs
  leds.clear();
  for (int i = 0; i < valueFromMQTT; i++) {
    leds.setPixelColor(i, col);
  }
  leds.show();
}

//Function that takes care of reconnection, if the connection drops
void reconnect() {
  // Loop until we’re reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    String clientId = "FireBeetle-"; // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(inTopic);   // subscribe the topics here
      //client.subscribe(sensor2_topic);   // subscribe the topics here
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//Function that published the message on MQTT
void publishMessage(const char* topic, String payload , boolean retained){
  //...
}

//Callback function - get messages from MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  /*
  String incomingMessage = "";
  for (int i = 0; i < length; i++){
    incomingMessage+=(char)payload[i];
  }
  Serial.println("Message arrived ["+String(topic)+"]: "+incomingMessage);
  */

  //Get the characters of the payload message
  char* getValue;
  getValue = (char*) malloc(length + 1);
  memcpy(getValue, payload, length);
  getValue[length] = '\0';

  //Conversion to String
  String getValueStr = (String) getValue;

  //Conversion to Float
  //float getValueFloat = getValueStr.toFloat();

  //Conversion to Int
  int getValueInt = getValueStr.toInt();
  Serial.println("Message arrived ["+String(topic)+"]: "+getValueInt);

  //Assign value to a global variable
  //Since the receiving value is from 0 to 16 (as assigned in the
  //rotEnc() function), we use this number to control the number of open LEDs
  valueFromMQTT = getValueInt;
  //col = leds.Color(random(255), random(255), random(255));
}
