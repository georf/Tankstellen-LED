#include <display.h>

void Display::Startup()
{
    pinMode(pinShiftLatch1, OUTPUT);
    digitalWrite(pinShiftLatch1, LOW);
    pinMode(pinShiftLatch2, OUTPUT);
    digitalWrite(pinShiftLatch2, LOW);
    pinMode(pinShiftLatch3, OUTPUT);
    digitalWrite(pinShiftLatch3, LOW);
    pinMode(pinShiftLatch4, OUTPUT);
    digitalWrite(pinShiftLatch4, LOW);
    pinMode(pinShiftData, OUTPUT);
    digitalWrite(pinShiftData, LOW);
    pinMode(pinShiftClock, OUTPUT);
    digitalWrite(pinShiftClock, LOW);
    pinMode(pinShiftOutputEnable, OUTPUT);
    digitalWrite(pinShiftOutputEnable, LOW);

    SetOutput(empty, false);
}

void Display::AddBrightnessValue(uint16_t value)
{
    uint32_t sum = 0;
    uint16_t average;
    brightnessValues[millis() % 1000 / 50] = value;
    for (uint8_t index = 0; index < 20; index++)
        sum += brightnessValues[index];
    average = sum / 20;
    if (average > 600)
        average = 600;
    brightnessSteps = average / 61 + 1;
}

void Display::Brightness()
{
    brightnessCount++;
    digitalWrite(pinShiftOutputEnable, brightnessCount % brightnessSteps == 0);
}

uint8_t Display::Representation(char character)
{
    //   - a -
    // |       |
    // b       c
    // |       |
    //   - d -
    // |       |
    // e       f
    // |       |
    //   - g -
    //
    // h ==> point

    switch (character)
    {
    //         0bacfgebdh;
    case '0':
        return 0b00111111;
    case '1':
        return 0b00000110;
    case '2':
        return 0b01011011;
    case '3':
        return 0b01001111;
    case '4':
        return 0b01100110;
    case '5':
        return 0b01101101;
    case '6':
        return 0b01111101;
    case '7':
        return 0b00000111;
    case '8':
        return 0b01111111;
    case '9':
        return 0b01101111;
    case '-':
        return 0b01000000;
    case 'b':
        return 0b01111100;
    case 'o':
        return 0b01011100;
    case 't':
        return 0b01111000;
    default:
        return 0;
    }
}

void Display::SetOutput(const char *characters, bool showPoints)
{
    uint8_t points = 0;
    uint8_t latch;
    bool changed = false;

    if (showPoints)
        points = 0b10000000;

    for (uint8_t i = 0; i < 4; i++)
    {
        latch = pinShiftLatch1 + i;

        // change leds only if changed
        if (currentOutput[i] != characters[i] || currentShowingPoints != showPoints)
        {
            changed = true;
            // prepare shift registers
            digitalWrite(latch, HIGH);
            shiftOut(pinShiftData, pinShiftClock, MSBFIRST, Display::Representation(characters[i]) | points);
            // output shift registers
            digitalWrite(latch, LOW);
        }
        currentOutput[i] = characters[i];
    }
    currentShowingPoints = showPoints;

    if (changed)
    {
        // Serial.print(characters[0]);
        // Serial.print(characters[1]);
        // Serial.print(showPoints ? ":" : " ");
        // Serial.print(characters[2]);
        // Serial.print(characters[3]);
        // Serial.print("\n");
    }
}
