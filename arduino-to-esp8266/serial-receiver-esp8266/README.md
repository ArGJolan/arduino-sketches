# Serial receiver for ESP8266

From https://www.youtube.com/watch?v=ji71cHaGW8w and adapted to make it happen the other way around.

## TL;DR

Same wiring as the video except:
- On Arduino side: Move "Digital 2 & 3" to "TX & RX"
- On ESP8266 side: Connect Arduino's TX to "GPIO 2" & Arduino's RX to "GPIO 0"

Send stuff from arduino and profit from 2€ wifi project.

