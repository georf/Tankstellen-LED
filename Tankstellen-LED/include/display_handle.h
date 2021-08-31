#include <base.h>
#include <display.h>
#include <stop_watch.h>

#define pinBrightnessInput A2

enum Modus
{
    WAITING,
    RUNNING,
    SHOWING,
    PRE_SHOWING_1,
    PRE_SHOWING_2,
    SHOWING_1,
    SHOWING_2,
};

class DisplayHandle
{
public:
    void Startup();
    void Handle();
    void StopTime(uint8_t timeSelect, const char *characters);
    void Start();
    void StartOrStop();
    void Waiting();
    void Brightness();

private:
    char waitingLines[4][5] = {"-   ", " -  ", "  - ", "   -"};
    Modus modus;
    Modus modi[2];
    char times[2][CHARS] = {"", ""};
    Display display;
    StopWatch stopWatch;
    uint32_t lastModusChange;
    uint32_t lastBrightnessRead = 0;
    void Stop();
    void SetModus(Modus newModus);
    void PreShowing(uint8_t line, uint32_t sinceLastModusChange);
    void Showing(uint8_t line, uint32_t sinceLastModusChange, Modus nextModus);
};