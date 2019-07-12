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

/*��������*/
//#define BlueTooth_Debug

/*LED����*/
#define LED_Debug

/*����Ѳ��*/
//#define Slow_FL

/*����Ѳ��*/
#define Fast_FL

#define BlueTooth

#define AUTO_Treasure

#define _NEW_MPU6050_//�°�������

#define max(a,b)			(a>b ? a:b)
#define min(a,b)			(a<b ? a:b)
#define limit(x,a,b)	(min(max(x,a) , b))	

#define NUM_OF_SENSOR 	12					//����������
#define USART3_MAX_SEND_LEN 200		 // ���ͻ����С

#define LEFT 0
#define RIGHT 1

#define DEFAULT_SPEED 3300
#define SLOW_SPEED 2200
#define QUICK_SPEED 6500
extern unsigned short glsensor_ad_value[NUM_OF_SENSOR];       //������ģ��������
extern unsigned short glsensor_dig_value;									    //����������������
extern unsigned char 	USART3_TX_BUF[USART3_MAX_SEND_LEN];     //����3���ͻ���

/********************************��������ֵ******************************************************************/
extern const unsigned short int  basic_sensorThreshold[NUM_OF_SENSOR]; //��������ֵ
extern const  u16  brige_sensorThreshold[NUM_OF_SENSOR];//������ֵ

/*******************************������*******************************************************************/
extern const map_linkInforTypeDef mapInformation[][NODEFORKNUM]; //��ͼ��Ϣ���ֻ���
extern const rankTypeDef rankInformation_FL[22];                   //Ѳ�߷ּ���


extern u8 RunMethod_Check;  //�������ѡ·�����ܵ���һ��ƽ̨(����Ѱ���л�·��) 
extern u8 QR_code_flag;  
extern u8 treasure_flag;
extern float glPitchbuff[2];
extern u8 QR_code[2];
extern float gldif_Pitch;
extern u8 mpu6050_flag;
extern u8 U_Dswitch;                                //����̨���ƿ��� 1������̨��2������̨
extern float gldYaw;																//����ƫ����PID���
extern float glPitch,glRoll,glYaw;							  //ŷ����
extern float glsetYaw;																		//�����趨��ƫ����
extern int gldSpeed;															//�����ٶ�PID���
extern u8 findLineFlag;														//Ѳ�߷�����ʼ����־λ
extern u8 rotAngleFlag;                         //��ת������ʼ����־λ
extern u8  USART1_RX_BUF[66];//����1 DMA������
extern u8 key0_Flag;																//����0��־λ
extern u16 gl_time;														 		 //��ʱ��3��־
extern u8 runTimes;																//��¼���ܴ���
extern float angle_read;			//��¼��һ���̰�ת��ĽǶ�
extern float angle_read_back;		//��¼�ڶ����̰�ת��ĽǶ�
extern u8 angle_flag;
extern float glsensor_angle;
extern u8 Treasure_all_Flag;		//����·�ߵı�־λ
/********************************�߼��������**************************************************/
extern PIDTypeDef glsensorPID;										//����һ��������PID������
extern PIDTypeDef glrotAnglePID;									//����һ��ת��PID������
extern motorSpeedTypeDef glmotorSpeed;				  	//����һ���ٶȼ�¼��
//extern rankTypeDef glrankInformation[50];				//����һ���ּ������ 
extern controlCenterTypeDef glHello_control;			//����һ������̨
extern runStateTypeDef		glrunState;							//����һ������״̬��¼��

void Fun_game(void);															//
extern const u8  runMethodTable[][100];						//����·�߱��
extern const u8  runMethodTableTreasure[][100];						//����·�߱��
extern u8 runMethodNum;
extern u8 runMethodNumTreasure;
extern u8 runMethod[100];													//�����һ�α���·��
extern u8 runMethod_2[100];                       //����ڶ��α���·��

extern u8 pes_L;																		//��߹�紫����״̬
extern u8 pes_R;																		//�ұ߹�紫����״̬

extern u8 SecondGameNum1;														//һ���л��ڶ���·��1������·�ߣ�
extern u8 SecondGameNum2;														//һ���л��ڶ���·��2���߷�·��

extern u16 currentSpeed;
extern u16 goalSpeed;
#endif



