# smartfield-firmware
Firmware for a smart garden plot, based on a HTCC-AB01 LoRa board.

## Hardware overview

 - Board: **CubeCell HTCC-AB01 ASR605x** (ARM Cortex M0+ & SX1262 LoRa)
   - [Documentation](https://heltec.org/project/htcc-ab01/)
   - [Arduino implementation](https://github.com/HelTecAutomation/CubeCell-Arduino)

 - Air temperature and humidity sensor: **DHT22**
    - [Documentation](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)
    - [Arduino library](https://platformio.org/lib/show/19/DHT%20sensor%20library)

 - Soil temperature and humidity sensor: **FS304-SHT31**
    - [Documentation](https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Datasheets/Sensirion_Humidity_Sensors_SHT3x_Datasheet_digital.pdf)
    - [Arduino library](https://platformio.org/lib/show/479/Adafruit%20SHT31%20Library)
## Development setup

Install **Visual Studio Code** and the **PlatformIO** extension.

Copy `include/NetworkConfiguration.h.example` to `include/NetworkConfiguration.h` and insert your [*The Things Network*](https://www.thethingsnetwork.org) configuration. 

Edit the `platformio.ini` file and change the `board_build.arduino.lorawan.region` to the correct frequency band for your country.

Attach a serial monitor and read the Device EUI after a reset. Then set the device EUI in the TTN console, use OTAA and MAC 1.0.2 .

Use the PlatformIO menu to compile and upload the code.