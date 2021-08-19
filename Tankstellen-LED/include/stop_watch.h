#include <base.h>

class StopWatch
{
public:
    void Start();
    boolean HasUpdate();
    void Output(char *output);
    static void CentiSecondsToChars(uint32_t centiSeconds, char *output);

private:
    uint16_t time;
    unsigned long lastCentiSecond;
};
