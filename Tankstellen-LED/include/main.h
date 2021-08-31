#include <base.h>
#include <display_handle.h>
#include <serial_control.h>
#include <button.h>

#define pinBtn1 11
#define pinBtn2 12

void cbStart();
void cbStartOrStop();
void cbWaiting();
void cbResult(uint32_t lastDeciTime, uint8_t lastLine);
