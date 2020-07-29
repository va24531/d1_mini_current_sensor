# d1_mini_current_sensor
D1 Mini Current Sensor via HTTP


Arduino sketch for ESP8266's (Including D1 Mini's) using a DFRobot 10 Amp AC Current sensor (https://www.dfrobot.com/product-1919.html). Will work with higher and
lower amperage sensors by changing the values in the sketch.

Sketch takes advantage of the ESP's ability for wifi setup after compile. Assigns IP Address via DHCP, and will report CSV values via browser.

Ie: A,4.87,W,584.00,*

Above shows (Amps) at 4.87 and (Watts) at 584.00, followed by a * showing completed sentence. No further data is returned.

Current sensor is powered by 3.3vDC, and the ESP's A0 (Analog sensor) picks up the current preportional output voltage as outputted from the sensor. No further
connections (Besides power) are needed.

Can be easily read by Node-Red flow, also provided for example, however any language that can parse a CSV HTTP sentence can handle this data with ease.
IP address of target device will need to be changed in Node-Red for TCP Connection (192.168.0.112 currently) to match your setup.

ESP8266mdns does work with Node-MCU versions of the board, will test on Di mimi's in the future and will empliment into the code in the future, allowing Node-Red to
use a device name to connect to instead of a IP address.
