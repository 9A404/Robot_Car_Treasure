#include "carpark.h"
#include "usart3.h"

/*

* 函数介绍：默认停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_default()
{
	delay_ms(400);
	return 1;
}

/*

* 函数介绍：右边光电传感器停车方法
* 输入参数：
* 输出参数：
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesR()
{
	static u8 flag=0;
//			if(flag ==0)
//		{	
//			glHello_control.linkInform.findLineWays = FL_stop;
//			findLineFlag = 0;
//			flag = 1;
//		}
//		if(0==PES_R && 1==flag)
//		{
//			speedAdjustment(0,0);
//			delay_ms(10);
//			flag = 0;
//			return 1 ;
//		}
	if(FL_slow == glHello_control.linkInform.findLineWays)
	{
		if(flag ==0)
		{	
			glHello_control.linkInform.findLineWays = FL_stop;
			findLineFlag = 0;
			flag = 1;
		}
		if(0==PES_R && 1==flag)
		{
			speedAdjustment(0,0);
			delay_ms(10);
			led_flash();
			flag = 0;
			return 1 ;
		}
	}
	else 
	{
		if(flag ==0)
		{	
			speedAdjustment(-2000,-2000);
			delay_ms(20);
			glHello_control.linkInform.findLineWays = FL_stop;
			findLineFlag = 0;
			flag = 1;
		}
		if(0==PES_R && 1==flag)
		{
			speedAdjustment(0,0);
			delay_ms(10);		
			flag = 0;
			return 1 ;
		}
	}
	
	return 0;	
}

/*

* 函数介绍：左边光电传感器停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesL()
{
	static u8 flag=0;
	if(flag ==0)
	{
		speedAdjustment(0,0);
		delay_ms(10);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
		speedAdjustment(0,0);
		delay_ms(10);
		flag=0;
		return 1;
	}
	
	return 0;	
}



/*

* 函数介绍：默认停车方法
* 输入参数：无
* 输出参数：无
* 返回值  ：1(完成)0（未完成）
* 其他		：
* 作者    ：@断忆

*/

u8 parkMethod_pesPlatform(controlCenterTypeDef *controlp)
{
//	char buff[2];
//	u8 i=0,j=0,k=0;
	static u8 flag=0,flag1=0;
	#ifdef BlueTooth
		if(0==flag)
		{
//		speedAdjustment(0,0);
//		delay_ms(500);
			glHello_control.linkInform.findLineWays = NFL;//盲走
			if(QR_code_flag==0&&controlp->curNode==4)  
			{
			//	Lcd_Clear(WHITE);
				u3_printf("1");              //在2号平台发送1扫描二维码
				flag1=1;
			}
			else if(controlp->curNode==QR_code_u3_printf(&glHello_control))        
			{
				flag1=1;
				/*  在2号平台扫码后QR_code_flag置为1*/
				if(1==QR_code_flag && 1==RunMethod_Check)u3_printf("1");  
				if(1==QR_code_flag && 2==RunMethod_Check) u3_printf("1"); 
				
				/*  在3或4号平台扫码后QR_code_flag置为2*/                                                                                                                                                                                                  
				if(2==QR_code_flag && 2==RunMethod_Check) u3_printf("1");
				treasure_flag=1;
			}
			flag=1;
		}
		if(1==flag&&0==PES_H)
		{
//		speedAdjustment(0,0);
//		delay_ms(500);
			glHello_control.linkInform.findLineWays = NFL_slow;
			flag=2;
		}
		if(2==flag&&1==Collision)//Collision是否撞墙？
		{
			delay_ms(100);
			flag=3;
		}
		else if(3==flag)
		{	
			speedAdjustment(-1300,-1300);
			delay_ms(320);	
			speedAdjustment(0,0);
			sgAngleControl(L_ARM,L_UP);
			delay_ms(200);
			sgAngleControl(L_ARM,L_DOWN);
			sgAngleControl(R_ARM,R_UP);
			delay_ms(200);
			sgAngleControl(R_ARM,R_DOWN);
			delay_ms(200);
			if(flag1)       //用于扫不到码不走
			{
				while(!(USART3_RX_STA&0x8000));
				flag1=0;
			}
			#ifdef _NEW_MPU6050_
			if(controlp->curNode==24||controlp->curNode==27)
			  rotAngle_Right(180);
			else rotAngle_Right(180);
			//rotAngle_Right(180);
			#else
			rotAngle_Left(180);
			#endif
			flag=4;
		}
		else if(4==flag)
		{
			if(treasure_flag)       //如果宝物在这个平台抬手
			{
				speedAdjustment(0,0);
				sgAngleControl(L_ARM,L_UP);
				sgAngleControl(R_ARM,R_UP);
				delay_ms(200);
				sgAngleControl(L_ARM,L_DOWN);
				sgAngleControl(R_ARM,R_DOWN);
				delay_ms(200);	
			#ifdef AUTO_Treasure        //如果定义了根据宝物改变路线
				if(Treasure_all_Flag != 1)
				 CheckTreasureNode(&glHello_control);
			#endif
				treasure_flag=0;
				flag=0;
				return 1;
			}
			else         //如果在宝物不在这个平台倒车转弯
			{	
				flag=0;
				return 1;
			}
		}
		#endif
	#ifdef OTG
		if(0==flag)
		{
//		speedAdjustment(0,0);
//		delay_ms(500);
			glHello_control.linkInform.findLineWays = NFL;
			if(QR_code_flag==0&&controlp->curNode==4)  
			{
			//	Lcd_Clear(WHITE);
				printf("1");              //在2号平台发送1扫描二维码
			}
			else if(controlp->curNode==QR_code_printf(&glHello_control))        
			{
				/*  在2号平台扫码后QR_code_flag置为1*/
				if(1==QR_code_flag && 1==RunMethod_Check)printf("1");  
				if(1==QR_code_flag && 2==RunMethod_Check) printf("1"); 
				
				/*  在3或4号平台扫码后QR_code_flag置为2*/
				if(2==QR_code_flag && 2==RunMethod_Check) printf("1");
				treasure_flag=1;
			}
			flag=1;
		}
		if(1==flag&&0==PES_H)
		{
//		speedAdjustment(0,0);
//		delay_ms(500);
			glHello_control.linkInform.findLineWays = NFL_slow;
			flag=2;
		}
		if(2==flag&&1==Collision)
		{
			delay_ms(100);
			flag=3;
		}
			else if(3==flag)
		{
			speedAdjustment(-1300,-1300);
			delay_ms(270);	
			speedAdjustment(0,0);
			sgAngleControl(L_ARM,L_UP);
			delay_ms(400);
			sgAngleControl(L_ARM,L_DOWN);
			sgAngleControl(R_ARM,R_UP);
			delay_ms(400);
			sgAngleControl(R_ARM,R_DOWN);
			delay_ms(400);
			rotAngle_Right(180);
			flag=4;
		}
		else if(4==flag)
		{
			if(treasure_flag)       //如果宝物在这个平台抬手
			{
				speedAdjustment(0,0);
				sgAngleControl(L_ARM,L_UP);
				sgAngleControl(R_ARM,R_UP);
				delay_ms(400);
				sgAngleControl(L_ARM,L_DOWN);
				sgAngleControl(R_ARM,R_DOWN);
				delay_ms(400);	
//				speedAdjustment(-1300,-1300);
//				delay_ms(270);
			#ifdef AUTO_Treasure        //如果定义了根据宝物改变路线
				CheckTreasureNode(&glHello_control);
			#endif
				treasure_flag=0;
				flag=0;
				return 1;
			}
			else         //如果在宝物不在这个平台倒车转弯
			{
				flag=0;
				return 1;
			}
		}
	#endif
	return 0;

}



