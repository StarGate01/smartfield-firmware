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

### Payload Formatter

```javascript
function decodeInt16(bytes, offset)
{
  return (((bytes[offset + 1] & 0xFF) << 8) | (bytes[offset] & 0xFF));
}

function decodeFloat32(bytes, offset)
{
  var d = new DataView(new ArrayBuffer(4));
  for(var i=0; i<4; i++) d.setUint8(i, bytes[offset + i]);
  return d.getFloat32(0, true);
}

function decodeUplink(input) 
{
  return {
    data: {
      bytes: input.bytes,
      id: input.bytes[0],
      battery: decodeInt16(input.bytes, 1),
      temperature: decodeFloat32(input.bytes, 3),
      humidity: decodeFloat32(input.bytes, 7),
      soilTemperature: decodeFloat32(input.bytes, 11),
      soilHumidity: decodeFloat32(input.bytes, 15)
    },
    warnings: [],
    errors: []
  };
}
```
