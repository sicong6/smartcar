#ifndef _CONTROL_H_
#define _CONTROL_H_ 
#include "AllInclude.h"

#define BalancePeriod 5
#define SpeedPeriod 8

void ScheduleInit();
void GlobalControl();
void OutputSmooth();
#endif