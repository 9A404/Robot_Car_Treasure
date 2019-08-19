#ifndef _CARPARK_H_
#define _CARPARK_H_
#include "sys.h"
#include "myconfig.h"

u8 parkMethod_default(void);
u8 parkMethod_pesR(void);
u8 parkMethod_pesL(void);
u8 parkMethod_pesL_Delay(int time);
u8 parkMethod_pesR_Delay(int time);
u8 parkMethod_pesPlatform(controlCenterTypeDef *controlp);

#endif





