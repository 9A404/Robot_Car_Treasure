#include "adc.h"
#include "myconfig.h"
#include "string.h"


/*

* �������ܣ�adc�õ���GPIO��ʼ����ģ������ģʽ
* �����������
* �����������
* ����ֵ  ����

*/
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE );	//PA��PB��PCʱ��ʹ��
	/*����PA*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/*����PB*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	/*����PC*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

/*

* �������ܣ�����adc1��������ͨ������
* �����������
* �����������
* ����ֵ  ����

*/
static void ADC_Multichannel_Config(void)
{
	ADC_InitTypeDef   ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 	//ʹ��ADC1ʱ��
	
	/*����ADC��Ƶϵ��&��λ*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//����ADC��Ƶ����6 ��72M/6=12,ADC���ʱ�䲻�ܳ���14M
	ADC_DeInit(ADC1);  								//��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;										//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;													//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;										//ģ��ת��������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;								//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = NUM_OF_SENSOR;										//˳����й���ת����ADCͨ������Ŀ
	
	ADC_Init(ADC1, &ADC_InitStructure);																		//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	/*s�����ƶ�ADC����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��*/
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0  , 1 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1  , 2 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2  , 3 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3  , 4 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4  , 5 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5  , 6 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6  , 7 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7  , 8 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8  , 9 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9  ,10 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10 ,11 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11 ,12 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12 ,13 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13 ,14 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14 ,15 , ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15 ,16 , ADC_SampleTime_239Cycles5);
	
	/*����ADC��DMA֧��*/
	ADC_DMACmd(ADC1,ENABLE);
	
	/*ADCʹ��&У׼*/
	ADC_Cmd(ADC1, ENABLE);											//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);									//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 								//����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 	//�ȴ�У׼����
}

/*

* �������ܣ���ʼ��DMA1��ͨ��1
* �����������
* �����������
* ����ֵ  ����

*/
static void ADC_DMA_Config(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);			//DMA1ʱ��ʹ��

	/*����DMAͨ��*/  
    DMA_DeInit(DMA1_Channel1);																					//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;	//�����ַ     
    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)glsensor_ad_value;  		//DMA�ڴ����ַ  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  							//dma���䷽��  
    DMA_InitStructure.DMA_BufferSize = NUM_OF_SENSOR;  								//DMAͨ����DMA����Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//����DMA���ڴ����ģʽ   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���������ֳ�   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //�ڴ������ֳ�   
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									//������ѭ������ģʽ   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;								//����DMA�����ȼ���     
    DMA_InitStructure.DMA_Mode = DMA_M2M_Disable;      								//���ڴ浽�ڴ洫��
		
		DMA_Init(DMA1_Channel1,&DMA_InitStructure);                      //����DMA_InitStructure��ָ���Ĳ�����ʼ��ͨ��

}

/*

* �������ܣ�����DMAͨ��1
* �����������
* �����������
* ����ֵ  ����

*/
static void DMA_Start()
{
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

/*

* �������ܣ�adc��dma��ʼ��
* �����������
* �����������
* ����ֵ  ����

*/
void ADC_DMA_Init(void)
{
	ADC_GPIO_Config();
	ADC_Multichannel_Config();
	ADC_DMA_Config();
	DMA_Start();
}

/*

* �������ܣ�����һ��adcת��
* �����������
* �����������
* ����ֵ  ����

*/
void ADC_ConvertOnce(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);												//�ر�DMA
	DMA_SetCurrDataCounter(DMA1_Channel1,NUM_OF_SENSOR );//����DMAͨ���Լ������С
	DMA_Cmd(DMA1_Channel1,ENABLE);											//��DMA
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

/*

* �������ܣ��������Ƿ����
* �����������
* �����������
* ����ֵ  ��1����ɣ���0��û�У�

*/
unsigned char sampingStatus(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)!=RESET) //�鿴DMA1ͨ��1�Ƿ���ɴ���
	{
		DMA_ClearFlag(DMA1_FLAG_TC1|DMA1_FLAG_HT1|DMA1_FLAG_GL1);             //���DMA1ͨ��1��ɱ�־
		return 1;
	}
	
	return 0;
}

/*

* �������ܣ�������ģ����ת��Ϊ������
* ���������sourceAnalog(��Ҫת������������ģ��ֵ)��thresholdAnalog��ģ������ֵ��
* �����������
* ����ֵ  ��12����������Ӧ��������
* ����    �����ص���������ʽΪ�Ҷ��룬���ֽڵĸ���λû���� 0000 1010 1010 1010   
*/
u16 sensorAD(u16 *sourceAnalog,const u16 *thresholdAnalog )
{
	int i=0;
	u16 temp=0;
	for(i=0;i<NUM_OF_SENSOR;i++)
	{
		temp=temp<<1;
		
		if(sourceAnalog[i] > thresholdAnalog[i])
			temp|=0x0001;
		else
			temp&=(~0x01);
	}

	return temp;

}

///*

//* �������ܣ��ּ�����ʼ��
//* �����������
//* �����������
//* ����ֵ  ����
//* ����    ����ʼ������̺Ѳ���ߵı��

//*/
//void rankInformationInit()
//{
//	int i;
//	memset(&glrankInformation,0,sizeof(rankTypeDef));//�ּ�������
//	for(i=0; i<sizeof(rankInformation_FL)/sizeof(rankInformation_FL[0]); i++)
//	{
//		glrankInformation[i].digitalValue = rankInformation_FL[i].digitalValue;
//		glrankInformation[i].proportion =  rankInformation_FL[i].proportion;
//	}

//}



///*

//* �������ܣ����ݷּ���񽫴��������������ֵȼ�
//* ���������digitalValue��������������������rankInformation(�ּ��ο��ı��)
//* ���������
//* ����ֵ  �����ݹ�������ĵȼ�
//* ����    �����ݴ�������������ֵ   

//*/
//int sensorDigitalRank(u16 digitalValue,rankTypeDef *rankInformationp)
//{
//	static u8 save;//���浱ǰֵ���Ա��´�ʹ��
//	int i;
//	int temp;
//	for(i=0;i<sizeof(rankInformationp) / sizeof(rankInformationp[0]);i++)
//	{
//		if(digitalValue == rankInformationp->digitalValue)
//		{
//			temp=rankInformationp->proportion;
//			save = temp;
//		}
//	}
//	temp = save;
//  return temp;

//}

///*

//* �������ܣ����ķּ���
//* ���������rankInformationp����Ҫ�滻�ķּ�����refp(�����滻�ķּ���)
//* �����������
//* ����ֵ  ����
//* ����    ����   

//*/
//void tableExchang(rankTypeDef *rankInformationp,const rankTypeDef *refp)
//{
//	int i;
//	memset(rankInformationp,0,sizeof(rankTypeDef));//�ּ�������
//	for(i=0;i<sizeof(refp) / sizeof(refp[0]);i++)
//	{
//		(rankInformationp+i)->digitalValue = (refp+i)->digitalValue;
//		(rankInformationp+i)->proportion = (refp+i)->proportion;
//	}
//	
//}




/*�ɰ汾

* �������ܣ����������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank(u16 digitalValue)
{
	int temp;
//	static int save=20;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0x800: temp=0;break;     // 1000 0000 0000
		case 0xC00: temp=2;break;			// 1100 0000 0000
		case 0xE00: temp=4;break;			// 1110 0000 0000
		case 0x600: temp=6;break;     // 0110 0000 0000
		case 0x700: temp=8;break;     // 0111 0000 0000
		case 0x300: temp=10;break;    // 0011 0000 0000
		case 0x380: temp=12;break;    // 0011 1000 0000
		case 0x180: temp=14;break;    // 0001 1000 0000
		case 0x1C0: temp=16;break;    // 0001 1100 0000
		case 0x0C0: temp=18;break;    // 0000 1100 0000 
		
		case 0x0E0: temp=19;break;    // 0000 1110 0000 �м�
		case 0x060: temp=20;break;    // 0000 0110 0000 �м�
		case 0x070: temp=21;break;    // 0000 0111 0000 �м�
		case 0x030: temp=22;break;    // 0000 0011 0000 �м�
		
		case 0x038: temp=24;break;    // 0000 0011 1000
		case 0x018: temp=26;break;    // 0000 0001 1000
		case 0x01C: temp=28;break;    // 0000 0001 1100
		case 0x00C: temp=30;break;    // 0000 0000 1100
		case 0x00E: temp=32;break;    // 0000 0000 1110
		case 0x006: temp=34;break;    // 0000 0000 0110
		case 0x007: temp=36;break;    // 0000 0000 0111
		case 0x003: temp=38;break;    // 0000 0000 0011
		case 0x001: temp=40;break;    // 0000 0000 0001
		default   : temp = 20; break;//��������ֵ��ʱ������ϴε�ֵ
	}
	//	save = temp;
	return temp;
}


/*

* �������ܣ����Ŵ��������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank_Brige(u16 digitalValue)
{
	int temp;
	//static int save=16;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			// 0000 1111 1111
	  case 0x8ff: temp=2;break;			// 1000 1111 1111
		case 0x87F: temp=4;break;			// 1000 0111 1111
		case 0xc7f: temp=6;break;			// 1100 0111 1111
		case 0xc3F: temp=8;break;    //  1100 0011 1111
		case 0xe3F: temp=10;break;     //1110 0011 1111
		case 0xe1F: temp=12;break;    // 1110 0001 1111
		case 0xf1f: temp=14;break;    // 1111 0001 1111
		case 0xf0f: temp=16;break;    // 1111 0000 1111
		case 0xf8f: temp=18;break;    // 1111 1000 1111
		case 0xf87: temp=20;break;    // 1111 1000 0111
		case 0xFc7: temp=22;break;    // 1111 1100 0111
		case 0xFc3: temp=24;break;    // 1111 1100 0011
		case 0xFe3: temp=26;break;    // 1111 1110 0011
		case 0xFe1: temp=28;break;    // 1111 1110 0001
		case 0xff1: temp=30;break;    // 1111 1111 0001
		case 0xFF0: temp=32;break;    // 1111 1111 0000
		default   : temp = 16; break;//��������ֵ��ʱ������ϴε�ֵ
	}
	
	//save = temp;
	return temp;
}

/*

* �������ܣ����Ŵ��������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank_Brige_Up(u16 digitalValue)
{
	int temp;
	static int save=16;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			//0000 1111 1111 
	  case 0x8ff: temp=4;break;			//1000 1111 1111
		case 0x87F: temp=6;break;			//1000 0111 1111
		case 0xc7f: temp=8;break;			//1100 0111 1111
		case 0xc3F: temp=10;break;    //1100 0011 1111
		case 0xe3F: temp=12;break;    //1110 0011 1111
		case 0xe1F: temp=12;break;    //1110 0001 1111
		case 0xf1f: temp=14;break;    //1111 0001 1111
		case 0xf0f: temp=16;break;    //1111 0000 1111
		case 0xf8f: temp=18;break;    //1111 1000 1111
		case 0xf87: temp=20;break;    //1111 1000 0111
		case 0xFc7: temp=22;break;    //1111 1100 0111
		case 0xFc3: temp=24;break;    //1111 1100 0011
		case 0xFe3: temp=26;break;    //1111 1110 0011
		case 0xFe1: temp=30;break;    //1111 1100 0001
		case 0xff1: temp=34;break;    //1111 1111 0001
		default   : temp = save; break;//��������ֵ��ʱ������ϴε�ֵ
	}
	
	save = temp;
	return temp;
}

/*

* �������ܣ����Ŵ��������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank_Brige_Down(u16 digitalValue)
{
	int temp;
	static int save=14;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0xff:  temp=0;break;			//  
	  case 0x8ff: temp=4;break;			// 
		case 0x87F: temp=6;break;			// 
		case 0xc7f: temp=8;break;			// 
		case 0xc3F: temp=10;break;     // 
		case 0xe3F: temp=12;break;     // 
		case 0xe1F: temp=12;break;    // 
		case 0xf1f: temp=14;break;    // �м�
		case 0xf0f: temp=16;break;
		case 0xf8f: temp=18;break;    // 
		case 0xf87: temp=20;break;    //  
		case 0xFc7: temp=22;break;    // 
		case 0xFc3: temp=24;break;    // 
		case 0xFe3: temp=26;break;
		case 0xFe1: temp=30;break;
		case 0xff1: temp=34;break;
		default   : temp = save; break;//��������ֵ��ʱ������ϴε�ֵ
	}
	
	save = temp;
	return temp;
}

/*

* �������ܣ�����崫�������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank_Peak(u16 digitalValue)
{
	int temp;
	static int save=16;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0xe00: temp=0;break;     // 
		case 0x600: temp=2;break;			// 
		case 0x700: temp=4;break;			// 
		case 0x300: temp=6;break;     // 
		case 0x380: temp=8;break;     // 
		case 0x180: temp=10;break;    // 
		case 0x0c0: temp=12;break;    // 
		case 0x0e0: temp=14;break;    // 
		case 0x060: temp=16;break;    // 
		case 0x010: temp=16;break;    // �м� 
		case 0x030: temp=16;break;    //
		case 0x018: temp=22;break;    // 
		case 0x01c: temp=24;break;    // 
		case 0x00c: temp=28;break;    // 
		case 0x004: temp=30;break;    // 
		case 0x003: temp=30;break;    // 
		
		default   : temp = save; break;//��������ֵ��ʱ������ϴε�ֵ
	}
		save = temp;
	return temp;
}


/*�ɰ汾

* ��������:���Ƕ��ܷ����Ƕȷּ�
* �����������ǰ�Ƕ�
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����  �����ݽǶ�������
*/
int rotangle_run(float angle)
{
		int temp=18;
//	int i;
//	static  u8 angle_flag=1;
//	static float angle_save;
	static int save=18;//���浱ǰֵ���Ա��´�ʹ��
  static float angle_temp[19]={-12.6,-11.2,-9.8,-8.4,-7.0,-5.6,-4.2,-2.8,-1.4,0,1.4,2.8,4.2,5.6,7.0,8.4,9.8,11.2,12.6};
//	    static float angle_temp[19]={-6.3,-5.6,-4.9,-4.2,-3.5,-2.8,-2.1,-1.4,-0.7,0,0.7,1.4,2.1,2.8,3.5,4.2,4.9,5.6,6.3};

//	if(angle_flag==1)
//	{
//	for(i=0;i<18;i++)
//		{
//		angle_temp[i]=angle+i*1.4-12.6;
//		}
//	    angle_save=angle;
//		angle_flag = 0;
//    }
//		if(angle_temp[0]== angle  ) temp = 0;
//     if( angle_temp[1] == angle) temp=0;
//     if(  angle_temp[2] ==angle)temp=2;
//	 if(  angle_temp[3] ==angle)temp=4;
//	 if(  angle_save==angle)temp=6;
//	 if(  angle_temp[4] ==angle )temp=8;
//	 if(  angle_temp[5] ==angle )temp=10;
//     if(  angle_temp[6] ==angle )temp=12;
//	else if(  angle_temp[6] ==angle )temp=14;
//	else if(  angle_temp[7] ==angle )temp=16;
//	else if(  angle_temp[8] ==angle )temp=18;
//	else if(  angle_temp[9] ==angle )temp=20;
//	else if(  angle_temp[10] ==angle )temp=22;
//	else if(  angle_temp[11] ==angle )temp=24;
//	
	if(angle_temp[0]>=angle ) temp = 38;
	  else  if(  angle_temp[0] < angle && angle<=angle_temp[1])temp=36;
	else if(  angle_temp[1] <angle && angle<=angle_temp[2])temp=34;
	else if(  angle_temp[2] <angle && angle<=angle_temp[3])temp=32;
	else if(  angle_temp[3] <angle && angle<=angle_temp[4])temp=30;
	else if(  angle_temp[4] <angle && angle<=angle_temp[5])temp=28;
	else if(  angle_temp[5] <angle && angle<=angle_temp[6])temp=26;
	else if(  angle_temp[6] <angle && angle<=angle_temp[7])temp=24;
	else if(  angle_temp[7] <angle && angle<=angle_temp[8])temp=22;
	else if(  angle_temp[8] <angle && angle<=angle_temp[9])temp=20;
	else if(  angle_temp[9] <angle && angle <=angle_temp[10])temp=18;
	else if(  angle_temp[10]<angle&& angle <=angle_temp[11])temp=16;
	else if(  angle_temp[11] <angle&& angle<=angle_temp[12])temp=14;
	else if(  angle_temp[12] <angle&& angle<=angle_temp[13])temp=12;
	else if(  angle_temp[13] <angle&& angle<=angle_temp[14])temp=10;
	else if(  angle_temp[14] <angle&& angle <=angle_temp[15])temp=8;
	else if(  angle_temp[15] <angle&& angle <=angle_temp[16])temp=6;
	else if(  angle_temp[16] <angle&& angle<=angle_temp[17])temp=4;
		else if(  angle_temp[17] <angle&& angle<=angle_temp[18])temp=2;
	else if( angle_temp[18]<angle)  temp=0;
		
//			if(angle_temp[0]>=angle ) temp = 0;
//	else  if(  angle_temp[0] < angle && angle<=angle_temp[1])temp=2;
//	else if(  angle_temp[1] <angle && angle<=angle_temp[2])temp=4;
//	else if(  angle_temp[2] <angle && angle<=angle_temp[3])temp=6;
//	else if(  angle_temp[3] <angle && angle<=angle_temp[4])temp=8;
//	else if(  angle_temp[4] <angle && angle<=angle_temp[5])temp=10;
//	else if(  angle_temp[5] <angle && angle<=angle_temp[6])temp=12;
//	else if(  angle_temp[6] <angle && angle<=angle_temp[7])temp=14;
//	else if(  angle_temp[7] <angle && angle<=angle_temp[8])temp=16;
//	else if(  angle_temp[8] <angle && angle<=angle_temp[9])temp=18;
//	else if(  angle_temp[9] <angle && angle <=angle_temp[10])temp=20;
//	else if(  angle_temp[10]<angle&& angle <=angle_temp[11])temp=22;
//	else if(  angle_temp[11] <angle&& angle<=angle_temp[12])temp=24;
//	else if(  angle_temp[12] <angle&& angle<=angle_temp[13])temp=26;
//	else if(  angle_temp[13] <angle&& angle<=angle_temp[14])temp=28;
//	else if(  angle_temp[14] <angle&& angle <=angle_temp[15])temp=30;
//	else if(  angle_temp[15] <angle&& angle <=angle_temp[16])temp=32;
//	else if(  angle_temp[16] <angle&& angle<=angle_temp[17])temp=34;
//	else if(  angle_temp[17] <angle&& angle<=angle_temp[18])temp=36;
//	else if( angle_temp[18]<angle)  temp=38;	  
		save = temp;
			//u3_printf("%.2f %.2f %.2f \n",angle,angle_temp[0],angle_temp[17]);
	return temp;
}




















/*

* �������ܣ���ת90���������������ֵȼ�
* ���������digitalValue������������������
* ���������
* ����ֵ  �����ݹ�������ĵȼ�
* ����    �����ݴ�������������ֵ   

*/
int sensorDigitalRank_HR90(u16 digitalValue)
{
	int temp;
	static int save=22;//���浱ǰֵ���Ա��´�ʹ��
	switch(digitalValue)
	{
		case 0x800: temp=-6;break;     // 1000 0000 0000
		case 0xC00: temp=-4;break;			// 1100 0000 0000
		case 0xE00: temp=-2;break;			// 1110 0000 0000
		case 0x600: temp=0;break;     // 0110 0000 0000
		case 0x700: temp=2;break;     // 0111 0000 0000
		case 0x300: temp=4;break;    // 0011 0000 0000
		case 0x380: temp=6;break;    // 0011 1000 0000
		case 0x180: temp=8;break;    // 0001 1000 0000
		case 0x1C0: temp=10;break;    // 0001 1100 0000
		case 0x0C0: temp=12;break;    // 0000 1100 0000  
		case 0x0E0: temp=14;break;    // 0000 1110 0000 �м�
		case 0x060: temp=22;break;    // 0000 0110 0000 �м�
		case 0x030: temp=30;break;    // 0000 0011 0000
		case 0x038: temp=32;break;    // 0000 0011 1000
		case 0x018: temp=34;break;    // 0000 0001 1000
		case 0x01C: temp=36;break;    // 0000 0001 1100
		case 0x00C: temp=38;break;    // 0000 0000 1100
		case 0x00E: temp=40;break;    // 0000 0000 1110
		case 0x006: temp=42;break;    // 0000 0000 0110
		case 0x007: temp=44;break;    // 0000 0000 0111
		case 0x003: temp=46;break;    // 0000 0000 0011
		case 0x001: temp=48;break;    // 0000 0000 0001
	
		default   : temp = save; break;//��������ֵ��ʱ������ϴε�ֵ
	}
	save = temp;
	return temp;
}



//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 













