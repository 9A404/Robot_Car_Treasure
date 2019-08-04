#include "myconfig.h"


/*全局变量*/
const u16  basic_sensorThreshold[NUM_OF_SENSOR] = {3800,3800,3800,3800,3800,3800,3800,3800,3800,3800,3800,3800};
const u16  brige_sensorThreshold[NUM_OF_SENSOR] = {800,800,800,800,800,800,800,800,800,800,800,800};

                         

/*****************************************************奔跑路线****************************************************************************************/
/*奔跑路线表格*/
const u8 runMethodTable[][100]={
	/* 调试路线 */
/*0*/{37,14,16,44,45,46,47,46,48,43,16,44,14,6},
	
	/* 保守路线一,只拿一个宝物 */
/*1*/{1,2,3,4,3,5,12,7,6,5,2,1,2},
	
	/*保守路线二  拿一个宝物加两个梯形 */
/*2*/{1,2,3,4,3,5,9,10,11,10,12,10,9,5,6,8,6,7,6,5,2,1,2},
		
	/*拿2个宝物 已修改*/	
/*3*/{1,2,3,4,3,5,12,7,6,15,37,14,16,44,45,46,47,46,48,43,16,44,14,6},  //,5,2,1,2
		
	/*拿3个宝物加一个梯形 已修改*/
/*4*/{1,2,3,4,3,5,12,7,6,15,37,14,16,44,45,46,47,46,48,43,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*过全部景点(少8号)，不切路线 没更新路线*/
/*5*/{1,2,3,4,3,5,10,11,10,12,7,6,42,14,44,43,17,18,19,18,17,43,16,44,45,46,47,46,43,44,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,42,6,5,2,1,2},	
	
    /*过全部景点，不切路线 没更新路线*/	
/*6*/{1,2,3,4,3,5,10,11,10,12,6,8,6,7,6,42,14,44,43,17,18,19,18,17,43,16,44,45,46,47,46,43,44,37,36,15,30,31,32,31,33,23,24,23,25,26,27,26,25,33,34,35,36,35,14,42,6,5,2,1,2},		
		
		/*切换路线，用于路段调试*/
	/*0号切换路线,第1个宝物所在位置在7，并且第2个宝物所在位置为37所切换的路线 */
/*7*/{7,6,15,37,15,9,5,2,1,2},
	
	/*1号切换路线,第1个宝物所在位置在12，并且第2个宝物所在位置为37所切换的路线 */
/*8*/{12,7,6,15,37,15,9,5,2,1,2},
	
	/*2号切换路线, 第2个宝物所在位置在37，并且第3个宝物位置在24所切换的路线*/
/*9*/{37,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*3号切换路线, 第2个宝物所在位置在37，并且第3个宝物位置在27所切换的路线*/
/*10*/{37,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*4号切换路线, 第2个宝物所在位置在47，并且第3个宝物位置在24所切换的路线*/
/*11*/{47,46,48,43,16,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
		
	/*5号切换路线, 第2个宝物所在位置在47，并且第3个宝物位置在27所切换的路线*/
/*12*/{47,46,48,43,16,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
};

const u8 runMethodTableTreasure[][100]={
	
	/*0号切换路线,第1个宝物所在位置在7，并且第2个宝物所在位置为37所切换的路线 */
/*7*/{7,6,15,37,15,9,5,2,1,2},
	
	/*1号切换路线,第1个宝物所在位置在12，并且第2个宝物所在位置为37所切换的路线 */
/*8*/{12,7,6,15,37,15,9,5,2,1,2},
	
	/*2号切换路线, 第2个宝物所在位置在37，并且第3个宝物位置在24所切换的路线*/
/*9*/{37,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*3号切换路线, 第2个宝物所在位置在37，并且第3个宝物位置在27所切换的路线*/
/*10*/{37,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,18,17,49,16,44,45,46,47,46,48,43,16,44,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
	
	/*4号切换路线, 第2个宝物所在位置在47，并且第3个宝物位置在24所切换的路线*/
/*11*/{47,46,48,43,16,17,18,19,18,20,21,22,23,24,23,25,26,27,26,25,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
		
	/*5号切换路线, 第2个宝物所在位置在47，并且第3个宝物位置在27所切换的路线*/
/*12*/{47,46,48,43,16,17,18,19,18,20,21,22,23,25,26,27,26,25,23,24,23,22,21,20,17,14,35,36,35,34,30,31,32,31,9,5,2,1,2},
};

u8 runMethod[100]={1,2,5,9};	//保守奔跑的路线:方案二
u8 runMethod_2[100]={1,2,5,9};  //保守奔跑的路线:方案二
/***********************************************************************************************************************************************/

u16 glsensor_ad_value[NUM_OF_SENSOR];		//储存模拟量
u16 glsensor_dig_value;									//储存转化后的数字量
u8 	USART3_TX_BUF[USART3_MAX_SEND_LEN];	//串口3 DMA缓存区

PIDTypeDef glsensorPID;										//定义一个传感器PID调节器
PIDTypeDef glrotAnglePID;									//定义一个转角PID调节器
motorSpeedTypeDef glmotorSpeed;						//定义一个速度记录器
controlCenterTypeDef glHello_control;			//定义一个控制台
runStateTypeDef		glrunState;							//定义一个运行状态记录器
//rankTypeDef glrankInformation[50];			//定义一个分级表变量 
float glsensor_angle;
int gldSpeed;															 //储存速度PID输出
float gldYaw=0;														 //储存偏航角PID输出
u8 findLineFlag=0;											   //巡线方法初始化标志位
u8 rotAngleFlag=0;                         //旋转方法初始化标志位
u8 angle_flag=0;
/*寻宝用标志位*/
u8 QR_code_flag=0;                         //记录收到多少次串口数据                      
u8 treasure_flag=0;                        //宝物摆手标志位
u8 RunMethod_Check=0;
u8 QR_code[2];
u8 Treasure_code[3]={0,0,0};				//记录宝物
float angle_read;
float angle_read_back;
u8 Treasure_all_Flag = 0;
float glPitch,glRoll,glYaw;							   //存储mpu6050读出的欧拉角
float glsetYaw;                            //储存设定的偏航角

float glPitchbuff[2];											 //俯仰角缓存区
float gldif_Pitch;                         //前后两次之差	  
u8 mpu6050_flag=0;												 //标志上下台
u8 U_Dswitch;                              //上下台控制开关 1代表上台，2代表下台
u8  USART1_RX_BUF[66];//串口1 DMA缓存区
u16 gl_time=0;														 	//定时器3标志
u8 runTimes=0;															//记录奔跑次数
u8 runMethodNum;                            //记录奔跑路线条数
u8 runMethodNumTreasure;

u8 pes_L=0;																		//左边光电传感器状态
u8 pes_R=0;																		//右边光电传感器状态

u8 SecondGameNum1=3;												//一键切换第二遍路线3（保守路线）
u8 SecondGameNum2=4;												//一键切换第二遍路线4（高分路线）

u16 currentSpeed=0;
u16 goalSpeed=0;
/*

* 函数介绍：比赛
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void Fun_game(void)
{
	Lcd_Clear(WHITE);//清屏
	Gui_DrawFont_GBK16(0,0,BLUE,WHITE,"比赛:");
	#ifndef  _NEW_MPU6050_
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"MPU6050_Init...");
	MPU6050_Init();		        //MPU6050初始化
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"               ");
	#endif
	Gui_DrawFont_GBK16(0,20,RED,WHITE,"Start");
	/*重新初始化*/
	runTimes = 0;						//记录奔跑次数
	gl_time=0;							//定时器3标志
	mpu6050_flag=0;					//标志上下台
	findLineFlag=0;					//巡线方法初始化标志位
	
	while(1)
	{
//		keyFlag = keyScan(0);
//		
//		/*当有按键按下就跳出*/
//		if( keyFlag==KEY4_ESC)
//		{
//			speedAdjustment(0,0);
//			Time3(STOP);     //关闭定时器
//			mpu6050_samping(STOP); //关闭mpu6050采样
//			/*软件复位*/
//			__set_FAULTMASK(1);  // 关闭所有中断
//			NVIC_SystemReset();  // 复位
//		}
//		if(keyFlag == KEY3_MENU)
//		{
//			//glrunState.F_LineState = EIC;
//			runTimes=1;
//			runStateReset1(&glrunState,&glHello_control);//重置运行状态
//			//findLineFlag=0;
//			speedAdjustment(0,0); 
//		}
		
		if(0 == runTimes)
			{
				CheckrunMethod(runMethod);
				Treasure_Reset_Usart3();
				
				Gui_DrawFont_GBK16(0,40,BLUE,WHITE,"First round...");
				runTimes=3;																		//保证跑一次只初始化
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
		if(1 == runTimes)
			{
				Treasure_Reset_Usart3();
				
				Gui_DrawFont_GBK16(0,60,BLUE,WHITE,"Second round...");
				runTimes=4;																		//保证跑一次只初始化
				runMethodReset(runMethod,runMethod_2);				//更新路线
				CheckrunMethod(runMethod);
				/*****软件逻辑层初始化部分*****/
				Control_Init(&glHello_control,runMethod);     //初始化控制台
				runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
			}
			/*跑完一个路段才更新一次*/
		 if(control_Update(&glHello_control,strlen((const char*)runMethod),runMethod,mapInformation))//当检测到节点后就会更新控制台的数据//sizeof(runMethod)/sizeof(runMethod[0])
			{
				runStateReset(&glrunState,&glHello_control);//重置运行状态
				findLineFlag=0;
				#ifdef BlueTooth_Debug
					controlCenter_u3printf(runMethod,&glHello_control);
				#endif
			}
				/*采样完成一次就进行一次处理*/
		if(sampingStatus() == 1) 
			{	
				findLine_Task(&glHello_control,&glrunState);        	 // 巡线任务
				roadBlocksHandle_Task(&glHello_control,&glrunState);	 // 障碍处理任务
				speed_Task(&glHello_control,&glrunState);				//加速任务
				seekNode_Task(&glHello_control,&glrunState);      		 // 找点任务
			 	carPark_Task(&glHello_control, &glrunState);       		 // 停车任务
                rotAngle_Task(&glHello_control,&glrunState);           // 转弯任务
			}
		
			
	}
}







/*********************************************************************************************************************/
int main(void)
{	
	/************硬件初始化部分*****************************************************************************/	
	NVIC_Configuration();				//系统中断优先级分组抢占2：响应2	
	delay_init();	    	  		//延时函数初始化	
	Lcd_Init();             //TFT屏幕显示初始化
	bootDisplay();					//开机界面
	ADC_DMA_Init();        	//ADC&DMA初始化
	sampingTime_Init(150);	//采样周期为15ms对应的值为150 
	//mpu6050_sampingTime_Init(80);//mpu6050采样周期8ms
	TIM3_Config(100-1,7200-1); // 定时器3定时周期为10ms
	motor_PWM_Init();       //PWM初始化
	uart_init(115200);			//串口1初始化
	#ifdef PHONE
		usart3_init(115200);
	#endif
	
	#ifdef MODULAR
		usart3_init(9600);			//串口DMA初始化函数	模块9600 手机115200	
	#endif
	sg_PWM_Init();					//舵机初始化
	keyInit();							//按键初始化
	pesInit();							//光电传感器初始化
	ledInit();							//led初始化
//	MPU6050_Init();		        //MPU6050初始化
	runMethodNum=sizeof(runMethodTable)/sizeof(runMethodTable[0]); //计算runMethodTable中共有几条线路
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
//		speedAdjustment(1080,900);//NFL——slow
//		speedAdjustment(-1050,-1100);//NFL——back
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
		
		
		
		
		
		
		

	














 



