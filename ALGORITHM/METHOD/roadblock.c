#include "roadblock.h"
#include "common_time.h"
//#include "myconfig.h"
/************************************************桥***********************************************************/
///*

//* 函数介绍：识别是否为全0
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1（到达路障）0（未到达路障）
//* 其他		：传感器全为0的时候
//* 作者    ：@断忆

//*/
static u8 identifyALL_Zero()
{
	
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	if( 0x000==glsensor_dig_value)
		return 1;
	else
		return 0;
}

///*

//* 函数介绍：桥路障处理方法
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(路障解决)0（路障未解决）
//* 其他		：将巡线方法切换成过桥的巡线
//* 作者    ：@断忆

//*/
//u8 BlockHandleMethod_Brige()
//{
//	static findLine save;
//	static u8 flag=0;
//	save = glHello_control.linkInform.findLineWays;
//	while(1==identifyALL_Zero()) speedAdjustment(2090,2000);//到达桥头底部
//	speedAdjustment(0,0);
//	delay_ms(500);
//	if(0==flag && 1==PES_Platform)          //在桥头顶部
//	{
//		glHello_control.linkInform.findLineWays = FL_brige;
//	  findLineFlag = 0;
//		flag=1;
//	}
//	if(1==flag && 0==PES_Platform)  flag=2;    //在桥上
//	while(1==identifyALL_Zero()) speedAdjustment(2090,2000);//在桥尾顶部
//	speedAdjustment(0,0);
//	delay_ms(500);
//	if(2==flag && 1==PES_Platform)        //在桥尾底部
//	{
//		glHello_control.linkInform.findLineWays = save;
//	  findLineFlag = 0;
//		flag=0;
//		return 1;
//	}
//	
//	return 0;

//}

/*

* 函数介绍：桥路障处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Brige()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag && 1==PES_Platform)         //到达桥头底部
	{
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays = FL_brigeup; 
		findLineFlag = 0;
		//angle_flag = 0;
		flag = 1;
	}
	if(1==flag && 0==PES_Platform)          //在桥头坡上
	{
		glHello_control.linkInform.findLineWays = FL_brigeup; 
		findLineFlag = 0;
		flag=2;
	}
	if(2==flag && 1==PES_Platform)          //在桥头顶部
	{
		glHello_control.linkInform.findLineWays = FL_brige;
	    findLineFlag = 0;
		flag=3;
	}
	if(3==flag && 0==PES_Platform)  flag=4;    //在桥上
	if(4==flag && 1==PES_Platform)             //在桥尾顶部
	{
		glHello_control.linkInform.findLineWays = FL_brigedown;
	  findLineFlag = 0;
		flag=5;
	}
	if(5==flag && 0==PES_Platform)  flag=6;
	if(6==flag && 1==PES_Platform)        //在桥尾底部
	{
		glHello_control.linkInform.findLineWays = save;
	  findLineFlag = 0;
		flag=0;
		return 1;
	}
	
	return 0;
//static findLine save;
//	static u8 flag=0;
//     if(0 == flag)
//	 { 
//		 save = glHello_control.linkInform.findLineWays;
//		 Time3(START);
//		 gl_time = 0;
//         flag = 1;		 
//	 }
//	else if(1==flag && gl_time > 50)         //μ?′???í·μ×2?
//	{   
////		speedAdjustment(0,0);
////		while(1);
////	
//		glHello_control.linkInform.findLineWays = FL_angle; 
//		findLineFlag = 0;
//		angle_flag = 0;
//		flag = 2;
//	}
//	else if(2==flag && gl_time > 150)          //?ú??í·??é?
//	{
//		
////		speedAdjustment(0,0);
////		while(1);
//		glHello_control.linkInform.findLineWays = FL_brige; 
//		findLineFlag = 0;
//		flag=3;
//	}
//	else if(3==flag && gl_time > 275)          //?ú??í·?￥2?
//	{
////		speedAdjustment(0,0);
////     	while(1);

//		flag=4;
//		Time3(STOP);
//	}
//	else if( 4 == flag )  
//	{
//     Time3(START);
//	 gl_time = 0;
//     glHello_control.linkInform.findLineWays = FL_slow_angle;
//	 findLineFlag = 0; 
//     angle_flag = 0;
//	 flag = 5; 
//	}
//  	//?ú??é?
//	else if(5==flag && gl_time > 105)             //?ú???2?￥2?
//	{
////	    speedAdjustment(0,0);
////     	while(1);
//		glHello_control.linkInform.findLineWays = save;
//	    findLineFlag = 0;
//		flag=0;
//		Time3(STOP);
//		return 1;
//		
//	}
////	if(6==flag && 0==PES_Platform)  flag=6;
////	if(6==flag && 1==PES_Platform)        //?ú???2μ×2?
////	{
////		glHello_control.linkInform.findLineWays = save;
////	  findLineFlag = 0;
////		flag=0;
////		return 1;
////	}
////	
//	return 0;


}
/***************************************************门********************************************************/
/*

* 函数介绍：过门处理函数
* 输入参数：无
* 输出参数：无
* 返回值  ：1(门开或者更新了线路)0（门关且没有更新线路）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_DOOR(void)
{
//  	static u8 flag=0;     //门开标志位  
//	/*******************  门开  ***************************/
//	if(1==PES_Platform && 0==flag)  flag=1;
//	else if(0==PES_Platform && 1==flag) flag=2;
//	else if(1==PES_Platform && 2==flag)  flag=3;
//	else if(0==PES_Platform && 3==flag)
//	{
//		flag=0;
//		return 1;
//	}      
//	return 0;
	return 1;
}



/***************************************************平台********************************************************/
/*

* 函数介绍：检测上台
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@断忆

*/
//u8 BlockHandleMethod_upPlatform()
//{
//	if(mpu6050_flag == 0)
//	{	
//		U_Dswitch = 1;//标志中断运行上台程序
//		mpu6050_samping(START);
//	}
//	if(mpu6050_flag == 2)
//	{
//		mpu6050_samping(STOP);
//		mpu6050_flag = 0;
//		U_Dswitch = 0;//让上台程序不运行
//		
//		//speedAdjustment(2000,2080);
//		//delay_ms(500);
//		return 1;
//	}
//	return 0;
//	
//}




/*

* 函数介绍：处理7号平台
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
 u8 BlockHandleMethod_down_27_26()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		#ifdef LED_Debug
		led_flash();
		#endif
		flag=2;
	}
	else if(2==flag && 0==PES_Platform) flag=3;
	else if(3==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		#ifdef LED_Debug
		led_flash();
		#endif
		flag=4;
	}
	else if(4==flag && 0==PES_Platform) flag=5;
	else if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_slow; 
		findLineFlag = 0;
		#ifdef LED_Debug
		led_flash();
		#endif
		Time3(START); //打开定时器
		gl_time=0;
		flag=6;
	}
	else if(6==flag && gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		#ifdef LED_Debug
		led_flash();
		#endif
		Time3(STOP); //打开定时器
		gl_time=0;
		flag=0;
		return 1;
	}
		return 0;

}

/*

* 函数介绍：  
* 输入参数：无
* 输出参数：无
* 返回值  ：翻滚角
* 其他		：
* 作者    ：@断忆

*/
static float Monitor_ROLL()
{
	float temp;
	u8 i;
	#ifdef _NEW_MPU6050_
		MPU6050_Pose_usart();
		temp=glRoll;
	#else
		for(i=0;i<50;i++)
			MPU6050_Pose();				//更新欧拉角
		temp=glPitch;
	#endif
	return temp;
}

/*

* 函数介绍:路障读角度方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：你猜

*/
 u8 Angle_read()
{
  
    static u8 flag=0;
	if(flag == 0)
	{
	    Time3(START);
		gl_time = 0;
		flag = 1;
	}
	else if(flag == 1&&gl_time>50)
	{
		Time3(STOP);
		MPU6050_Pose_usart();
		angle_read = setYaw(glYaw,85);
		angle_read_back = setYaw(glYaw,-83);
		flag = 0; 
		   
		return 1;
	}
	return 0;
}
/*

* 函数介绍：过跷跷板
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@林

*/
 u8 BlockHandleMethod_Seesaw()
{
//	static findLine save;
	static u8 flag=0;
	static u8 Turn_Flag=0;
	float temp;
	if(0==flag)                //在找点任务中将车摆正后延时直走
	{	
//		speedAdjustment(2450,2200);
		Time3(START);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_angle;
    angle_flag = 0; 		
		findLineFlag = 0;
		//led_flash();
		flag=1;
	}
	else if(1==flag&&gl_time>86)         
	{
//		temp = Monitor_ROLL();
//		if( temp > -10)               //如果车在跷跷板的另外一端则继续盲走后置flag=2
//		{
//			//flag++;
//			// ("glPitch%0.2f\r\n",temp);
//			speedAdjustment(2000,2000);

//			//glHello_control.linkInform.findLineWays = NFL; 
//			//led_flash();
//			flag=2;
//		}
//		else                         //如果车还没有到则继续盲走
//		{
//			speedAdjustment(2000,2120);
//		
//			delay_ms(1000);
//			delay_ms(200);
//			speedAdjustment(0,0);
//		
//			delay_ms(1000);

//			//u3_printf("glPitch%0.2f\r\n",glPitch);
//		}
		speedAdjustment(0,0);
		//if(pes_R==0) {speedAdjustment(2000,2400);delay_ms(10);}
		//else if(pes_L==0) {speedAdjustment(2400,2000);delay_ms(10);}
	    delay_ms(800);

		temp = Monitor_ROLL();
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		if(temp>-10){
			speedAdjustment(2100,2200);
			flag=2;	
			
		}
		
		
	}
	else if(2 == flag)                //车子在跷跷板的另外一端则先检测传感器有没有在白线上
	{
		glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量	
			if(calculateNum(glsensor_dig_value)<=1 && Turn_Flag<4) 
		{
			rotAngle_Left(20);             //如果不在白线则左转20度，大多数情况下是车子偏右，故左转
			Turn_Flag++;
		}
		else                         //否则返回1完成障碍任务
		{
			Turn_Flag=0;
			flag=0;
			return 1;
		}
	}
		return 0;

}


static u8 Check_DownPlatform(u16 sensor_dig_value)
{
	u8 temp = 0;
	sensor_dig_value = sensor_dig_value&0x7fe;
	sensorBit_u3printf(sensor_dig_value);
	switch(sensor_dig_value)
	{
		case 0x800: temp=1;break;     // 1000 0000 0000
		case 0xC00: temp=1;break;			// 1100 0000 0000
		case 0xE00: temp=1;break;			// 1110 0000 0000
		case 0x600: temp=1;break;     // 0110 0000 0000
		case 0x700: temp=1;break;     // 0111 0000 0000
		case 0x300: temp=1 ;break;    // 0011 0000 0000
		case 0x380: temp=1 ;break;    // 0011 1000 0000
		case 0x180: temp=1 ;break;    // 0001 1000 0000
		case 0x1C0: temp=1 ;break;    // 0001 1100 0000
		case 0x0C0: temp=1 ;break;    // 0000 1100 0000 
		
		case 0x0E0: temp=1 ;break;    // 0000 1110 0000 中间
		case 0x060: temp=1 ;break;    // 0000 0110 0000 中间
		case 0x070: temp=1 ;break;    // 0000 0111 0000 中间
		case 0x030: temp=1 ;break;    // 0000 0011 0000 中间
		
		case 0x038: temp=1 ;break;    // 0000 0011 1000
		case 0x018: temp=1 ;break;    // 0000 0001 1000
		case 0x01C: temp=1 ;break;    // 0000 0001 1100
		case 0x00C: temp=1 ;break;    // 0000 0000 1100
		case 0x00E: temp=1 ;break;    // 0000 0000 1110
		case 0x006: temp=1 ;break;    // 0000 0000 0110
		case 0x007: temp=1 ;break;    // 0000 0000 0111
		case 0x003: temp=1 ;break;    // 0000 0000 0011
		case 0x001: temp=1 ;break;    // 0000 0000 0001
		default:  break;
	}
	return temp;
}
/*

* 函数介绍：下平台处理方法（光电开关）
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：下完平台才巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Platform ()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform)
	{
			glHello_control.linkInform.findLineWays = FL_DownPlatform; 
			findLineFlag = 0;
			flag=2;
//		glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量	
//		if( Check_DownPlatform(glsensor_dig_value) )
//		{
//			glHello_control.linkInform.findLineWays = FL_DownPlatform; 
//			findLineFlag = 0;
//			flag=2;
//		}
//		else
//		{
//			speedAdjustment(-1000,-1000);
//			delay_ms(500);
//			while( !pes_R && !pes_L)
//				speedAdjustment(-1000,-1000);
//			
//			if(1 == pes_R) 
//			{
//				rotAngle_Right(20);
//				pes_R = 0;
//			}
//			else if(1 == pes_L) 
//			{
//				rotAngle_Left(20);
//				pes_L = 0;
//			}
//			flag=0;
		
		//}
		
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(3==flag&&1==PES_Platform)  flag=4;
	else if(0==PES_Platform && 4==flag)
	{
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;

}

/*

* 函数介绍：过台阶方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：无
* 作者    ：@袁梓聪

*/
u8 BlockHandleMethod_Step (){
	static u8 flag=0;
	static findLine save;
	if(flag == 0)
	{
		save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	else if(1 == flag&&1 == PES_Platform)          //?°??1aμ??a1?2?áá′ú±íμ?′?é??eμ×2?
	{
		glHello_control.linkInform.findLineWays = FL_UpPlatform;   
		findLineFlag = 0;
		flag=2; 
	}
	else if(2==flag&&0==PES_Platform)         //?°??1aμ??a1?áá′ú±íμ?′?é??e?￥2?
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform;   
		findLineFlag = 0;
		Time3(START); //′ò?a?¨ê±?÷
		gl_time=0;
		flag=3;
	}
	else if(gl_time>250 && 3==flag)
	{
		Time3(STOP); //1?±??¨ê±?÷
		gl_time = 0;
//	  speedAdjustment(0,0);
//	  delay_ms(1000);
		glHello_control.linkInform.findLineWays = save;   
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
	return 0;
}
/*

* 函数介绍：过两个台阶方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：无
* 作者    ：@袁梓聪

*/
u8 BlockHandleMethod_Step_2 (){
	static u8 flag=0;
	static findLine save;
	if(flag == 0)
	{
		save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	else if(1 == flag&&1 == PES_Platform) 
	{
		glHello_control.linkInform.findLineWays = FL_UpPlatform;   
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag=2; 
	}
	else if(2==flag&&gl_time>60){
		Time3(STOP);
		gl_time=0;
		flag=3;
	}
	else if(3==flag) 
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform;   
		findLineFlag = 0;
		Time3(START); //′ò?a?¨ê±?÷
		gl_time=0;
		flag=4;
	}
	else if(gl_time>100 && 4==flag)
	{
		Time3(STOP); //1?±??¨ê±?÷
		gl_time = 0;
		glHello_control.linkInform.findLineWays = FL_UpPlatform;
		findLineFlag = 0;
		Time3(START);
		gl_time = 0;
		flag = 5;
	}
	else if(flag==5 && gl_time>60)
	{
		Time3(STOP);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_DownPlatform;
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag = 6;
	}
	else if(flag==6 && gl_time>60)
	{
		Time3(STOP);
		gl_time=0;
		glHello_control.linkInform.findLineWays = save;
		findLineFlag=0;
		flag=0;
		return 1;
	}
	return 0;
}
/*

* 函数介绍：过山丘方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：无
* 作者    ：@林

*/
u8 BlockHandleMethod_Slope ()
{
	static u8 flag=0;
	static findLine save;
	if(flag == 0)
	{
		save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	else if(1 == flag&&1 == PES_Platform)          //前下光电开关不亮代表到达山丘底部
	{
		glHello_control.linkInform.findLineWays = FL_UpPlatform;   
		findLineFlag = 0;
		flag=2;	
	}
	else if(2==flag&&0==PES_Platform)         //前下光电开关亮代表到达山丘顶部
	{
		glHello_control.linkInform.findLineWays = FL_DownPlatform;   
		findLineFlag = 0;
		Time3(START); //打开定时器
		gl_time=0;
		flag=3;
	}
	else if(gl_time>200 && 3==flag)
	{
		Time3(STOP); //关闭定时器
		gl_time = 0;
		glHello_control.linkInform.findLineWays = save;   
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;

}

/**********************************************挡板*************************************************************/
/*

* 函数介绍：挡板判断
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：前方光电没有检测到就出发
* 作者    ：@断忆

*/
static u8 BlockHandleMethod_Baffle()
{
	static u8 flag=0;
	if(flag == 0)
	{
		speedAdjustment(0,0);	
	    sgAngleControl(HEAD,H_L);
	    delay_ms(400);
		sgAngleControl(HEAD,H_R);
		delay_ms(400);
		sgAngleControl(HEAD,H_L);
		delay_ms(400);
		sgAngleControl(HEAD,H_R);
		delay_ms(400);
		sgAngleControl(HEAD,H_MID);
		flag = 1;
	 }	
	while(1==PES_H)  speedAdjustment(0,0);	
	while(0==PES_H)  speedAdjustment(0,0);	
	while(1==PES_H)  
	{
		flag=0;
		return 1;
	}
  return 0;
}

/*

* 函数介绍：下起点处理方法(利用底下光电开关+检测挡板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：下完平台才巡线
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Platform_1 ()
{
	static findLine save;
	static u8 flag=0;
	if(flag == 0&&1==BlockHandleMethod_Baffle())
	{
		//u3_printf("Baffle+NFL");
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL;
		flag = 1;
	}
else if(1==flag&&1==PES_Platform)
	{
		speedAdjustment(0,0);
//		delay_ms(500);
//		Gui_DrawFont_GBK16(0,60,BLUE,WHITE,"YES1");
//		delay_ms(500);
		//u3_printf("slow");
		glHello_control.linkInform.findLineWays = FL_DownPlatform; 
		findLineFlag = 0;
		flag=2;
	}
		else if(2==flag&&0==PES_Platform)  
		{
			flag=3;	
		}
		else if(1==PES_Platform && 3==flag)
	{
		//u3_printf("finish");
//		speedAdjustment(0,0);
//		delay_ms(500);
//		Gui_DrawFont_GBK16(0,1,BLUE,WHITE,"YES3");
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = save; 
		findLineFlag = 0;
		flag = 0;
		return 1;
	}
		return 0;
}
/***********************************************************************************************************/

/*

* 函数介绍：定时(用于2-5减速板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME_1()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(gl_time > 200)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}
		
	return 0;

}

/*

* 函数介绍：定时(用于26-27减速板)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_TIME_2()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(1==flag && gl_time > 200)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=2;
	}
	if(2==flag && 0==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=3;
	}
	if(3==flag &&1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag=0;
		return 1;
	}
		
	return 0;

}







/**************************************************梯形景点*********************************************************/
/*

* 函数介绍：01梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
//u8 BlockHandleMethod_Trapezoid_1()
//{
//	static u8 flag=0;
//	if(0==flag)
//	{
//		Time3(START); //打开定时器
//		gl_time=0;
//		flag=1;
//	}
//	if(1==flag && gl_time>50)
//	{
//		flag = 2;
//		gl_time = 0;
//	}
//	
//	else if(2 == flag)
//	{
//		glHello_control.linkInform.findLineWays = FL_quick; 
//		findLineFlag = 0;
//		flag = 3;
//	}
//	else if(3==flag && gl_time>70)  //加速时间
//	{
//		glHello_control.linkInform.findLineWays = FL_stop;
//	  findLineFlag = 0;
//		Time3(STOP); //关闭定时器
//		gl_time = 0;
//		flag = 4;
//	}
//	else if((4==flag) && (0==PES_H))   //加速完成后开始计时
//	{
//		Time3(START);
//		flag = 5;
//	}
//	else if(5 == flag && gl_time>60)
//	{
//		Time3(STOP);
//		gl_time = 0;
//		flag = 0;
//		speedAdjustment(0,0);
//		return 1;	
//	}
//	return 0;
//}
u8 BlockHandleMethod_Trapezoid_1()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(1==flag && gl_time>40)
	{
		flag = 2;
		gl_time = 0;
	}
	
	else if(2 == flag)
	{
		glHello_control.linkInform.findLineWays = FL_quickest; 
		findLineFlag = 0;
		flag = 3;	

	}
	else if(3==flag && gl_time>TIME_PRAPEZOID_1)   //加速时间
	{
		glHello_control.linkInform.findLineWays = FL_slow;
	  findLineFlag = 0;
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag = 4;
	}
	else if(4==flag && 0==PES_H)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
	  findLineFlag = 0;
		flag = 0;
		return 1;	
	}

	return 0;
}
	

/*

* 函数介绍：02梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Trapezoid_2(void)
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		gl_time=0;
		flag=1;
	}
	if(1==flag && gl_time>40)
	{
		flag = 2;
		gl_time = 0;
	}
	
	else if(2 == flag)
	{
		glHello_control.linkInform.findLineWays = FL_quick; 
		findLineFlag = 0;
		flag = 3;	

	}
	else if(3==flag && gl_time>30)
	{
		glHello_control.linkInform.findLineWays = FL_slow;
	  findLineFlag = 0;
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag = 4;
	}
	else if(4==flag && 0==PES_H)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
	  findLineFlag = 0;
		flag = 0;
		return 1;	
	}

	return 0;
}


/*

* 函数介绍：05、06、07、08梯形景点处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Trapezoid_3()
{
	static u8 flag=0;
	if(0==flag)
	{
		Time3(START); //打开定时器
		flag=1;
		gl_time=0;
	}
	if(gl_time > TIME_PRAPEZOID_3)
	{	
		Time3(STOP); //关闭定时器
		gl_time = 0;
		flag=0;
		return 1;
	}		
	return 0;
}





/*****************************************************斜坡******************************************************/
///*

//* 函数介绍：检测上斜坡(俯仰角)
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(检测到)0（未检测到）
//* 其他		：
//* 作者    ：@断忆

//*/
//static u8 ComingTILT_PITCH()
//{
//	u8 i;
//	for(i=0;i<10;i++)
//		MPU6050_Pose();				//更新欧拉角
//	if(glPitch<-18)
//		return 1;
//	else
//		return 0;
//}


///*
//* 函数介绍：右转倾斜路面路障处理方法
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(路障解决)0（路障未解决）
//* 其他		：
//* 作者    ：@林

//*/
//u8 BlockHandleMethod_GO_Tilt_R()
//{
//	if(1 == identifyALL_Zero())//ComingTILT_PITCH()
//	{ 
//		delay_ms(70);
//    //speedAdjustment(0,0);
//		rotAngle_UR(90);		
//		while(CrossingTILT_ROLL()>12)
//		{
//		return 1;
//	}
//	else return 0;
//}


/*
* 函数介绍：右转倾斜路面路障处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_GO_Tilt_R()
{
//	static u8 flag=0;
//	if(0==flag) 
//	{
//		pes_R=0;
//		flag=1;
//	}
//	if(1==flag && 1 == PES_Platform)//ComingTILT_PITCH()
//	{ 
//	 // while(pes_R==0 || pes_L==0)  speedAdjustment(2000,2080);
//		
//		speedAdjustment(2000,2000);
//		delay_ms(250);
//		rotAngle_UR(90);
//		
//		while(1 == identifyALL_Zero())
//		{
//			speedAdjustment(2000,2080);
//		}
//		glHello_control.linkInform.findLineWays = FL_slow;
//		findLineFlag = 0;
//		flag=0;
//		return 1;
//	}
//	else return 0;
    static u8 flag=0;
	if(0==flag) 
	{

		pes_R=0;
		flag=1;

	}
	else if(1==flag && 1 == PES_Platform)//ComingTILT_PITCH()
	{ 
	 // while(pes_R==0 || pes_L==0)  speedAdjustment(2000,2080);
//	    speedAdjustment(0,0);
//		while(1);
// 		
        Time3(START);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_angle;
		findLineFlag = 0;
		angle_flag = 0;
		flag=2;
	}
	else if(2 == flag && gl_time>13)
	{	 
//		speedAdjustment(0,0);
//		while(1);
		Time3(STOP);
		rotAngle_UR(83);
		while(1 == identifyALL_Zero())
		{
			speedAdjustment(2080,2000);
		}
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	 return 0;
}

/*
* 函数介绍：右转倾斜路面路障处理方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_GO_Tilt_L()
{
	static u8 flag=0;
	if(0==flag) 
	{
		pes_R=0;
		flag=1;
	}
	if(1==flag && 1 == PES_Platform)//ComingTILT_PITCH()
	{ 
	  //while(pes_R==0||pes_L==0)  speedAdjustment(2000,2080);
		
		speedAdjustment(2000,2080);
		delay_ms(200);
		rotAngle_UL(80);
		
		while(1 == identifyALL_Zero())
		{
			speedAdjustment(2000,2080);
		}
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	else return 0;
}



///*

//* 函数介绍：右拐检测上斜坡（翻滚角）
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(检测到)0（未检测到）
//* 其他		：
//* 作者    ：@断忆

//*/
//static u8 ComingTILT_ROLL_R()
//{
// float temp;
// u8 i;
//	for(i=0;i<100;i++)
//		MPU6050_Pose();				//更新欧拉角
//	temp=glRoll;
//	if(temp>10)
//		return 1;
//	else
//		return 0;
//}

///*

//* 函数介绍：检测是否通过斜坡（俯仰角）
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：0(检测到)1（未检测到）
//* 其他		：
//* 作者    ：@断忆

//*/
//static float CrossingTILT_PITCH()
//{
// float temp;
// u8 i;
//	for(i=0;i<10;i++)



///*
//* 函数介绍：倾斜路面路障处理方法（回）
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(路障解决)0（路障未解决）
//* 其他		：
//* 作者    ：@林

//*/
////u8 BlockHandleMethod_BACK_TILT_R()
////{

////	if(1 == ComingTILT_ROLL_R())
////	{
////		glHello_control.linkInform.findLineWays = FL_default;
////		findLineFlag = 0;
////		speedAdjustment(1700,1700);
////		delay_ms(550);
////		rotAngle_Right(70);
////		//rotAngle_UR(90);
////		while(CrossingTILT_PITCH()>10)
////		{
////			speedAdjustment(1400,1400);
////			//u3_printf("glRoll:%0.2f",glRoll);
////		}
////		return 1;
////	}
//// 
////	return 0;
////}


u8 BlockHandleMethod_BACK_TILT_R()
{
//  static u8 flag=0;
//	if(0==flag && 0==PES_Platform)  flag=1;
//	else if(1==flag && 1==PES_Platform)
//	{
//		speedAdjustment(2000,2080);
//		delay_ms(520);
//		rotAngle_UR(70);
//		return 1;
//	}
// 
//	return 0;
	static u8 flag=0;
	if(0==flag) 
	{

		pes_R=0;
		flag=1;

	}
	else if(1==flag && 1 == PES_Platform)//ComingTILT_PITCH()
	{ 
	 // while(pes_R==0 || pes_L==0)  speedAdjustment(2000,2080);
//	    speedAdjustment(0,0);
//		while(1);
// 		
        Time3(START);
		gl_time=0;
		glHello_control.linkInform.findLineWays = FL_angle;
		findLineFlag = 0;
		angle_flag = 0;
		flag=2;
	}
	else if(2 == flag && gl_time>41)
	{	 
//		speedAdjustment(0,0);
//		while(1);
		Time3(STOP);
		rotAngle_UR(84);
     	glHello_control.linkInform.findLineWays = FL_slow;
	  	findLineFlag = 0;
	    flag=0;
		return 1;
	}
	 return 0;
}


///*

//* 函数介绍：左拐检测上斜坡（翻滚角）
//* 输入参数：无
//* 输出参数：无
//* 返回值  ：1(检测到)0（未检测到）
//* 其他		：
//* 作者    ：@断忆

//*/
//static u8 ComingTILT_ROLL_L()
//{
// float temp;
// u8 i;
//	for(i=0;i<100;i++)
//		MPU6050_Pose();				//更新欧拉角
//	temp=glRoll;
//	if(temp<-10)
//		return 1;
//	else
//		return 0;
//}



/*
* 函数介绍：左拐倾斜路面路障处理方法（回）
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：将巡线方法切换成过桥的巡线
* 作者    ：@林

*/
//u8 BlockHandleMethod_BACK_TILT_L()
//{

//	if(1==ComingTILT_ROLL_L())
//	{
//		speedAdjustment(1700,1700);
//		delay_ms(500);
//		rotAngle_Left(90);
//		while(CrossingTILT_PITCH()>10)
//		{
//			speedAdjustment(1400,1500);
//			u3_printf("glRoll:%0.2f",glRoll);
//		}
//		return 1;
//	}
// 
//	return 0;
//}

u8 BlockHandleMethod_BACK_TILT_L()
{

  static u8 flag=0;
	if(0==flag && 0==PES_Platform)  flag=1;
	else if(1==flag && 1==PES_Platform)
	{
		speedAdjustment(2000,2080);
		delay_ms(700);
		//rotAngle_Right(70);
		rotAngle_UL(80);
		return 1;
	}
 
	return 0;
}

/*
* 函数介绍：穿过整个斜坡
* 输入参数：无
* 输出参数：无
* 返回值  ：1(路障解决)0（路障未解决）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_Crossing_All_TILT()
{
//	static u8 flag;
//	if(0==flag && 0==PES_Platform)  flag=1;
//	else if(1==flag && 1==PES_Platform)
//	{	
//		speedAdjustment(2350,2100);
//		#ifdef LED_Debug
//		led_flash();
//		#endif
//		Time3(START); //打开定时器
//		gl_time=0;
//		flag=2;
//	}
//	else if(2==flag && gl_time>50)
//	{
//		while(1 == identifyALL_Zero())
//		{
//			speedAdjustment(2300,2100);
//		}
//		Time3(STOP); //关闭定时器
//		gl_time = 0;
//		#ifdef LED_Debug
//		led_flash();
//		#endif
//		flag=0;
//		
//		return 1;
//	}
//	return 0;
	static u8 flag;
	if(0==flag)  
	{
	     Time3(START);
		gl_time=0;
         flag = 1;
	}     	
	else if(1==flag && gl_time>45)
	{	

//		led_flash();
//		Time3(STOP); //打开定时器
		glHello_control.linkInform.findLineWays = FL_angle;
		findLineFlag = 0;
		angle_flag = 0;
 		flag=2;
		
	}
	else if(2==flag && gl_time>200)
	{
		
		glHello_control.linkInform.findLineWays = FL_slow;
		findLineFlag = 0; 
		Time3(STOP); //关闭定时器

//		speedAdjustment(0,0);
//		while(1);;
//		led_flash();
		flag=0;
		
		return 1;
	}
	return 0;
}



/*************************************************珠峰**********************************************************/
/*

* 函数介绍：上珠峰
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_Peak()
{
	static u8 flag=0;
	//static findLine save;
	if(0==flag && 0==PES_Platform)
	{
	//	save=glHello_control.linkInform.findLineWays;
		flag=1;
	}
	if(1==flag && 1==PES_platform_Shake())
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=2;
	}
	
  if(2==flag && 0==PES_Platform) flag=3;
	if(3==flag && 1==PES_platform_Shake())
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=NFL;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_platform_Shake())
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays=FL_upPeak;
		findLineFlag = 0;
		flag=6;
	}
	if(6==flag && 0==PES_Platform) flag=7;
	if(7==flag && 1==PES_platform_Shake())
	{
		glHello_control.linkInform.findLineWays = NFL;
		flag=0;
		return 1;
	}
	return 0;
	
	
}
/*
* 函数介绍：下珠峰方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/
u8 BlockHandleMethod_downPlatform()
{
	static findLine save;
	static u8 flag=0;
	
	if(flag == 0)
	{
	//	DangerFlag=1;            //将危险信号标志位置为1
		Time3(START);
		gl_time=0;
		save = glHello_control.linkInform.findLineWays;
		glHello_control.linkInform.findLineWays =NFL_slow;
		findLineFlag = 0;
		flag = 1;
	}
	else if(1==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform)  flag=3;
	else if(1==PES_Platform && 3==flag)
	{

		glHello_control.linkInform.findLineWays = NFL_slow; 
		findLineFlag = 0;
		flag = 4;

	}
	else if(4==flag && 0==PES_Platform) flag=5;
	else if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays = FL_downPeak; 
		findLineFlag = 0;
		flag=6;
	}
	else if(6==flag && 0==PES_Platform)	flag=7;
	else if(7==flag && 1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays=save;
		findLineFlag = 0;
		flag=0;
		return 1;
	}
	else if(gl_time>1000) 
	{
		if(1==danger24_23())
		{
			Time3(STOP); //关闭定时器
			gl_time = 0;
		}
	}
		return 0;
//  static findLine save;
//	static u8 flag=0;
//	
//	if(flag == 0)
//	{
////	DangerFlag=1;            //???￡??D?o?±ê???????a1
//		Time3(START);
//		gl_time=0;
//		save = glHello_control.linkInform.findLineWays;
//		glHello_control.linkInform.findLineWays =NFL;
//		flag = 1;
//	}
//	else if(1==flag && 1==PES_Platform)
//	{

//		glHello_control.linkInform.findLineWays = FL_downPeak; 
//		findLineFlag = 0;
//		flag=2;
//	}
//	else if(2==flag &&gl_time>150)//
//	{
//       glHello_control.linkInform.findLineWays = FL_slow_angle; 
//		findLineFlag = 0;
//		angle_flag = 0;
//		flag = 3;
//	}
//	else if(3==flag&&gl_time>325)//
//		{

//		glHello_control.linkInform.findLineWays = FL_downPeak; 
//		findLineFlag = 0;
//	    flag=4;
//	   }

//	else if(4 == flag && 0==PES_Platform)  flag = 5;
//	else if(5 == flag && 1==PES_Platform)
//	{
//		glHello_control.linkInform.findLineWays=save;
//		findLineFlag = 0;
//		flag = 0;
//		return 1;
//	}	
//	else if(gl_time>650)
//	{
//		if(1==danger24_23())
//		{
//			Time3(STOP); 
//			gl_time = 0;
//		}
//	}
//		return 0;

}

//***************************************************减速板****************************************//
/*

* 函数介绍：过减速板1(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_S_BOARD_1()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
		save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	else if(1==flag&&1==PES_Platform) 
	{
		glHello_control.linkInform.findLineWays =FL_slow;
		findLineFlag = 0;
//		speedAdjustment(0,0);
//		delay_ms(500);
		Time3(START);
		gl_time=0;
		flag=2;
	}
	else if(2==flag&&gl_time>87)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =save;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=0;
		return 1;
	}
	return 0;
}

/*

* 函数介绍：过减速板2(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_S_BOARD_2()
{
//	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
	//	save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	if(1==flag&&0==PES_Platform) flag=2;
	if(2==flag&&1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_slow;
		findLineFlag = 0;
		Time3(START);
		gl_time=0;
		flag = 3;
	}
	if(3==flag&&gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_default;
		findLineFlag = 0;
		Time3(STOP);
		gl_time=0;
		flag=0;
		return 1;
	}
	return 0;
}

/*

* 函数介绍：从26到27(用底下光电开关)
* 输入参数：无
* 输出参数：无
* 返回值  ：1(检测到)0（未检测到）
* 其他		：
* 作者    ：@林

*/
u8 BlockHandleMethod_26_27()
{
	static findLine save;
	static u8 flag=0;
	if(0==flag)
	{
		save = glHello_control.linkInform.findLineWays;
		flag = 1;
	}
	if(1==flag&&0==PES_Platform) flag=2;
	if(2==flag&&1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_slowest;
		findLineFlag = 0;
		led_flash();
		Time3(START);
		gl_time=0;
		flag = 3;
	}
	if(3==flag&&gl_time>150)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =save;
		findLineFlag = 0;
		led_flash();
		Time3(STOP);
		gl_time=0;
		flag=4;
	}
	if(4==flag && 0==PES_Platform) flag=5;
	if(5==flag && 1==PES_Platform)
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
		glHello_control.linkInform.findLineWays =FL_upPeak;
		findLineFlag = 0;
	//	led_flash();
		flag=6;
	}
	if(6==flag && 0==PES_Platform) flag=7;
	if(7==flag && 1==PES_Platform) 
	{
//		speedAdjustment(0,0);
//		delay_ms(500);
	//	led_flash();
		flag=0;
		return 1;
	}
	return 0;
}


/*

* 函数介绍：过限高障碍
* 输入参数：无
* 输出参数：无
* 返回值  ：1（到达路障）0（未到达路障）
* 其他		：无
* 作者    ：@断忆

*/
u8 LimtdeHeight_Method()
{
	static u8 flag=0;
	if(flag == 0)
	{
	  Time3(START);
		gl_time = 0;
		sgAngleControl(BODY,B_DOWN);
		flag = 1;
	}
	else if(flag == 1&&gl_time>210)
	{
		Time3(STOP);
		sgAngleControl(BODY,B_UP);
		flag = 0; 
		return 1;
	}
  return 0;
}



