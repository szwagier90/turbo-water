#!/bin/bash
set -e

arduino-cli compile --fqbn esp8266:esp8266:d1_mini
arduino-cli.exe upload -p COM3 --fqbn esp8266:esp8266:d1_mini:baud=921600
