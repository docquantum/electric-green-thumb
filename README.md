# Electric Green Thumb
Green house automation using Ardunios and Espressive based systems (32/8266).

This was worked on at [CornHacks 2020](https://devpost.com/software/electric-green-thumb)

This version of the project (on the arduino branch) was built using an arduino and esp8266 with the compents listed in [Components.md](Components.md) which includes a photoresistor for light level, soil moisture sensor for the dryness of the plant soil, water level sensor for the level of the water in the resevoir, and a DHT11 temperature/humidity sensor to know the temp and humidity in the box. Two other components, both relays, were controling an led grow light and a 5v dc water pump.

The Arduino also talked to an esp8266 via software serial to do wifi via AT commands since a good wifi system wasn't available at the time. A better option would be to make the esp8266 the master and talk over serial to the arduino to get sensor data and control the relays. We also used an MQTT library to send and recieve data over MQTT. We used CloudMQTT as the broker.

The future of the project would incluce creating a web interface or stack that either had it's own MQTT broker to keep things standard, or to use something like Firebase directly using REST api to send and recieve data. The web interface would allow the user to control the water and light remotely, as well as set up thresholds for things like lighting time, min/max soil moisutre, etc, to have automation take over.
