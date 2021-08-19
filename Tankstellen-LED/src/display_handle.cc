#include <display_handle.h>

void DisplayHandle::Startup()
{
    pinMode(pinBrightnessInput, INPUT);
    display.Startup();
    Waiting();
}

void DisplayHandle::Handle()
{
    char output[CHARS];
    uint32_t sinceLastModusChange = millis() - lastModusChange;
    uint8_t index;
    switch (modus)
    {
    case WAITING:
        index = sinceLastModusChange % 1000 / 250;
        display.SetOutput(waitingLines[index], false);
        if (index > 0)
            display.AddBrightnessValue(analogRead(pinBrightnessInput));
        break;

    case RUNNING:
        if (!stopWatch.HasUpdate())
            return;

        stopWatch.Output(output);
        display.SetOutput(output, true);
        break;

    case PRE_SHOWING_1:
        stopWatch.HasUpdate();
        PreShowing(0, sinceLastModusChange);
        break;

    case PRE_SHOWING_2:
        stopWatch.HasUpdate();
        PreShowing(1, sinceLastModusChange);
        break;
        break;

    case SHOWING_1:
        Showing(0, sinceLastModusChange, SHOWING_2);
        break;

    case SHOWING_2:
        Showing(1, sinceLastModusChange, SHOWING_1);
        break;

    case SHOWING:
        break;
    }
}

void DisplayHandle::Showing(uint8_t line, uint32_t sinceLastModusChange, Modus nextModus)
{
    if (sinceLastModusChange < 800)
        display.SetOutput(line == 0 ? "-1- " : "-2- ", false);
    else if (sinceLastModusChange < 5800)
        display.SetOutput(times[line], true);
    else
        SetModus(nextModus);
}

void DisplayHandle::PreShowing(uint8_t line, uint32_t sinceLastModusChange)
{
    if (sinceLastModusChange < 800)
        display.SetOutput(line == 0 ? "-1- " : "-2- ", false);
    else if (sinceLastModusChange < 2800)
        display.SetOutput(times[line], true);
    else
        SetModus(RUNNING);
}

void DisplayHandle::StartOrStop()
{
    if (modus == WAITING)
        Start();
    else
        Stop();
}

void DisplayHandle::Stop()
{
    char output[CHARS];
    for (uint8_t i = 0; i < 2; i++)
    {
        if (modi[i] == RUNNING)
        {
            stopWatch.Output(output);
            StopTime(i, output);
            return;
        }
    }
}

void DisplayHandle::StopTime(uint8_t timeSelect, const char *characters)
{
    modi[timeSelect] = SHOWING;
    Modus other = modi[(timeSelect + 1) % 2];
    if (other == RUNNING)
    {
        SetModus(timeSelect == 0 ? PRE_SHOWING_1 : PRE_SHOWING_2);
    }
    else
    {
        SetModus(SHOWING_1);
    }

    for (uint8_t charNumber = 0; charNumber < CHARS; charNumber++)
    {
        times[timeSelect][charNumber] = characters[charNumber];
    }
}

void DisplayHandle::Start()
{

    stopWatch.Start();
    SetModus(RUNNING);
    modi[0] = RUNNING;
    modi[1] = RUNNING;
    display.SetOutput(empty, false);
}

void DisplayHandle::Waiting()
{
    SetModus(WAITING);
    modi[0] = WAITING;
    modi[1] = WAITING;
}

void DisplayHandle::Brightness()
{
    display.Brightness();
}

void DisplayHandle::SetModus(Modus newModus)
{
    modus = newModus;
    lastModusChange = millis();
}
