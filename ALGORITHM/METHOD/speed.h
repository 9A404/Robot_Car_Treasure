#ifndef __SPEED_H_
#define __SPEED_H_
#include "sys.h"
#include "myconfig.h"

u8 Speed_downMethod(u16 time);
u8 Speed_commonMethod(u16 time);
u8 Take_up_time(u16 time);
u8 Speed_upRise(u16 time);
void getCurrentSpeed(findLine fl);
#endif

