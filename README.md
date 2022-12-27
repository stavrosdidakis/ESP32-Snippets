# ESP32-Snippets

A collection of code examples using **ESP32** (FireBeetle IoT) and other physical computing resources (i.e. neopixel, sensors, etc).

---
**01_FireBeetle_MQTT_send**

  This example demonstrates how to utilize an ESP32 (Firebeetle IoT) & MQTT (HiveMQ) for sending the value of a rotary encoder over the network. The messages are published on a specific topic within the MQTT broker and can be viewed by any connected MQTT client.

  Materials needed for this example:
  - [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html)
  - [Rotary Encoder](https://www.amazon.com/Maxmoral-Encoder-Degrees-Compatible-Development/dp/B07M631J1Q)
---

**02_FireBeetle_MQTT_receive**

  This example demonstrates how to utilize an ESP32 (Firebeetle IoT) & MQTT for receiving messages over the network, which are published on a specific topic. The code also shows how to connect and control a 16-LED Neopixel ring with the incoming message.

  Materials needed for this example:
  - [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html)
  - [16-LED Neopixel](https://www.adafruit.com/product/1463)

---
**03_FireBeetle_MQTT_send_and_receive**

This example demonstrates how to utilize an ESP32 (Firebeetle IoT) & MQTT (HiveMQ) for sending the value of a rotary encoder over the network and receiving it to control a 16-LED Neopixel. The messages are published on a specific topic within the MQTT broker and can be viewed by any connected MQTT client.
  Materials needed for this example:
  - [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html)
  - [Rotary Encoder](https://www.amazon.com/Maxmoral-Encoder-Degrees-Compatible-Development/dp/B07M631J1Q)
  - [16-LED Neopixel](https://www.adafruit.com/product/1463)

---
**04_FireBeetle_MQTT_receive_multiple_topics**

  This example demonstrates how to utilize an ESP32 (Firebeetle IoT) & MQTT (HiveMQ) for sending the value of a rotary encoder over the network and receiving it to control a 16-LED Neopixel. Here, we use multiple topics, to control different properties of the Neopixel that arrive on different MQTT topics. The messages are published on a specific topic within the MQTT broker and can be viewed by any connected MQTT client.
  Materials needed for this example:
  - [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html)
  - [Rotary Encoder](https://www.amazon.com/Maxmoral-Encoder-Degrees-Compatible-Development/dp/B07M631J1Q)
  - [16-LED Neopixel](https://www.adafruit.com/product/1463)

A helpful client utility is provided by HiveMQ here: http://www.hivemq.com/demos/websocket-client/

---
**05_FlexibleLED**

  This example demonstrates how to utilize an ESP32 (Firebeetle IoT) together with a flexible LED Matrix 7x71
  - [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html)
  - [Flexible LED](https://www.dfrobot.com/product-1992.html)

A helpful client utility is provided by HiveMQ here: http://www.hivemq.com/demos/websocket-client/

---
The examples were used in the course "Responsive Environments - Designing Interactive, Sentient, and Intelligent Spaces", at NYU Shanghai, Fall 2022
