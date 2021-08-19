#include <main.h>

DisplayHandle displayHandle;
SerialControl serialControl = SerialControl(&cbStart, &cbWaiting, &cbResult);
Button btn1 = Button(pinBtn1, &cbStartOrStop);
Button btn2 = Button(pinBtn2, &cbWaiting);

void setup()
{
  noInterrupts();

  //set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0;  //initialize counter value to 0
  // set compare match register for 1hz increments
  // OCR1A = 15624; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  OCR1A = 14; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // // set compare match register for 1000hz increments
  // OCR1A = 14; // = (16*10^6) / (1000*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();

  displayHandle.Startup();
  serialControl.Startup();
}

ISR(TIMER1_COMPA_vect)
{
  displayHandle.Brightness();
}

void loop()
{
  btn1.read();
  btn2.read();
  serialControl.Handle();
  displayHandle.Handle();
}

void cbResult(SerialControl *control)
{
  char output[CHARS];
  StopWatch::CentiSecondsToChars(control->LastDeciTime(), output);
  displayHandle.StopTime(control->LastLine(), output);
}

void cbStart()
{
  displayHandle.Start();
}

void cbStartOrStop()
{
  displayHandle.StartOrStop();
}

void cbWaiting()
{
  displayHandle.Waiting();
}
