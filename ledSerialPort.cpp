// miniblip turn on led sending command through tty

#include "mbed.h"
#include "neopixel.h"
#include "USBSerial.h"

// Matrix led output pin
#define DATA_PIN P0_9

USBSerial serial;

void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{
    if (index == 0 && extra == 1){
        out->red = 0xFF;
        out->green = 0;
        out->blue = 0;
    }
    else{
        out->red = 0;
        out->green = 0;
        out->blue = 0;
    }
}

int main()
{
    // Turn off miniblip buzzer
    PwmOut speaker(P0_8);
    speaker=0.0;
    
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    neopixel::PixelArray array(DATA_PIN);

    uint32_t offset = 0;
    uint32_t errorCode = 500;
    char readBuffer[20];
    while (1) {
        errorCode = serial.scanf("%s", readBuffer);
        serial.printf("errorCode: %i\n", errorCode);
        if (errorCode == 1){
            serial.printf("readBuffer: ++%s++\n", readBuffer);
            if (strcmp(readBuffer,"on")==0){
                offset = 1;
            }
            else {
                offset = 0;
            }
        }
        serial.printf("offset: %i\n\n", offset);
        array.update(generate, 25, offset);
        wait_ms(250);
    }
}

