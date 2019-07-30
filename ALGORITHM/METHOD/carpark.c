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
	delay_ms(700);
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
	#ifdef PHONE
		static u8 flag=0,flag1=0;
		if(0==flag)
		{
			glHello_control.linkInform.findLineWays = NFL;
			if(Treasure_code[0]==0){
				if(QR_code_flag==0&&controlp->curNode==4)  
				{
					//get_from_phone();
					u3_printf("1");              //��2��ƽ̨����1ɨ���ά��
					flag1=1;
				}
				else if(controlp->curNode==QR_code_u3_printf(&glHello_control))        
				{
					//get_from_phone();
					flag1=1;
					/*  ��2��ƽ̨ɨ���QR_code_flag��Ϊ1*/
					if(1==QR_code_flag && 1==RunMethod_Check) u3_printf("1");  
					if(1==QR_code_flag && 2==RunMethod_Check) u3_printf("1"); 
					
					/*  ��3��4��ƽ̨ɨ���QR_code_flag��Ϊ2*/
					if(2==QR_code_flag && 2==RunMethod_Check) u3_printf("1");
					treasure_flag=1;
				}
			}else if(controlp->curNode==Treasure_code[0]||controlp->curNode==Treasure_code[1]||controlp->curNode==Treasure_code[2]){
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
			speedAdjustment(-1100,-1100);
			delay_ms(270);	
			speedAdjustment(0,0);
			sgAngleControl(L_ARM,L_UP);
			delay_ms(200);
			sgAngleControl(L_ARM,L_DOWN);
			sgAngleControl(R_ARM,R_UP);
			delay_ms(200);
			sgAngleControl(R_ARM,R_DOWN);
			delay_ms(200);
			if(flag1)       //����ɨ�����벻��
			{
				Time3(START);
				gl_time = 0;
				while(!(USART3_RX_STA&0x8000)){
					if(gl_time==200) 
					{
						//u3_printf("2");
						break;
					}
				}
				Time3(STOP);
				gl_time = 0;
				flag1=0;
			}
			#ifdef _NEW_MPU6050_
			//rotAngle_Left(180);
			rotAngle_Right(180);
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
	
	#ifdef MODULAR
		static u8 flag=0,flag1=0,next_treasure=0;
		if(0==flag)
		{
			glHello_control.linkInform.findLineWays = NFL;
			if(QR_code_flag==0&&controlp->curNode==4)  
			{
				next_treasure=QR_code_u3_print(); 
				flag1=1;
			}
			else if(controlp->curNode==next_treasure){
				flag1=1;
				/*  ��2��ƽ̨ɨ���QR_code_flag��Ϊ1*/
				if(1==QR_code_flag && 1==RunMethod_Check) next_treasure=QR_code_u3_print();
				if(1==QR_code_flag && 2==RunMethod_Check) next_treasure=QR_code_u3_print();
				
				/*  ��3��4��ƽ̨ɨ���QR_code_flag��Ϊ2*/
				if(2==QR_code_flag && 2==RunMethod_Check) next_treasure=QR_code_u3_print();
				treasure_flag=1;
			}
			flag=1;
		}
		if(1==flag&&0==PES_H)
		{
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
			//rotAngle_Left(180);
			rotAngle_Right(180);
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
	return 0;

}



