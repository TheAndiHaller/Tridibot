# Tridibot

Tridibot is an open source robot, originally created for educational purposes. You can download the code to build your own Tridibot from this repository. 

You can find the 3D design here https://www.thingiverse.com/thing:3050870

## How to:

First of all, you will need to install the Arduino IDE (if you don’t have it already). You can download it from here: https://www.arduino.cc/en/Main/Software

After that you have to add support for ESP8266 chip to the Arduino environment.

- Open Arduino and go to Preferences.
- Enter http://arduino.esp8266.com/stable/package_esp8266com_index.json into Additional Board Manager URLs field.
- Go to Boards Manager from Tools > Board menu and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

You can find more information here https://github.com/esp8266/Arduino 

The next step is to download the tool to upload files to the ESP file system. We recommend you to use ESP8266FS.

- Download the tool from https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.3.0/ESP8266FS-0.3.0.zip.  (Check for the updated version on the link below)
- In your Arduino sketchbook directory, create tools directory if it doesn't exist yet
- Unpack the tool into tools directory (the path will look like <home_dir>/Arduino/tools/ESP8266FS/tool/esp8266fs.jar)
- Restart Arduino IDE

The official project Doc: https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst 


#### Now we need to download some libraries:

1)	**ArduinoWebSockets** library by Links2004. Download it from https://github.com/Links2004/arduinoWebSockets  
2)	**ArduinoJson**, by bblanchon, https://github.com/bblanchon/ArduinoJson 

To install the libraries go to Sketch > Include Library > Add .ZIP Library and select the downloaded zip file. 


