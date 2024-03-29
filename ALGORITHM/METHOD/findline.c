#include "findline.h"


/*

* 函数介绍：缺省巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_default()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,3500,200,0,500);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,3300,3300); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//位置式改变电机速度

}

/*

* 函数介绍：过桥巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_brige()
{
	int rank;
	if(findLineFlag == 0)   //保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,14,2500,200,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2200,2200); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank_Brige(glsensor_dig_value); 															//对数字量进行等级划分
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：上桥斜坡时的巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_brige_up()
{
	int rank;
	if(findLineFlag == 0)   //保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,14,2500,400,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1800,1800); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank_Brige_Up(glsensor_dig_value); 															//对数字量进行等级划分
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：下桥斜坡时的巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_brige_down()
{
	int rank;
	if(findLineFlag == 0)   //保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,14,2500,400,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1500,1500); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank_Brige_Down(glsensor_dig_value); 															//对数字量进行等级划分
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}


/*

* 函数介绍：慢速度巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_slow()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,2500,200,0,100);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2200,2200); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：中速度巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_middle()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,2500,200,0,600);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,4500,4500); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：上台巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_UpPlatform(void)
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,2500,300,0,200);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2000,2000); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：下台巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_DownPlatform(void)
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,1500,200,0,200);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1300,1300); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：快速度巡线方法（用于加速）
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_quick()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,4000,200,0,1000);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,5000,5000); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：超快速度巡线方法（用于加速）
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_quickest()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,5500,250,0,2800);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,6500,6500); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value&0x7FE);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}



/*

* 函数介绍：复杂节点巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_node()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,2000,200,0,400);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2500,2500); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value&0X1F0);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：43_44巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_43_44()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,21,2000,200,0,400);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2400,2600); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value&0X1F0);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：圆巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_circular()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,22,2000,300,0,400);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1800,1900); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：圆巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_16_44()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,10,2000,200,0,500);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1500,1500); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value&0xFC0);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}
/*

* 函数介绍：停车巡线方法(主要用于节点停车和撞梯台)
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_stop()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,300,150,0,200);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1200,1200); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：上珠峰巡线方法()
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_upPeak()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,3500,400,0,100);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,3000,3000); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}


/*

* 函数介绍：下珠峰巡线方法()
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_downPeak()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,2000,400,0,100);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1400-270,1380-270); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}












/*

* 函数介绍：倒车巡线方法(主要用于节点停车和撞梯台)（2017-7-21测试未通过）
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_back()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,4000,250,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,-2000,-2000); 																				//对初始速度进行设定
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=-sensorDigitalRank(glsensor_dig_value);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}


/*

* 函数介绍：偏左巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_left()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,4000,120,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1400,2080); 																				//对初始速度进行设定2200+200
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value & 0xF00);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//位置式改变电机速度

}

/*

* 函数介绍：偏右巡线方法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 其他    ：每个方法最主要的区别：1、glmotorSpeed初始速度 2、glsensorPID的P I D三个参数
* 作者    ：@断忆

*/
void flMethod_right()
{
	int rank;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,20,3500,80,0,0);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2080,1400); 																				//对初始速度进行设定2200+200
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
	rank=sensorDigitalRank(glsensor_dig_value & 0x00F);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//位置式改变电机速度

}

/*

* 函数介绍：循角度跑法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 作者    ：你猜

*/
void flMethod_NFL()
{
	int rank;
	float err;
	static u8 flag=0;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,18,2600,200,0,200);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,2200,2200); 																				//对初始速度进行设定
		findLineFlag=1;

	}
	//glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
       if(angle_flag == 0)
		  { 
				MPU6050_Pose_usart();
				glsensor_angle=glYaw;
				angle_flag = 1;
		   }  
        MPU6050_Pose_usart();		  
	    err = errCalculation(glYaw,glsensor_angle);
//		u3_printf("%d\n",glsensor_angle);
		rank=rotangle_run(err);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);	
}


/*

* 函数介绍：循角度跑法
* 输入参数：无
* 输出参数：无
* 返回值  ：
* 作者    ：你猜

*/
void flMethod_NFL_slow()
{
	int rank;
	float err;
	static u8 flag=0;
	if(findLineFlag == 0)//保证每个路段初始化一次
	{
		PID_Init(&glsensorPID,18,2600,200,0,200);																					//对速度PID的参数进行初始化设置
		speedRec_Init(&glmotorSpeed,1500,1500); 																				//对初始速度进行设定
		findLineFlag=1;

	}
	//glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//与阈值比较后将模拟量转化成数字量
       if(angle_flag == 0)
		  { 
				MPU6050_Pose_usart();
				glsensor_angle=glYaw;
				angle_flag = 1;
		   }  
        MPU6050_Pose_usart();		  
	    err = errCalculation(glYaw,glsensor_angle);
//		u3_printf("%d\n",glsensor_angle);
		rank=rotangle_run(err);                                    //分级
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //速度位置式PID输出
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);	
}



