#ifndef __PHOTOELECTRIC_H_
#define __PHOTOELECTRIC_H_

#include "Timer.h"

#define PES_L  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define PES_R  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define PES_H  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)
#define PES_Platform  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)

void pesInit(void);
void pesLSwitch(SWITCHState newState);
u8 PES_platform_Shake(void);


#endif














