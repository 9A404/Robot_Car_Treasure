#ifndef __PWM_H
#define __PWM_H

#include "sys.h"
/*��¼��ǰ���ҵ�����ٶ�*/
typedef struct{
	
	int leftSpeed;
	int rightSpeed;
	
}motorSpeedTypeDef;

/*������*/
typedef enum {HEAD ,BODY, L_ARM , R_ARM}SgNumber;

/*���ת���Ƕ�*/
typedef enum {L_UP = 650,L_DOWN = 1150,R_DOWN = 200,R_UP = 550,H_MID = 600,H_L=800,H_R=400,B_UP=100,B_DOWN=200}RotationAngle;

void motor_PWM_Init(void);
void speedAdjustment(int lspeed,int rspeed);
void incrementalSpeedOut(motorSpeedTypeDef *p,int dSpeed);
void speedRec_Init(motorSpeedTypeDef *speedRegulator,int leftSpeed,int rightSpeed);
void positionSpeedOut(int leftSpeed,int rightSpeed,int dSpeed);
void sg_PWM_Init(void);
void sgAngleControl(SgNumber num,RotationAngle angle);


#endif

