# Electric Green Thumb
Green house automation using Ardunios and Raspberry Pi's


Just an idea currently, something I wish to accomplish this coming summer.


Initially, it would use a portable green house with multiple shelves that typically supports small plant growth. Using this greenhouse, I would be able to use small plastic tubing with small holes poked through to allow for watering of the plants. Small electrically controlled valves would be on at the base of every shelf to allow for per-shelf control of water. On every shelf there would also be LED plant growth light bulbs, also individually controlled per-shelf. The unit as a whole would have a humidity and temperature sensor. Every shelf would have a plethora of soil sensors that could function as acidity, mineral, or water sensors to help know those things about the plants on the shelves. The project would require multiple Arduino's to manage and control the light and watering mechanisms, as well as receive data from the sensors. A single Arduino might be able to handle most of the sensors and data given a mux, but it would be easier and more modular to have the Arduinos control their individual sensor groupings and have a master Raspberry Pi (RPi), with WiFi, use the data from the Arduinos to control the system. The RPi could then present a webpage with graphs and visualizations to show history of the greenhouse and operations. Eventually, camera systems could be added to also allow for remote viewing of the plants themselves.


Given I love opensource, I will document and release the code as I create it with schematics of wiring and pictures of the build. Pull requests and bug reports will be welcome, just try to follow my format.

As I'm sure this is something that's been worked on and is being worked on in many respects by others in the community, this is more a learning experience in sensor networks and embeded systems for myself, but I do wish it will benefit the community in some form or fashion.
