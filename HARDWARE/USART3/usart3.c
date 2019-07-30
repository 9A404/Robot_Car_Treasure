#include "usart3.h"	
#include "sys.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "myconfig.h"

char *findLinep[]={"FL_default","FL_circular","FL_node","FL_43_44","FL_16_44","FL_middle","FL_brige","FL_brigeup","FL_brigedown","FL_slow","FL_quick","FL_stop","FL_quickest","FL_upPeak","FL_downPeak","FL_UpPlatform","FL_DownPlatform","FL_left","FL_Right","NFL","NFL_slow","BACK_NFL"};

	char *typeRoadblockp[]={"FREE","BRIGE","DOOR","S_BOARD_1","S_BOARD_2","S_BOARD_26_27","SEESAW","GO_TILT_R","GO_TILT_L",\
							"BACK_TILT_R","BACK_TILT_L","SLOPE","PLATFORM","PLATFORM_1","Peak","TRAPEZOID_1","TRAPEZOID_2","TRAPEZOID_3",\
							"TIME","TIME_1","TIME_2","TIME_3","SPEEDTIME_11_10","SPEEDTIME_8_6","SPEEDTIME_7_6","SPEEDTIME_6_7","SPEEDTIME_5_12","SPEEDTIME_2","SPEEDTIME_36_17","SPEEDTIME_17_37","SPEEDTIME_14_37","SPEEDTIME_38_37","DOWNPLATFORM","ALL_TILT",\
							"DOWN27_26"		};

char *seekNodeWayp[]={"SEEK_PESL","SEEK_PESR","SEEK3","SEEK4","SEEK_default","NOTSEEK","SEEK_SeeSaw","SEEK_PesPlatform","SEEK_Collision","SEEK_Collision_1"};

char *carParkp[]={"NOTPARK","PARK1","PARK_pesR","PARK_default","PARK_pesL","PARK_PesPlatform","PARK_Door"};

char *carRotAnglep[]={"HL_180","HL_145","HL_135","HL_110","HL_120","HL_90","HL_60","HL_45","HL_35","HN_Rotate","HR_35","HR_45","HR_60","HR_90","HR_110","HR_130","HR_135","HR_145","HR_180","rot_LFL","rot_RFL","rot_UL","rot_UR","Sensor_L90","Sensor_R90"};

char *updataStatep[]={"NTBE","EIC","STANDBY"};

//u8 uartData;

//u8 uartData;

/*

* �������ܣ�����3��DMA��������
* ���������(DMA_CHx)DMAͨ��CHx	(cpar)�����ַ	(cmar)�洢����ַ
* ���������
* ����ֵ  ��
* ����    ��@����

*/

void USART3_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
    DMA_DeInit(DMA_CHx);   															//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  	//DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  			//DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = 0;  							//DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  									//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  	//���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 					//���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  													//��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 									//DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  													//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  																//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���	
}


/*

* �������ܣ�DMA1�ĸ�ͨ������,����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�,�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
* ���������(DMA_CHx)DMAͨ��CHx	(cpar)�����ַ	(cmar)�洢����ַ
* ���������
* ����ֵ  ��
* ����    ��@����

*/
void USART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
{
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
  DMA_DeInit(DMA_CHx);   															//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  	//DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  			//DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = 66;  							//DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  									//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  	//���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 					//���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  													//��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 									//DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  													//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  																//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���	
}

/*����3�жϷ������*/
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART3_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����3 
//bound:������
void usart3_init(u32 bound){
    /*GPIO�˿�����*/
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		/*ʹ��USART3*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	
		/*ʹ��USART1��GPIOBʱ��*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
		/*��λ����3*/
		USART_DeInit(USART3);  
		/*USART3_TX   PB10*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
    /*USART1_RX	  PB11*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11
   /*Usart3 NVIC ����*/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�1
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
   /*USART3 ��ʼ������*/
		USART_InitStructure.USART_BaudRate = bound;																				//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;												//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;													//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;															//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;								//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); 			//��ʼ������
		
		/*ʹ�ܴ���3��DMA����*/
		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);  	
		/*DMA1ͨ��3,����Ϊ����3,�洢��ΪUSART3_TX_BUF*/
		USART3_DMA_Config(DMA1_Channel2,(u32)&USART3->DR,(u32)USART3_TX_BUF);
    
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//�����ж�
    USART_Cmd(USART3, ENABLE);                    	//ʹ�ܴ��� 

}
#if EN_USART3_RX   //���ʹ���˽���
void USART3_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	char buff[2];
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
			
		if((USART3_RX_STA&0x8000)==0)//����δ���
			{
			if(USART3_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART3_RX_STA=0;//���մ���,���¿�ʼ
				else {
					USART3_RX_STA|=0x8000;	//��������� 
					get_from_phone();
				}
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART3_RX_STA|=0x4000;
				else
					{
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   
		}
				
	
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif	


/*

* �������ܣ�����һ�δ���1DMA����
* �����������
* �����������
* ����ֵ  ����
* ����   :@λʤ

*/
void USART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	/*�⺯���汾*/
		//	DMA_Cmd(DMA_CHx, DISABLE ); 				 //�ر� ָʾ��ͨ��        
		//	DMA_SetCurrDataCounter(DMA_CHx,len);//DMAͨ����DMA����Ĵ�С	
		//	DMA_Cmd(DMA_CHx, ENABLE);           //����DMA����
	/*�Ĵ����汾*/
				DMA_CHx->CCR&=~(1<<0);//�ر�DMA����
				DMA_CHx->CNDTR=66;   //DMA1,���������� 
				DMA_CHx->CCR|=1<<0;   //����DMA����
}

/*

* �������ܣ�����һ��DMA����
* �����������
* �����������
* ����ֵ  ����
* ����    ��@����

*/
void USART3_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u8 len)
{
	/*�⺯���汾*/
		//	DMA_Cmd(DMA_CHx, DISABLE ); 				 //�ر� ָʾ��ͨ��        
		//	DMA_SetCurrDataCounter(DMA_CHx,len);//DMAͨ����DMA����Ĵ�С	
		//	DMA_Cmd(DMA_CHx, ENABLE);           //����DMA����
	/*�Ĵ����汾*/
				DMA_CHx->CCR&=~(1<<0);//�ر�DMA����
				DMA_CHx->CNDTR=len;   //DMA1,���������� 
				DMA_CHx->CCR|=1<<0;   //����DMA����
}	  

/*

* �������ܣ���ʼ������3�Լ�Ѱ����־λ(���ڵڶ��α���)
* �����������
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@��

*/
void Treasure_Reset_Usart3(void)
{
	treasure_flag=0;
	QR_code_flag=0;
	memset(QR_code,'0',sizeof(QR_code));
	USART3_RX_STA=0;
	memset(USART3_RX_BUF,'0',sizeof(USART3_RX_BUF));
}	

/*

* �������ܣ�����3,printf ����
* �����������
* �����������
* ����ֵ  ����
*	����		��ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
* ����    ��@����

*/
void u3_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	while(DMA1_Channel2->CNDTR!=0);					//�ȴ�ͨ��2������ɲŸ��»�����
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);  
	USART3_DMA_Enable(DMA1_Channel2,strlen((const char*)USART3_TX_BUF)); 	//ͨ��dma���ͳ�ȥ
	
}

/*

* �������ܣ�ͨ������3��������ģ����ȫ����ӡ
* �����������sourceArray�����鴢���׵�ַ
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@����

*/
void array_u3printf(const unsigned short int *sourceArray)
{
	u3_printf("%d %d %d %d %d %d %d %d %d %d %d %d\r\n",
						sourceArray[0],sourceArray[1],sourceArray[2],sourceArray[3],sourceArray[4],sourceArray[5],
						sourceArray[6],sourceArray[7],sourceArray[8],sourceArray[9],sourceArray[10],sourceArray[11]);
}
/*

* �������ܣ�ͨ������3���մ��ֻ��������Ķ�ά�����ݲ�����
* ���������controlCenterTypeDef
* �����������
* ����ֵ  ����ά�����ݣ������Զ���ڵ㣩
*	����		����
* ����    ��@�ֺƽ�

*/
u8 QR_code_u3_printf(controlCenterTypeDef *controlp)
{
	u8 temp;
	u16 len=0;
	u8 t=0;
	if(USART3_RX_STA&0x8000)
	{
		QR_code_flag++;                  //ÿ�յ�һ�δ��ֻ���������ά������QR_code_flag++
		len=USART3_RX_STA&0x3fff;
		for(t=0;t<len;t++)	QR_code[t]=USART3_RX_BUF[t];
		//Gui_DrawFont_Num32(0,0,BLUE,WHITE,QR_code_flag);
		USART3_RX_STA=0;
		memset(USART3_RX_BUF,'0',sizeof(USART3_RX_BUF));
	}
	switch(QR_code_flag)
	{
		/*��һ������*/
		
		/*  �ж���ƽ̨1(�ڵ�4)ɨ�赽�Ķ�ά�룬������һ��Ӧ��ͬʱ����˫�ֵ�ƽ̨(3��4ƽ̨)(�ڵ�Ϊ7��12)*/
		case 1:if(QR_code[0]=='7'&&QR_code[1]=='0') 	{temp=7;break;}
			   else if(QR_code[0]=='1'&&QR_code[1]=='2') {temp=12;break;}
			   break;
					 
					 
		/*�ڶ�������*/
					 
					 
		/*  �ж���ƽ̨2��3(�ڵ�1��12)ɨ�赽�Ķ�ά�룬������һ��Ӧ��ͬʱ����˫�ֵ�ƽ̨(5��6ƽ̨)(�ڵ�Ϊ37��47)*/
		case 2:if(QR_code[0]=='3'&&QR_code[1]=='7') {temp= 37;break;}
			   else if(QR_code[0]=='4'&&QR_code[1]=='7') {temp=47;break;}
			   break;
						
						
		/*����������*/
					 
					 
		/*  �ж���ƽ̨2��3(�ڵ�1��12)ɨ�赽�Ķ�ά�룬������һ��Ӧ��ͬʱ����˫�ֵ�ƽ̨(5��6ƽ̨)(�ڵ�Ϊ37��47)*/
		case 3:if(QR_code[0]=='2'&&QR_code[1]=='7') {temp=27;break;}
			   else if(QR_code[0]=='2'&&QR_code[1]=='4') {temp=24;break;}break;
	}
	return temp;
}
/*

* �������ܣ�ͨ������3���մ���һ���ֻ�����������Ϣ���н��������������
* �����������
* �����������
* ����ֵ  ����
* ����	  ��Treasure_code���鸳ֵ
* ����    ��@Ԭ����

*/
void get_from_phone()
{
	int i=0;
	u16 len=0;
	u8 t=0;
	char buff[2];
	u8 temp[3];
	if(USART3_RX_STA&0x8000)
	{
		len=USART3_RX_STA&0x3fff;
		for(t=0;t<len;t++)	temp[t]=USART3_RX_BUF[t];	
	}
	if(t==3){
		Lcd_Clear(WHITE);
		USART3_RX_STA=0;
		memset(USART3_RX_BUF,'0',sizeof(USART3_RX_BUF));
		for(i=0;i<3;i++){
			switch(temp[i]){
				case '3':Treasure_code[i]=7;break;
				case '4':Treasure_code[i]=12;break;
				case '5':Treasure_code[i]=37;break;
				case '6':Treasure_code[i]=47;break;
				case '7':Treasure_code[i]=27;break;
				case '8':Treasure_code[i]=24;break;
				default:break;
			}
		}
	}
//	//Lcd_Clear(WHITE);
//	sprintf(buff,"%d",Treasure_code[0]);
//	//USART3_RX_STA=0;
//	Gui_DrawFont_GBK16(50,50,BLUE,WHITE,buff);
}


/*

* �������ܣ�������������1����
* ���������digital�����������������
* �����������
* ����ֵ  ��1�ĸ���
* ����    ��@����

*/
u8 calculateNum(u16 digital)
{
	u8 i;
	u8 temp=0;
	for(i=0;i<NUM_OF_SENSOR;i++)
	{
		if(digital & (1<<i) )
			temp++;
	}
	return temp;
}


/*

* �������ܣ�ͨ������3����������������ӡ����
* �����������value��������
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@����(value&0x40)>>6

*/
void sensorBit_u3printf(const unsigned short int value)
{
	unsigned short int temp = 0x0800;
	u3_printf("Digital:%d%d%d%d %d%d%d%d %d%d%d%d %x %d\r\n",(value&temp)>>11,(value&(temp>>1))>>10,(value&(temp>>2))>>9,(value&(temp>>3))>>8,(value&(temp>>4))>>7,
	(value&(temp>>5))>>6,(value&(temp>>6))>>5,(value&(temp>>7))>>4,(value&(temp>>8))>>3,(value&(temp>>9))>>2,(value&(temp>>10))>>1,value&1,value,calculateNum(value));

}	
/*

* �������ܣ�ͨ������3����������������ӡ����
* �����������value��������
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@����(value&0x40)>>6

*/
void sensor3printf(const unsigned short int value)
{
	u3_printf("0x%x\r\n",value,calculateNum(value));

}	


/*

* �������ܣ�ͨ������3������̨��Ϣ��ӡ����
* ���������controlp������̨��ַ��
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@����

*/
void controlCenter_u3printf(const u8 *runMethod ,const controlCenterTypeDef *controlp)
{
	static char i=0;
	u3_printf("LD:%d-%d\r\ncurNode:%d  nextNode:%d  nnNode:%d \r\n updataState:%s\r\n findLineWays:%s\r\n typeRoadblock:%s\r\n seekways:%s\r\n parkways:%s\r\n rotateAngle:%s\r\n",
	*(runMethod+i),
	*(runMethod+i+1),
	controlp->curNode,controlp->nextNode,controlp->nnNode,
	updataStatep[controlp->update],
	findLinep[controlp->linkInform.findLineWays],
	typeRoadblockp[controlp->linkInform.typeRoadblock],
	seekNodeWayp[controlp->linkInform.seekways],
	carParkp[controlp->linkInform.parkways],
	carRotAnglep[controlp->linkInform.rotateAngle]
	);
	i++;
	
}	

/*

* �������ܣ�ͨ������3������״̬��ӡ����
* ���������runState������״̬��¼��״̬��
* �����������
* ����ֵ  ����
*	����		����
* ����    ��@����

*/
void runState_u3printf(runStateTypeDef *runState)
{
	u3_printf("findLine:%s\n fB:%s\n seekNode:%s\n carpark:%s\n rotangle:%s\n",
	updataStatep[runState->F_LineState],
	updataStatep[runState->F_RoadBlockState],
	updataStatep[runState->seekNodeState],
	updataStatep[runState->carParkState],
	updataStatep[runState->RotangleState]
	);
}	





