# smartfield-firmware
Firmware for a smart garden plot, based on a HTCC-AB01 LoRa board.

## Hardware overview

 - Board: **CubeCell HTCC-AB01 ASR605x** (ARM Cortex M0+ & SX1262 LoRa)
   - Documentation: https://heltec.org/project/htcc-ab01/
   - Arduino implementation: https://github.com/HelTecAutomation/CubeCell-Arduino
   - Purchase: https://www.amazon.de/gp/product/B07ZH7NL38?psc=1

## Development setup

Install **Visual Studio Code** and the **PlatformIO** extension.

Copy `include/NetworkConfiguration.h.example` to `include/NetworkConfiguration.h` and insert your [*The Things Network*](https://www.thethingsnetwork.org) configuration. 

Edit the `platformio.ini` file and change the `board_build.arduino.lorawan.region` to the correct frequency band for your country.

Use the PlatformIO menu to compile and upload the code.