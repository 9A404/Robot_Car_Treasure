#include "findline.h"

/*

* �������ܣ�ȱʡѲ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_default()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,3500,200,0,500);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,3220,3350);																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ�����Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_brige()
{
	int rank;
	if(findLineFlag == 0)   //��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,14,2500,200,0,0);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2100,2200);																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank_Brige(glsensor_dig_value); 															//�����������еȼ�����
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ�����б��ʱ��Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_brige_up()
{
	int rank;
	if(findLineFlag == 0)   //��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,14,2500,400,0,0);																				//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1900,2000);  																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank_Brige_Up(glsensor_dig_value); 															//�����������еȼ�����
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ�����б��ʱ��Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_brige_down()
{
	int rank;
	if(findLineFlag == 0)   //��֤ÿ��·�γ�ʼ��һ��
	{
				PID_Init(&glsensorPID,14,2500,400,0,0);																						//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,930,1000); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,brige_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank_Brige_Down(glsensor_dig_value); 															//�����������еȼ�����
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}


/*

* �������ܣ����ٶ�Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_slow()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2500,300,0,100);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2150,2200); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ����ٶ�Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_middle()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2500,200,0,600);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,4400,4500); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ���̨Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_UpPlatform(void)
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2000,200,0,200);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1500,1500); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ���̨Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_DownPlatform(void)
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,1500,200,0,300);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1050,1100); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ����ٶ�Ѳ�߷��������ڼ��٣�
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_quick()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,4000,200,0,1000);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,4850,5000); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ������ٶ�Ѳ�߷��������ڼ��٣�
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_quickest()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		
		PID_Init(&glsensorPID,20,5500,250,0,2900);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,6500,6500); 
//		PID_Init(&glsensorPID,20,5500,300,0,2900);																					//���ٶ�PID�Ĳ������г�ʼ������
//		speedRec_Init(&glmotorSpeed,6430,6500);  																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value&0x7FE);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}



/*

* �������ܣ����ӽڵ�Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_node()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2000,200,0,400);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2500,2500); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value&0X1F0);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ�43_44Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_43_44()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,21,2000,200,0,400);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2400,2600); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value&0X1F0);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ�ԲѲ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_circular()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,22,2500,500,0,400);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1800,2000); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ�ԲѲ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_16_44()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,12,2000,600,0,500);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1400,1500); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value&0xFC0);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}
/*

* �������ܣ�ͣ��Ѳ�߷���(��Ҫ���ڽڵ�ͣ����ײ��̨)
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_stop()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,300,150,0,200);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,950,1000);  																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ������Ѳ�߷���()
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_upPeak()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,3000,300,0,150);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2200,2200); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}


/*

* �������ܣ������Ѳ�߷���()
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_downPeak()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2000,400,0,100);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1050,1100); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}



/*

* �������ܣ�����Ѳ�߷���(��Ҫ���ڽڵ�ͣ����ײ��̨)��2017-7-21����δͨ����
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_back()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,4000,250,0,0);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,-2000,-2000); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=-sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}


/*

* �������ܣ�ƫ��Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_left()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,3500,300,0,0);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1000,3000); 																				//�Գ�ʼ�ٶȽ����趨2200+200
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value & 0xF00);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ�ƫ��Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_right()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,3500,200,0,0);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,3000,1000); 																				//�Գ�ʼ�ٶȽ����趨2200+200
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value & 0x00F);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

/*

* �������ܣ�ѭ�Ƕ��ܷ�
* �����������
* �����������
* ����ֵ  ��
* ����    �����

*/
void flMethod_NFL()
{
	int rank;
	float err;
	static u8 flag=0;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,18,2600,200,0,200);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,2300,2400); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;

	}
	//glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	if(angle_flag == 0)
    { 
		MPU6050_Pose_usart();
		glsensor_angle=glYaw;
		angle_flag = 1;
    }  
	MPU6050_Pose_usart();		  
	err = errCalculation(glYaw,glsensor_angle);
//		u3_printf("%d\n",glsensor_angle);
	rank=rotangle_run(err);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);	
}


/*

* �������ܣ�ѭ�Ƕ��ܷ�
* �����������
* �����������
* ����ֵ  ��
* ����    �����

*/
void flMethod_NFL_slow()
{
	int rank;
	float err;
	static u8 flag=0;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,18,2600,200,0,200);		//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1400,1500); 		//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;

	}
	//glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
   if(angle_flag == 0)
	{ 
		MPU6050_Pose_usart();
		glsensor_angle=glYaw;
		angle_flag = 1;
	}  
	MPU6050_Pose_usart();		  
	err = errCalculation(glYaw,glsensor_angle);
//		u3_printf("%d\n",glsensor_angle);
	rank=rotangle_run(err);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);	
}

/*

* �������ܣ��𽥼���ѭ�߷���
* �����������
* ���������1��������ɣ� 0������δ��ɣ�
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@Ԭ����

*/
u8 flMethod_upRise()
{
	int rank;
	static int D,P=200;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		if(currentSpeed<2500) D=500;
		else if(currentSpeed>2500&&currentSpeed<4500) D=600;
		else if(currentSpeed>4500&&currentSpeed<5000) D=1000;
		else if(currentSpeed>5000){
			D=2800;
			P=250;
		}
		PID_Init(&glsensorPID,20,currentSpeed+200,P,0,D);								//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,currentSpeed,currentSpeed);					//�Գ�ʼ�ٶȽ����趨
		currentSpeed+=gl_time*30;
		if(currentSpeed>=goalSpeed){
			findLineFlag=1;
			return 1;
		}
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//λ��ʽ�ı����ٶ�
	
	return 0;
}

/*

* �������ܣ��𽥼���ѭ�߷���
* �����������
* ���������1��������ɣ� 0������δ��ɣ�
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@Ԭ����

*/
u8 flMethod_downRise()
{
	int rank;
	static int D,P=200;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		if(currentSpeed<2500) D=500;
		else if(currentSpeed>2500&&currentSpeed<4500) D=600;
		else if(currentSpeed>4500&&currentSpeed<5000) D=1000;
		else if(currentSpeed>5000){
			D=2800;
			P=250;
		}
		PID_Init(&glsensorPID,20,currentSpeed+200,P,0,D);								//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,currentSpeed,currentSpeed);					//�Գ�ʼ�ٶȽ����趨
		currentSpeed-=gl_time*30;
		if(currentSpeed<=goalSpeed){
			findLineFlag=1;
			return 1;
		}
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed+gldYaw);			//λ��ʽ�ı����ٶ�
	return 0;
}

/*

* �������ܣ�����Ѳ�߷���
* �����������
* �����������
* ����ֵ  ��
* ����    ��ÿ����������Ҫ������1��glmotorSpeed��ʼ�ٶ� 2��glsensorPID��P I D��������
* ����    ��@����

*/
void flMethod_step()
{
	int rank;
	if(findLineFlag == 0)//��֤ÿ��·�γ�ʼ��һ��
	{
		PID_Init(&glsensorPID,20,2500,200,0,0);																					//���ٶ�PID�Ĳ������г�ʼ������
		speedRec_Init(&glmotorSpeed,1500,1550); 																				//�Գ�ʼ�ٶȽ����趨
		findLineFlag=1;
	}
	glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  				//����ֵ�ȽϺ�ģ����ת����������
	rank=sensorDigitalRank(glsensor_dig_value);                                    //�ּ�
	gldSpeed=positionPIDCalc(&glsensorPID,rank);   //�ٶ�λ��ʽPID���
	positionSpeedOut(glmotorSpeed.leftSpeed,glmotorSpeed.rightSpeed,gldSpeed);			//λ��ʽ�ı����ٶ�

}

