//This example demonstrates how to utilize an ESP32 (Firebeetle IoT) & MQTT (HiveMQ)
//for sending the value of a rotary encoder over the network and receiving it to control
//a 16-LED Neopixel. Here, we use multiple topics, to control different properties of the Neopixel
//that arrive on different MQTT topics. The messages are published on a specific topic within the MQTT broker
//and can be viewed by any connected MQTT client.
//A helpful utility is provided by HiveMQ here: http://www.hivemq.com/demos/websocket-client/

//*********************************** Setup MQTT
//Import libraries needed for MQTT
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//Replace the next variables with your SSID (WiFi)/Password combination
const char* ssid = "xxx";
const char* password = "xxx";

//---- MQTT Broker settings
const char* mqtt_server = "xxx.s1.eu.hivemq.cloud"; //Cluster credentials with HiveMQ
const char* mqtt_username = "xxx";
const char* mqtt_password = "xxx";
const int mqtt_port = 8883;

WiFiClientSecure espClient;
PubSubClient client(espClient);

const char inTopic1[] =  "/RED/";   //The incoming topic
const char inTopic2[] =  "/GREEN/";   //The incoming topic
const char inTopic3[] =  "/BLUE/";   //The incoming topic

const char outTopic1[] = "/RED/";  //The outgoing topic
const char outTopic2[] = "/GREEN/";  //The outgoing topic
const char outTopic3[] = "/BLUE/";  //The outgoing topic

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

//################################### Rotary Encoder Settings
#define CLK 18
#define DT 14
#define SW D3
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;
//###################################

///////////////////////////////////// Adafruit Neopixel Settings
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN   D2
#define LED_COUNT 48
Adafruit_NeoPixel leds(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t col;
/////////////////////////////////////

//This variable will store the incoming values from the MQTT broker
int valueFromMQTTred = 255;
int valueFromMQTTgreen = 0;
int valueFromMQTTblue = 255;

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

  //Set encoder inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  //Settings for the LED pixels
  leds.begin();           // INITIALIZE NeoPixel leds object (REQUIRED)
  leds.show();            // Turn OFF all pixels ASAP
  leds.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  //Set a purple color for the LEDs
  col = leds.Color(valueFromMQTTred, valueFromMQTTgreen, valueFromMQTTblue);
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
  delay(1000);
  WiFi.disconnect();
  delay(1000);
  WiFi.begin(ssid, password);
  delay(1000);

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

  rotEnc();

  //Our routine for controlling the LED ring
  //In this instance, we use the valueFromMQTT variable (defined in callback)
  leds.clear();

  col = leds.Color(valueFromMQTTred, valueFromMQTTgreen, valueFromMQTTblue);
  for (int i = 0; i < LED_COUNT; i++) {
    leds.setPixelColor(i, col);
  }
  leds.show();
}

//Function responsible for getting the rotary encoder input (counter & button)
void rotEnc() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter -= 10;
      currentDir = "CCW";
    } else {
      // Encoder is rotating CW so increment
      counter += 10;
      currentDir = "CW";
    }

    //This function ensures that the counter always remains
    //in a range between 0 and 255
    counter = constrain(counter, 0, 255);

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);

    //**********************************************
    //MQTT message function executes
    publishMessage(outTopic1,String(counter),false);
    publishMessage(outTopic2,String(counter),false);
    publishMessage(outTopic3,String(counter),false);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");

      //**********************************************
      //MQTT message function executes
      //publishMessage(outTopic,String(counter),true);
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
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
      client.subscribe(inTopic1);   // subscribe the topics here
      client.subscribe(inTopic2);
      client.subscribe(inTopic3);
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
  if (client.publish(topic, payload.c_str(), true))
  Serial.println("Message published ["+String(topic)+"]: "+payload);
}

//Callback function - get messages from MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic,"/RED/")==0){
      //Get the characters of the payload message
    char* getValue;
    getValue = (char*) malloc(length + 1);
    memcpy(getValue, payload, length);
    getValue[length] = '\0';

    //Conversion to String
    String getValueStr = (String) getValue;

    //Conversion to Int
    int getValueInt = getValueStr.toInt();
    Serial.println("Message arrived ["+String(topic)+"]: "+getValueInt);

    //Assign value to a global variable
    valueFromMQTTred = getValueInt;
  }

  if (strcmp(topic,"/GREEN/")==0){
      //Get the characters of the payload message
    char* getValue;
    getValue = (char*) malloc(length + 1);
    memcpy(getValue, payload, length);
    getValue[length] = '\0';

    //Conversion to String
    String getValueStr = (String) getValue;

    //Conversion to Int
    int getValueInt = getValueStr.toInt();
    Serial.println("Message arrived ["+String(topic)+"]: "+getValueInt);

    //Assign value to a global variable
    valueFromMQTTgreen = getValueInt;
  }

  if (strcmp(topic,"/BLUE/")==0){
      //Get the characters of the payload message
    char* getValue;
    getValue = (char*) malloc(length + 1);
    memcpy(getValue, payload, length);
    getValue[length] = '\0';

    //Conversion to String
    String getValueStr = (String) getValue;

    //Conversion to Int
    int getValueInt = getValueStr.toInt();
    Serial.println("Message arrived ["+String(topic)+"]: "+getValueInt);

    //Assign value to a global variable
    valueFromMQTTblue = getValueInt;
  }
}
