#include "seeknodeway.h"

///*

//* 函数介绍：计算数字量中1个数
//* 输入参数：digital（待计算的数字量）
//* 输出参数：无
//* 返回值  ：1的个数
//* 作者    ：@断忆

//*/

//static u8 calculateNum(u16 digital)
//{
//	u8 i;
//	u8 temp=0;
//	for(i=0;i<NUM_OF_SENSOR;i++)
//	{
//		if(digital & (0x001<<i) )
//			temp++;
//	}
//	return temp;
//}

/*

* 函数介绍：缺省找点方法
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：“1”的个数为4时将flag置1
													下一次检测到“1”的个数为5时候判断为此处为节点 
* 作者    ：@断忆

*/

u8 seekNodeMethod_default()
{
//	static u8 flag=0;
//	if(4 == calculateNum(glsensor_dig_value) && (flag==0))
//		flag = 1;
//	else if((1 == flag) && (3 < calculateNum(glsensor_dig_value)))
//	{
//		flag = 0;
//		return 1;
//	}
//	return 0;
	 if(3 < calculateNum(glsensor_dig_value))
	 {
		return 1;
	 }
	 return 0;
			
}
/*

* 函数介绍：传感器最左边找点
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：传感器最右的为1时为找到点
* 作者    ：@袁梓聪

*/

u8 seekNodeMethod_digL()
{

	if(glsensor_dig_value&0x800)
		return 1;
	return 0;	
}

/*

* 函数介绍：传感器最右边找点
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：传感器最右的为1时为找到点
* 作者    ：@袁梓聪

*/

u8 seekNodeMethod_digR()
{

	if(glsensor_dig_value&0x001)
		return 1;
	return 0;	
}

/*

* 函数介绍：特殊路段找点
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：传感器最右的为1时为找到点
* 作者    ：@袁梓聪

*/

u8 seekNodeMethod_7_6_15()
{

	static u8 flag=0;
	if(seekNodeMethod_digR()){
		flag=1;
	}
	else if(1==flag){
		rotAngle_Right(45);
		flag=0;
		return 1;
	}
	return 0;	
}
/*

* 函数介绍：特殊路段找点
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：传感器最左的为1时为找到点
* 作者    ：@袁梓聪

*/

u8 seekNodeMethod_6_15_37()
{
	static u8 flag=0;
	if(seekNodeMethod_digR()){
		flag=1;
	}
	else if(1==flag){
		rotAngle_Left(30);
		flag=0;
		return 1;
	}
	return 0;	
}

///*

//* 函数介绍：左边光电找点方法
//* 输入参数：
//* 输出参数：
//* 返回值  ：1(找到节点)0（没有找到节点）
//* 其他		：找点方法思路：根据左边光电传感器判断节点
//* 作者    ：@断忆

//*/

//u8 seekNodeMethod_pesL()
//{
//	if(0==PES_L)
//	{	
//			return 1;
//	}
//		
//	return 0;
//	
//}

///*

//* 函数介绍：右边光电找点方法
//* 输入参数：
//* 输出参数：
//* 返回值  ：1(找到节点)0（没有找到节点）
//* 其他		：找点方法思路：根据右边光电传感器判断节点
//* 作者    ：@断忆

//*/

//u8 seekNodeMethod_pesR()
//{
//	if(0==PES_R)
//	{	
//			return 1;
//	}
//		
//	return 0;
//	
//}

/*

* 函数介绍：左边光电找点方法(一定要用中断，不然有几率漏点)
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：根据左边光电传感器判断节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_pesL()
{
	static u8 flag=0;
	if(0 == flag)
	{
		pes_L=0;
		//pesLSwitch(STOP);//开中断
		flag = 1;
	}
	if(1==pes_L && 1==flag)
	{	
		//pesLSwitch(STOP);//关中断
		pes_L=0;
		flag = 0;	
		return 1;
	}
		
	return 0;
	
}

/*

* 函数介绍：右边光电找点方法(一定要用中断，不然有几率漏点)
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：根据右边光电传感器判断节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_pesR()
{
	static u8 flag=0;
	if(0 == flag)
	{
		pes_R=0;
		//pesRSwitch(START);//开中断
		flag = 1;
	}
	if(1==pes_R && 1==flag)
	{	
	//	pesRSwitch(STOP);//关中断
		pes_R=0;
		flag = 0;	
		return 1;
	}
		
	return 0;
	
}

/*

* 函数介绍：4节点找点方法(上台)
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_4()
{
	static u8 flag=0;
	if(mpu6050_flag == 0 && 0==flag)
	{	
		U_Dswitch = 1;//标志中断运行上台程序
		mpu6050_samping(START);
		flag=1;
		u3_printf("1\n");
	
	}
	
	if(mpu6050_flag == 1&&1==flag)
	{
		flag=2;
		u3_printf("2\n");
		//sgAngleControl(R_ARM,DOWM);//放下舵机	
		glHello_control.linkInform.findLineWays = NFL;
	}
	if(mpu6050_flag == 2&&flag==2)
	{
		flag=0;
		u3_printf("3\n");
		mpu6050_flag = 0;
		U_Dswitch = 0;//让上台程序不运行
		mpu6050_samping(STOP);
		//u3_printf ("\na %0.2f\n",glPitch-glPitchbuff[0]);
		
		//delay_ms(10);  //保证车子在台中
		return 1;
	}
	return 0;
	
}

/*

* 函数介绍：找点方法(上台):利用光电开关上台
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_pesPlatform()
{
  static u8 flag=0;	
	
	if(flag==0&&PES_Platform==1)
	{
		Time3(START);
		gl_time=0;
		while(gl_time<10);
		if(PES_Platform==1) 
		{
			Time3(STOP);
		  gl_time=0;
			flag=1;
		}
		else 
		{
			Time3(STOP);
		  gl_time=0;
			flag=0;
		}
	}	
	//if (1==flag&&PES_Platform==0) flag = 2;
	else if (1==flag) 
	{
		glHello_control.linkInform.findLineWays = FL_slow;
	  findLineFlag = 0;
		flag=2;
	}
	else if(2==flag&&0==PES_Platform) 
	{
	flag=3;

	}
	else if(3==flag&&1==PES_Platform)
	{
		glHello_control.linkInform.findLineWays = NFL;
		flag=0;
		return 1;
	}		
	return 0;
	
}


/*

* 函数介绍：10节点找点方法
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_10()
{
	if(calculateNum(glsensor_dig_value) > 4)
	{	
			return 1;
	}
		
	return 0;
	
}


/*

* 函数介绍：	梯形景点找点方法（利用碰撞开光）
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_Collision()
{
//	static u8 flag=0;
//	if(0==flag&&0==Collision) flag=1;
//	else if(1==flag&&1==Collision)
//	{
//		flag=0;
//		return 1;
//	}
	if(1==Collision) 
	{
		delay_ms(100);
		speedAdjustment(-2000,-2000);	
		delay_ms(200);
		return 1;
	}
		
	return 0;
	
}

/*

* 函数介绍：	梯形景点找点方法（利用碰撞开光）
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@断忆

*/

u8 seekNodeMethod_Collision_1()
{
//	static u8 flag=0;
//	if(0==flag&&0==Collision) flag=1;
//	else if(1==flag&&1==Collision)
//	{
//		flag=0;
//		return 1;
//	}
	if(1==Collision) return 1;
		
	return 0;
	
}

/*

* 函数介绍：跷跷板找点（利用下面光电开光）
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@林

*/

u8 seekNodeMethod_SeeSaw()
{

//	if(1==PES_Platform) 
//	{
//		speedAdjustment(0,0);	
//		delay_ms(200);
//		speedAdjustment(0,1900);
//		delay_ms(350);
//		return 1;
//	}
//		
//	return 0;
	    int err,speed;
		if(1==PES_Platform) 
	   {
		speedAdjustment(0,0);
		delay_ms(200);
		PID_Init(&glrotAnglePID,0,0,0,0,0);//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
		err=errCalculation(glYaw,angle_read);
		if(err<0)err=-err;
		while(err > 2)
		{
			#ifdef _NEW_MPU6050_
			MPU6050_Pose_usart();
			#else 
			for(int i=0;i<50;i++) MPU6050_Pose();
			#endif
		    err = errCalculation(glYaw,angle_read);
		    if(err<0)err=-err;
		
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(0,speed+2500);
		}
//		speedAdjustment(0,0);
//		while(1);
		return 1;
	}
		
	return 0;
}

/*

* 函数介绍：跷跷板回去找点（利用下面光电开光）
* 输入参数：
* 输出参数：
* 返回值  ：1(找到节点)0（没有找到节点）
* 其他		：找点方法思路：检测上到平台认为到达节点
* 作者    ：@袁梓聪

*/

u8 seekNodeMethod_SeeSaw_back()
{

//	if(1==PES_Platform) 
//	{
//		speedAdjustment(0,0);	
//		delay_ms(200);
//		speedAdjustment(0,1900);
//		delay_ms(350);
//		return 1;
//	}
//		
//	return 0;
	    int err,speed;
		if(1==PES_Platform) 
	   {
		speedAdjustment(0,0);
		delay_ms(200);
		PID_Init(&glrotAnglePID,0,0,0,0,0);//对转弯PID的参数进行初始化设置，旋转PID直接传误差值
		err=errCalculation(glYaw,angle_read_back);
		if(err<0)err=-err;
		while(err > 2)
		{
			#ifdef _NEW_MPU6050_
			MPU6050_Pose_usart();
			#else 
			for(int i=0;i<50;i++) MPU6050_Pose();
			#endif
		    err = errCalculation(glYaw,angle_read_back);
		    if(err<0)err=-err;
		
		speed=positionPIDCalc_rotAngle(&glrotAnglePID,err); //速度位置式PID输出,直接传入误差参数
		speedAdjustment(0,speed+2500);
		}
//		speedAdjustment(0,0);
//		while(1);
		return 1;
	}
		
	return 0;
}


