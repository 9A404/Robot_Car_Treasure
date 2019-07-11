#ifndef _LED_H_
#define _LED_H_

#include "myconfig.h"

#define LED0 PEout(2)		// PE2
#define LED1 PEout(3)		// PE3	
#define LED2 PEout(4)		// PE4
#define BEEP PEout(14)	// PE14


void ledInit(void);     //led��ʼ��
void led_light(u8 n);   //����led
void buzzerInit(void);  //��������ʼ��
void buzzer_beep(void); //����������
void led_flash(void);       //led��˸


#endif



