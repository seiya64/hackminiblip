// miniblip led knight rider demo

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

void generate(neopixel::Pixel * out, uint32_t index, uintptr_t extra)
{
    uint32_t brightness = (index + extra) % 5;
    out->green = (brightness >= 2) ? brightness * 10 * (0xFF / 30) : 0;
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
    bool rightToLeft = true;
    while (1) {
        if (offset == 2){
            rightToLeft = false;
        }
        if (offset == 0){
            rightToLeft = true;
        }
        if (rightToLeft){
            offset++;
        }
        else{
            offset--;
        }
        array.update(generate, 5, offset);
        wait_ms(250);
    }
}

