/**
 * @file main.cpp
 * @author Christoph Honal
 * @brief Provides the core logic
 * @version 0.1
 * @date 2021-04-12
 */

#include "LoRaWanMinimal_APP.h" // LoRa WAN

#include <Arduino.h>
#include "HardwareConfiguration.h"
#include "NetworkConfiguration.h"
#include "LowPower.h" // Sleep mode
#include "CubeCell_NeoPixel.h" // RGB LED



// Auxiliary hardware drivers
CubeCell_NeoPixel rgbLED(1, RGB, NEO_GRB + NEO_KHZ800);

// LoRo network configuration buffers
// These symbols are required by the LoraWan libraray
static uint8_t ttn_device_eui[8];
static uint8_t ttn_app_eui[] = TTN_APP_EUI;
static uint8_t ttn_app_key[] = TTN_APP_KEY;

// This symbol is referenced and required by the LoRa WAN library
// Allow channels 0-255; e.g. EU868 uses 1-9 only, CN470 uses 0-95 and so on
uint16_t userChannelsMask[6] = { 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

// Lora packet structure definition and buffer allocation
// Force packed memory alignment to enable pointer cast to buffer
struct __attribute__ ((packed)) lora_packet_t 
{ 
    uint8_t id; 
    int16_t battery; 
} static packet;


// Core logic


void setup() 
{
    // Serial
    Serial.begin(115200);

    // Enable 3.3V auxiliary power output
    pinMode(Vext, OUTPUT);
    digitalWrite(Vext, LOW); 

    // Initialize RGB LED
    rgbLED.begin();
    rgbLED.clear();
    rgbLED.setPixelColor(0, rgbLED.Color(100, 100, 0)); // yellow
    rgbLED.show();

    // Generate LoRa EUI from chip ID
    uint64_t chipID = getID();
	for(int i = 7; i >= 0; i--) ttn_device_eui[i] = (chipID >> (8 * (7 - i))) & 0xFF;
    Serial.print("Device EUI: ");
    for(int i = 0; i < 8; i++) 
    {
        Serial.print(ttn_app_eui[i], HEX); 
        Serial.print(" ");
    }
    Serial.print("\n");

    // Setup and connect to Lora network
    LoRaWAN.begin(LORAWAN_CLASS, ACTIVE_REGION);

    // Enable adaptive data rate
    LoRaWAN.setAdaptiveDR(true);

    // Loop until joined
    while (true) 
    {
        Serial.print("Joining Network... ");

        // Join TTN using OTAA
        LoRaWAN.joinOTAA(ttn_app_eui, ttn_app_key, ttn_device_eui);

        if (!LoRaWAN.isJoined()) 
        {
            Serial.println("Joining failed, retrying in 10 s");
            rgbLED.setPixelColor(0, rgbLED.Color(100, 0, 0)); // red
            rgbLED.show();
            lowPowerSleep(10000);
        } 
        else 
        {
            Serial.println("Joined successfully");
            rgbLED.setPixelColor(0, rgbLED.Color(0, 100, 0)); // green
            rgbLED.show();
            break;
        }
    }
}

void loop() 
{
    // Read battery voltage
    packet.battery = getBatteryVoltage();

    Serial.printf("Sending packet with id=%d, battery=%d\n", 
        packet.id, 
        packet.battery);

    // Send packet, Require acknowledgment only for the first 5 packets to conform to fair use policy
    if (LoRaWAN.send(sizeof(lora_packet_t), (uint8_t*)(&packet), 1, packet.id < 5)) 
    {
        Serial.println("Send successful");
    } 
    else 
    {
        Serial.println("Send failed");
    }
    packet.id++;

    // Sleep for 15 s
    lowPowerSleep(15000);
}

// This function is referenced and required by the LoRa WAN library
void downLinkDataHandle(McpsIndication_t *mcpsIndication)
{
    rgbLED.setPixelColor(0, rgbLED.Color(0, 0, 100)); // blue
    rgbLED.show();

    // Print packet meta info
    Serial.printf("Received downlink: %s, RXSIZE %d, PORT %d, DATA: ",
        mcpsIndication->RxSlot ? "RXWIN2":"RXWIN1",
        mcpsIndication->BufferSize,
        mcpsIndication->Port);

    // Print packet data
    for(uint8_t i = 0;i < mcpsIndication->BufferSize; i++) 
    {
        Serial.printf("%02X", mcpsIndication->Buffer[i]);
    }
    Serial.println();

    lowPowerSleep(200);
    rgbLED.setPixelColor(0, rgbLED.Color(0, 100, 0)); // back to green
    rgbLED.show();
}