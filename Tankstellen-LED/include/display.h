#include <base.h>

#define pinShiftLatch1 4
#define pinShiftLatch2 5
#define pinShiftLatch3 6
#define pinShiftLatch4 7
#define pinShiftData 8
#define pinShiftClock 3
#define pinShiftOutputEnable 2

class Display
{
public:
    void Startup();
    void AddBrightnessValue(uint16_t value);
    void Brightness();
    static uint8_t Representation(const char character);
    void SetOutput(const char *characters, bool showPoints);

private:
    uint8_t brightnessCount = 0;
    uint8_t brightnessSteps = 1;
    char currentOutput[4] = "";
    bool currentShowingPoints = false;
    uint16_t brightnessValues[20] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
};