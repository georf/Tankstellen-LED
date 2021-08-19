#include <base.h>

#define MODE_READY 0
#define MODE_CONTROL 1
#define MODE_TIME 2
#define MODE_TIME_END 3

#define MODE_CHAR_WAIT 'w'
#define MODE_CHAR_START 's'
#define MODE_CHAR_1 '1'   // "1-0:18,03"
#define MODE_CHAR_2 '2'   // "2-0:22,04"
#define MODE_CHAR_END '#' // "#0:18,030|0:22,040\*"
#define NEXT_LINE '\n'

class SerialControl
{
public:
    void Handle();
    uint8_t LastLine();
    char *LastCharTime();
    uint32_t LastDeciTime();
    SerialControl(void (*pCallbackStartF)(), void (*pCallbackWaitF)(), void (*pCallbackShowF)(SerialControl *));
    void Startup();

private:
    uint8_t transmitMode = MODE_READY;
    char receivedTime[2][5];
    uint8_t receivedPart;
    uint8_t receivedTimePosition;
    void (*pCallbackStart)();
    void (*pCallbackWait)();
    void (*pCallbackShow)(SerialControl *);
};
