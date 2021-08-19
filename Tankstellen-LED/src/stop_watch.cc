#include <stop_watch.h>

void StopWatch::Start()
{
  time = 0;
  lastCentiSecond = millis();
}

boolean StopWatch::HasUpdate()
{
  unsigned long newCentiSecond = millis();
  if (newCentiSecond >= lastCentiSecond + 10)
  {
    lastCentiSecond = newCentiSecond;
    time++;
    return true;
  };
  return false;
}

void StopWatch::Output(char *output)
{
  CentiSecondsToChars(time, output);
}

void StopWatch::CentiSecondsToChars(uint32_t centiSeconds, char *output)
{
  output[0] = 48 + (centiSeconds / 1000 % 10);
  output[1] = 48 + (centiSeconds / 100 % 10);
  output[2] = 48 + (centiSeconds / 10 % 10);
  output[3] = 48 + (centiSeconds % 10);
}
