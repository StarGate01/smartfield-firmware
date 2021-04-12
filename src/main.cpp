/**
 * @file main.cpp
 * @author Christoph Honal
 * @brief Provides the core logic
 * @version 0.1
 * @date 2021-04-12
 */


#include <Arduino.h>
#include "HardwareConfiguration.h"

#include "CubeCell_NeoPixel.h" // For RGB LED


// Auxiliary hardware drivers
CubeCell_NeoPixel rgbLED(1, RGB, NEO_GRB + NEO_KHZ800);


void setup() 
{
    // Enable 3.3V auxiliary power output
    pinMode(Vext, OUTPUT);
    digitalWrite(Vext, LOW); 

    // Initialize RGB LED
    rgbLED.begin();
    rgbLED.clear();
}


void loop() 
{
    // Cycle though colors
    for(uint8_t i = 0; i <= 3; i++)
    {
        for(uint8_t j = 0; j <= 3; j++)
        {
            for(uint8_t k = 0; k <= 3; k++)
            {
                rgbLED.setPixelColor(0, rgbLED.Color(i * 50, j * 50, k * 50));
                rgbLED.show();
                delay(50); 
            }
        }
    }
    
}