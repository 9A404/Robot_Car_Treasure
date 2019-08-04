#include "myconfig.h"


/*ȫ�ֱ���*/
const u16  basic_sensorThreshold[NUM_OF_SENSOR] = {3800,3800,3800,3800,3800,3800,3800,3800,3800,3800,3800,3800};
const u16  brige_sensorThreshold[NUM_OF_SENSOR] = {800,800,800,800,800,800,800,800,800,800,800,800};

                         

/*****************************************************����·��****************************************************************************************/
/*����·�߱��*/
const u8 runMethodTable[][100]={
	/* ����·�� */
/*0*/{37,14,16,44,45,46,47,46,48,43,16,44,14,6},
	
	/* ����·��һ,ֻ��һ������ */
/*1*/{1,2,3,4,3,5,12,7,6,5,2,1,2},
	
	/*����·�߶�  ��һ��������������� */
/*2*/{1,2,3,4,3,5,9,10,11,10,12,10,9,5,6,8,6,7,6,5,2,1,2},
		
	/*��2������ ���޸�*/	
/*3*/{1,2,3,4,3,5,12,7,6,15,37,14,16,44,45,46,47,46,48,43,16,44,14,6},  //,5,2,1,2
		
	/*��3�������һ������ ���޸�*/
/*4*/{1,2,3,4,3,5,12,7,6,15,37,14,16,44,45,46,47,46,48,43,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*��ȫ������(��8��)������·�� û����·��*/
/*5*/{1,2,3,4,3,5,10,11,10,12,7,6,42,14,44,43,17,18,19,18,17,43,16,44,45,46,47,46,43,44,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,42,6,5,2,1,2},	
	
    /*��ȫ�����㣬����·�� û����·��*/	
/*6*/{1,2,3,4,3,5,10,11,10,12,6,8,6,7,6,42,14,44,43,17,18,19,18,17,43,16,44,45,46,47,46,43,44,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,42,6,5,2,1,2},		
		
		/*�л�·�ߣ�����·�ε���*/
	/*0���л�·��,��1����������λ����7�����ҵ�2����������λ��Ϊ37���л���·�� */
/*7*/{7,6,15,37,15,9,5,2,1,2},
	
	/*1���л�·��,��1����������λ����12�����ҵ�2����������λ��Ϊ37���л���·�� */
/*8*/{12,7,6,15,37,15,9,5,2,1,2},
	
	/*2���л�·��, ��2����������λ����37�����ҵ�3������λ����24���л���·��*/
/*9*/{37,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*3���л�·��, ��2����������λ����37�����ҵ�3������λ����27���л���·��*/
/*10*/{37,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*4���л�·��, ��2����������λ����47�����ҵ�3������λ����24���л���·��*/
/*11*/{47,46,48,43,16,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
		
	/*5���л�·��, ��2����������λ����47�����ҵ�3������λ����27���л���·��*/
/*12*/{47,46,48,43,16,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
};

const u8 runMethodTableTreasure[][100]={
	
	/*0���л�·��,��1����������λ����7�����ҵ�2����������λ��Ϊ37���л���·�� */
/*7*/{7,6,15,37,15,9,5,2,1,2},
	
	/*1���л�·��,��1����������λ����12�����ҵ�2����������λ��Ϊ37���л���·�� */
/*8*/{12,7,6,15,37,15,9,5,2,1,2},
	
	/*2���л�·��, ��2����������λ����37�����ҵ�3������λ����24���л���·��*/
/*9*/{37,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*3���л�·��, ��2����������λ����37�����ҵ�3������λ����27���л���·��*/
/*10*/{37,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*4���л�·��, ��2����������λ����47�����ҵ�3������λ����24���л���·��*/
/*11*/{47,46,48,43,16,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
		
	/*5���л�·��, ��2����������λ����47�����ҵ�3������λ����27���л���·��*/
/*12*/{47,46,48,43,16,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
};

u8 runMethod[100]={1,2,5,9};	//���ر��ܵ�·��:������
u8 runMethod_2[100]={1,2,5,9};  //���ر��ܵ�·��:������
/***********************************************************************************************************************************************/

u16 glsensor_ad_value[NUM_OF_SENSOR];		//����ģ����
u16 glsensor_dig_value;									//����ת�����������
u8 	USART3_TX_BUF[USART3_MAX_SEND_LEN];	//����3 DMA������

PIDTypeDef glsensorPID;										//����һ��������PID������
PIDTypeDef glrotAnglePID;									//����һ��ת��PID������
motorSpeedTypeDef glmotorSpeed;						//����һ���ٶȼ�¼��
controlCenterTypeDef glHello_control;			//����һ������̨
runStateTypeDef		glrunState;							//����һ������״̬��¼��
//rankTypeDef glrankInformation[50];			//����һ���ּ������ 
float glsensor_angle;
int gldSpeed;															 //�����ٶ�PID���
float gldYaw=0;														 //����ƫ����PID���
u8 findLineFlag=0;											   //Ѳ�߷�����ʼ����־λ
u8 rotAngleFlag=0;                         //��ת������ʼ����־λ
u8 angle_flag=0;
/*Ѱ���ñ�־λ*/
u8 QR_code_flag=0;                         //��¼�յ����ٴδ�������                      
u8 treasure_flag=0;                        //������ֱ�־λ
u8 RunMethod_Check=0;
u8 QR_code[2];
u8 Treasure_code[3]={0,0,0};				//��¼����
float angle_read;
float angle_read_back;
u8 Treasure_all_Flag = 0;
float glPitch,glRoll,glYaw;							   //�洢mpu6050������ŷ����
float glsetYaw;                            //�����趨��ƫ����

float glPitchbuff[2];											 //�����ǻ�����
float gldif_Pitch;                         //ǰ������֮��	  
u8 mpu6050_flag=0;												 //��־����̨
u8 U_Dswitch;                              //����̨���ƿ��� 1������̨��2������̨
u8  USART1_RX_BUF[66];//����1 DMA������
u16 gl_time=0;														 	//��ʱ��3��־
u8 runTimes=0;															//��¼���ܴ���
u8 runMethodNum;                            //��¼����·������
u8 runMethodNumTreasure;

u8 pes_L=0;																		//��߹�紫����״̬
u8 pes_R=0;																		//�ұ߹�紫����״̬

u8 SecondGameNum1=3;												//һ���л��ڶ���·��3������·�ߣ�
u8 SecondGameNum2=4;												//һ���л��ڶ���·��4���߷�·�ߣ�

u16 currentSpeed=0;
u16 goalSpeed=0;
/*

* �������ܣ�����
* �����������
* �����������
* ����ֵ  ����
* ����    ��@����

*/
void Fun_game(void)
{
	Lcd_Clear(WHITE);//����
	Gui_DrawFont_GBK16(0,0,BLUE,WHITE,"����:");
	#ifndef  _NEW_MPU6050_
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"MPU6050_Init...");
	MPU6050_Init();		        //MPU6050��ʼ��
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"               ");
	#endif
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"Start");
	/*���³�ʼ��*/
	runTimes = 0;						//��¼���ܴ���
	gl_time=0;							//��ʱ��3��־
	mpu6050_flag=0;					//��־����̨
	findLineFlag=0;					//Ѳ�߷�����ʼ����־λ
	
	while(1)
	{
//		keyFlag = keyScan(0);
//		
//		/*���а������¾�����*/
//		if( keyFlag==KEY4_ESC)
//		{
//			speedAdjustment(0,0);
//			Time3(STOP);     //�رն�ʱ��
//			mpu6050_samping(STOP); //�ر�mpu6050����
//			/*�����λ*/
//			__set_FAULTMASK(1);  // �ر������ж�
//			NVIC_SystemReset();  // ��λ
//		}
//		if(keyFlag == KEY3_MENU)
//		{
//			//glrunState.F_LineState = EIC;
//			runTimes=1;
//			runStateReset1(&glrunState,&glHello_control);//��������״̬
//			//findLineFlag=0;
//			speedAdjustment(0,0); 
//		}
		
		if(0 == runTimes)
			{
				CheckrunMethod(runMethod);
				Treasure_Reset_Usart3();
				
				Gui_DrawFont_GBK16(0,40,BLUE,WHITE,"First round...");
				runTimes=3;																		//��֤��һ��ֻ��ʼ��
				/*****����߼����ʼ������*****/
				Control_Init(&glHello_control,runMethod);     //��ʼ������̨
				runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
			}
		if(1 == runTimes)
			{
				Treasure_Reset_Usart3();
				
				Gui_DrawFont_GBK16(0,60,BLUE,WHITE,"Second round...");
				runTimes=4;																		//��֤��һ��ֻ��ʼ��
				runMethodReset(runMethod,runMethod_2);				//����·��
				CheckrunMethod(runMethod);
				/*****����߼����ʼ������*****/
				Control_Init(&glHello_control,runMethod);     //��ʼ������̨
				runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
			}
			/*����һ��·�βŸ���һ��*/
		 if(control_Update(&glHello_control,strlen((const char*)runMethod),runMethod,mapInformation))//����⵽�ڵ��ͻ���¿���̨������//sizeof(runMethod)/sizeof(runMethod[0])
			{
				runStateReset(&glrunState,&glHello_control);//��������״̬
				findLineFlag=0;
				#ifdef BlueTooth_Debug
					controlCenter_u3printf(runMethod,&glHello_control);
				#endif
			}
				/*�������һ�ξͽ���һ�δ���*/
		if(sampingStatus() == 1) 
			{	
				findLine_Task(&glHello_control,&glrunState);        	 // Ѳ������
				roadBlocksHandle_Task(&glHello_control,&glrunState);	 // �ϰ���������
				speed_Task(&glHello_control,&glrunState);				//��������
				seekNode_Task(&glHello_control,&glrunState);      		 // �ҵ�����
			 	carPark_Task(&glHello_control, &glrunState);       		 // ͣ������
                rotAngle_Task(&glHello_control,&glrunState);           // ת������
			}
		
			
	}
}







/*********************************************************************************************************************/
int main(void)
{	
	/************Ӳ����ʼ������*****************************************************************************/	
	NVIC_Configuration();				//ϵͳ�ж����ȼ�������ռ2����Ӧ2	
	delay_init();	    	  		//��ʱ������ʼ��	
	Lcd_Init();             //TFT��Ļ��ʾ��ʼ��
	bootDisplay();					//��������
	ADC_DMA_Init();        	//ADC&DMA��ʼ��
	sampingTime_Init(150);	//��������Ϊ15ms��Ӧ��ֵΪ150 
	//mpu6050_sampingTime_Init(80);//mpu6050��������8ms
	TIM3_Config(100-1,7200-1); // ��ʱ��3��ʱ����Ϊ10ms
	motor_PWM_Init();       //PWM��ʼ��
	uart_init(115200);			//����1��ʼ��
	#ifdef PHONE
		usart3_init(115200);
	#endif
	
	#ifdef MODULAR
		usart3_init(9600);			//����DMA��ʼ������	ģ��9600 �ֻ�115200	
	#endif
	sg_PWM_Init();					//�����ʼ��
	keyInit();							//������ʼ��
	pesInit();							//��紫������ʼ��
	ledInit();							//led��ʼ��
//	MPU6050_Init();		        //MPU6050��ʼ��
	runMethodNum=sizeof(runMethodTable)/sizeof(runMethodTable[0]); //����runMethodTable�й��м�����·
	while(1)
	{	
//		
//		delay_ms(1000);
		displayOperation();
//  get_from_phone();
		
//	flMethod_slow();
//	flMethod_stop();


////   rotAngle_Right(180);
//		rotAngle_Left(180);
//		delay_ms(3000);


		
		//xin che
//		speedAdjustment(2600,2500);//	FL_slow
//		speedAdjustment(1600,1500); //step
//		speedAdjustment(3600,3500); //default		
//		speedAdjustment(1940,1800);//NFL
//		speedAdjustment(1080,900);//NFL����slow
//		speedAdjustment(-1050,-1100);//NFL����back
//		 speedAdjustment(4600,4500); //middle
//		speedAdjustment(2400,2300); //brige
//		speedAdjustment(2100,2000); //upbrige
//		speedAdjustment(1500,1400); //downbrige
//		speedAdjustment(2100,2000); //UpPlatform
//		speedAdjustment(1400,1200); //downPlatform

//		speedAdjustment(5000,4900); //quick
//     speedAdjustment(6600,6400); //quickest


		 
//		 delay_ms(3000);
//		 delay_ms(1000);
//		 speedAdjustment(0,0);
//		 while(1);	
		
	}
}
		
		
		
		
		
		
		

	














 



