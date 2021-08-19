#include <base.h>

class Button
{
private:
    int lastValue;
    unsigned long lastDebounceTime;
    void (*pCallback)();

public:
    int pin;
    int state;
    bool pressed;
    void read();
    Button(int PIN, void (*pCallbackFunction)());
};
