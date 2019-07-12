#ifndef  _MY_CONFIG_H_
#define  _MY_CONFIG_H_


#include "sys.h"
#include "delay.h"
#include "timer.h"
#include "pwm.h"
#include "usart.h"
#include "pid.h"
#include "usart3.h"
#include "control.h"
#include "findline.h"
#include "roadblock.h"
#include "speed.h"
#include "rotangle.h"
#include "seeknodeway.h"
#include "carpark.h"
#include "adc.h"
#include "mpu6050.h"
#include "key.h"
#include "pes.h"
#include "led.h"
#include "string.h"
#include "GUI.h"
#include "Lcd_Driver.h"
#include "myGUI.h"
#include "danger.h"
#include "Treasure.h"

/*蓝牙调试*/
//#define BlueTooth_Debug

/*LED调试*/
#define LED_Debug

/*慢速巡线*/
//#define Slow_FL

/*快速巡线*/
#define Fast_FL

#define BlueTooth

#define AUTO_Treasure

#define _NEW_MPU6050_//新版陀螺仪

#define max(a,b)			(a>b ? a:b)
#define min(a,b)			(a<b ? a:b)
#define limit(x,a,b)	(min(max(x,a) , b))	

#define NUM_OF_SENSOR 	12					//传感器个数
#define USART3_MAX_SEND_LEN 200		 // 发送缓存大小

#define LEFT 0
#define RIGHT 1

#define DEFAULT_SPEED 3300
#define SLOW_SPEED 2200
#define QUICK_SPEED 6500
extern unsigned short glsensor_ad_value[NUM_OF_SENSOR];       //传感器模拟量数组
extern unsigned short glsensor_dig_value;									    //传感器数字量数组
extern unsigned char 	USART3_TX_BUF[USART3_MAX_SEND_LEN];     //串口3发送缓存

/********************************传感器阈值******************************************************************/
extern const unsigned short int  basic_sensorThreshold[NUM_OF_SENSOR]; //传感器阈值
extern const  u16  brige_sensorThreshold[NUM_OF_SENSOR];//过桥阈值

/*******************************常量表*******************************************************************/
extern const map_linkInforTypeDef mapInformation[][NODEFORKNUM]; //地图信息数字化表
extern const rankTypeDef rankInformation_FL[22];                   //巡线分级表


extern u8 RunMethod_Check;  //检查你所选路线是跑到哪一个平台(用于寻宝切换路线) 
extern u8 QR_code_flag;  
extern u8 treasure_flag;
extern float glPitchbuff[2];
extern u8 QR_code[2];
extern float gldif_Pitch;
extern u8 mpu6050_flag;
extern u8 U_Dswitch;                                //上下台控制开关 1代表上台，2代表下台
extern float gldYaw;																//储存偏航角PID输出
extern float glPitch,glRoll,glYaw;							  //欧拉角
extern float glsetYaw;																		//储存设定的偏航角
extern int gldSpeed;															//储存速度PID输出
extern u8 findLineFlag;														//巡线方法初始化标志位
extern u8 rotAngleFlag;                         //旋转方法初始化标志位
extern u8  USART1_RX_BUF[66];//串口1 DMA缓存区
extern u8 key0_Flag;																//按键0标志位
extern u16 gl_time;														 		 //定时器3标志
extern u8 runTimes;																//记录奔跑次数
extern float angle_read;			//记录第一个翘板转弯的角度
extern float angle_read_back;		//记录第二个翘板转弯的角度
extern u8 angle_flag;
extern float glsensor_angle;
extern u8 Treasure_all_Flag;		//不切路线的标志位
/********************************逻辑层控制器**************************************************/
extern PIDTypeDef glsensorPID;										//定义一个传感器PID调节器
extern PIDTypeDef glrotAnglePID;									//定义一个转角PID调节器
extern motorSpeedTypeDef glmotorSpeed;				  	//定义一个速度记录器
//extern rankTypeDef glrankInformation[50];				//定义一个分级表变量 
extern controlCenterTypeDef glHello_control;			//定义一个控制台
extern runStateTypeDef		glrunState;							//定义一个运行状态记录器

void Fun_game(void);															//
extern const u8  runMethodTable[][100];						//奔跑路线表格
extern const u8  runMethodTableTreasure[][100];						//奔跑路线表格
extern u8 runMethodNum;
extern u8 runMethodNumTreasure;
extern u8 runMethod[100];													//储存第一次奔跑路线
extern u8 runMethod_2[100];                       //储存第二次奔跑路线

extern u8 pes_L;																		//左边光电传感器状态
extern u8 pes_R;																		//右边光电传感器状态

extern u8 SecondGameNum1;														//一键切换第二遍路线1（保守路线）
extern u8 SecondGameNum2;														//一键切换第二遍路线2（高分路线

extern u16 currentSpeed;
extern u16 goalSpeed;
#endif



