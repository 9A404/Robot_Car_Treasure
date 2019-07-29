#include "carpark.h"
#include "usart3.h"

/*

* �������ܣ�Ĭ��ͣ������
* �����������
* �����������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/

u8 parkMethod_default()
{
	delay_ms(300);
	return 1;
}

/*

* �������ܣ��ұ߹�紫����ͣ������
* ���������
* ���������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

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

* �������ܣ���߹�紫����ͣ������
* �����������
* �����������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

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

* �������ܣ�Ĭ��ͣ������
* �����������
* �����������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

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
			glHello_control.linkInform.findLineWays = NFL;
			if(QR_code_flag==0&&controlp->curNode==4)  
			{
			//	Lcd_Clear(WHITE);
				u3_printf("1");              //��2��ƽ̨����1ɨ���ά��
				flag1=1;
			}
			else if(controlp->curNode==QR_code_u3_printf(&glHello_control))        
			{
				flag1=1;
				/*  ��2��ƽ̨ɨ���QR_code_flag��Ϊ1*/
				if(1==QR_code_flag && 1==RunMethod_Check)u3_printf("1");  
				if(1==QR_code_flag && 2==RunMethod_Check) u3_printf("1"); 
				
				/*  ��3��4��ƽ̨ɨ���QR_code_flag��Ϊ2*/
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
		if(2==flag&&1==Collision)
		{
			delay_ms(100);
			flag=3;
		}
		else if(3==flag)
		{	
			speedAdjustment(-1300,-1315);
			delay_ms(270);	
			speedAdjustment(0,0);
			sgAngleControl(L_ARM,L_UP);
			delay_ms(200);
			sgAngleControl(L_ARM,L_DOWN);
			sgAngleControl(R_ARM,R_UP);
			delay_ms(200);
			sgAngleControl(R_ARM,R_DOWN);
			delay_ms(200);
//			if(flag1)       //����ɨ�����벻��
//			{
//				while(!(USART3_RX_STA&0x8000));
//				flag1=0;
//			}
			#ifdef _NEW_MPU6050_
			rotAngle_Left(180);
//			rotAngle_Right(180);
			#else
			rotAngle_Left(180);
			#endif
			flag=4;
		}
		else if(4==flag)
		{
			if(treasure_flag)       //������������ƽ̨̧��
			{
				speedAdjustment(0,0);
				sgAngleControl(L_ARM,L_UP);
				sgAngleControl(R_ARM,R_UP);
				delay_ms(200);
				sgAngleControl(L_ARM,L_DOWN);
				sgAngleControl(R_ARM,R_DOWN);
				delay_ms(200);	
			#ifdef AUTO_Treasure        //��������˸��ݱ���ı�·��
				if(Treasure_all_Flag != 1)
				 CheckTreasureNode(&glHello_control);
			#endif
				treasure_flag=0;
				flag=0;
				return 1;
			}
			else         //����ڱ��ﲻ�����ƽ̨����ת��
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
				printf("1");              //��2��ƽ̨����1ɨ���ά��
			}
			else if(controlp->curNode==QR_code_printf(&glHello_control))        
			{
				/*  ��2��ƽ̨ɨ���QR_code_flag��Ϊ1*/
				if(1==QR_code_flag && 1==RunMethod_Check)printf("1");  
				if(1==QR_code_flag && 2==RunMethod_Check) printf("1"); 
				
				/*  ��3��4��ƽ̨ɨ���QR_code_flag��Ϊ2*/
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
			if(treasure_flag)       //������������ƽ̨̧��
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
			#ifdef AUTO_Treasure        //��������˸��ݱ���ı�·��
				CheckTreasureNode(&glHello_control);
			#endif
				treasure_flag=0;
				flag=0;
				return 1;
			}
			else         //����ڱ��ﲻ�����ƽ̨����ת��
			{
				flag=0;
				return 1;
			}
		}
	#endif
	return 0;

}
/*

* �������ܣ��ұ߹�紫����ǰ��û����ͣ������
* ���������
* ���������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/

u8 parkMethod_pesR_noline()
{
	static u8 flag=0;
	if(flag ==0)
	{	
//		/*��ת����ɲ��*/
//		speedAdjustment(-3500,-3500);
//		delay_ms(20);
		glHello_control.linkInform.findLineWays = NFL_slow;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		/*ͣ��*/
		speedAdjustment(-3500,-3500); 
		delay_ms(25);
//		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}
/*

* �������ܣ���߹�紫����ǰ��û����ͣ������
* ���������
* ���������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/

u8 parkMethod_pesL_noline()
{
	static u8 flag=0;
	if(flag ==0)
	{	
//		/*��ת����ɲ��*/
//		speedAdjustment(-3500,-3500);
//		delay_ms(20);
		glHello_control.linkInform.findLineWays = NFL_slow;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{
		/*ͣ��*/
		speedAdjustment(-3500,-3500); 
		delay_ms(25);
//		speedAdjustment(0,0);
//		delay_ms(500);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}	

/*

* �������ܣ���߹�紫������ʱͣ������
* �����������
* �����������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/
u8 parkMethod_pesL_Delay(int time)
{
	static u8 flag=0;
	if(flag ==0)
	{
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
		glHello_control.linkInform.findLineWays = NFL;
		findLineFlag = 0; 
		delay_ms(time);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}

/*

* �������ܣ��ұ߹�紫����ʱͣ������
* ���������
* ���������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/
u8 parkMethod_pesR_Delay(int time)
{
	static u8 flag=0;
	if(flag ==0)
	{	
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		glHello_control.linkInform.findLineWays = NFL;
		findLineFlag = 0; 
		delay_ms(time);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}

/*

* �������ܣ���߹�紫����ͣ������(����ת����)
* �����������
* �����������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/

u8 parkMethod_pesL_back()
{
	static u8 flag=0;
	if(flag ==0)
	{
		/*��ת����ɲ��*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_L && 1==flag)
	{	
		/*ͣ��*/
		speedAdjustment(-2000,-2000);
		delay_ms(40);
		speedAdjustment(0,0);
		flag = 0;
		delay_ms(40);		
		//delay_ms(1000);
		//delay_ms(1000);
		return 1;
	}
	
	return 0;	
}


/*

* �������ܣ��ұ߹�紫����ͣ������������ת���٣�
* ���������
* ���������
* ����ֵ  ��1(���)0��δ��ɣ�
* ����		��
* ����    ��@����

*/

u8 parkMethod_pesR_back()
{
	static u8 flag=0;
	if(flag ==0)
	{	
		/*��ת����ɲ��*/
		speedAdjustment(-3500,-3500);
		delay_ms(20);
		glHello_control.linkInform.findLineWays = FL_stop;
		findLineFlag = 0;
		flag = 1;
	}
	if(0==PES_R && 1==flag)
	{
		/*ͣ��*/
		speedAdjustment(-3500,-3500); 
		delay_ms(15);
		speedAdjustment(0,0);
		flag = 0;
		return 1 ;
	}
	
	return 0;	
}


