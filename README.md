download MinGW Posix Seh MS...

curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py

python3 get-platformio.py

pio project init

"[env:d1_mini]
platform = espressif8266
board = d1_mini
framework = arduino" > platformio.ini

pio run -e d1_mini
pio run -t upload
pio test -e native





Step 1: Add the ESP8266 Package Index

    Locate or create the arduino-cli configuration file:

arduino-cli config init

This creates a configuration file at ~/.arduino15/arduino-cli.yaml (on Linux/Mac) or %UserProfile%\.arduino15\arduino-cli.yaml (on Windows).

Open the configuration file for editing:

nano ~/.arduino15/arduino-cli.yaml

Add the ESP8266 package URL under the board_manager.additional_urls section:

board_manager:
  additional_urls:
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json

Save and exit (Ctrl+O, Enter, Ctrl+X in nano).


arduino-cli core update-index
arduino-cli core install esp8266:esp8266
arduino-cli lib install "Encoder"
arduino-cli lib install "ezButton"
arduino-cli compile --fqbn esp8266:esp8266:d1_mini

