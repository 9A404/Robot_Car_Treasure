#include "carpark.h"
#include "usart3.h"
#include "Treasure.h"
//u8 QR_node=0;
void (*RunMethodTreasure)(int); //ָ�뺯��


/*

* �������ܣ����ݱ���λ�ø���·��
* ���������num,����ȷ�������л�·�߱��������һ��·��
* �����������
* ����ֵ  ����
* ����    ��@�ֺƽ�

*/
void Treasure(int num)
{
//	char buff[2];
//	u8 i=0,j=0,k=0;
	//Gui_DrawFont_Num32(0,0,BLUE,WHITE,1);
	//rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
	runMethodUpdate(runMethod,num,runMethodTableTreasure); 
	Control_Init(&glHello_control,runMethod);     //��ʼ������̨
	runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
}

/*

* �������ܣ�·��ѡ��
��һ������Ϊ��Ҫ��·�߱���л��ĵڼ���·��RunMethodChoose��
�ڶ�������Ϊ���ĸ�ƽ̨ɨ��RunMethodChoose��
����������Ϊ��ƽ̨��ɨ���Ķ�ά����ʲôNext_Code_node��
���ĸ�Ϊ����ָ��
* �����������
* �����������
* ����ֵ  ����
* ����    ��@�ֺƽ�

*/
QRcodeTypeDef TreasureTab[Treasure_Num]={
	{0,7,37,(*Treasure)}, 
	
	{1,12,37,(*Treasure)}, 
	
	{2,37,24,(*Treasure)},  
	
	{3,37,27,(*Treasure)},  
	
	{4,47,24,(*Treasure)},  
	
	{5,47,27,(*Treasure)},  
};


/*

* �������ܣ�������ı����ұ�����Ҫ�л���·��
* �������������̨�ṹ��
* �����������
* ����ֵ  ����
* ����    ��@�ֺƽ�

*/
void CheckTreasureNode(controlCenterTypeDef *controlp)
{
	int i;
	for(i=0;i<Treasure_Num;i++)
		{
			/*������ڵ�ǰ�ڵ����ɨ��ṹ���ɨ�����ڽڵ���
			����(����������ƽ̨��ɨ���Ķ�ά����ֵ����ɨ��ṹ�����һ�������ڽڵ�����������OTG��ƽ̨��ɨ���Ķ�ά����ֵ����ɨ��ṹ�����һ�������ڽڵ���)Ϊ��*/
			if(controlp->curNode==TreasureTab[i].Scan_Code_node && (QR_code_u3_printf(&glHello_control)==TreasureTab[i].Next_Code_node))
			{
				RunMethodTreasure = TreasureTab[i].AutoTreasure;      //�Ѷ�Ӧ�ĺ�������RunMethodTreasure
				(*RunMethodTreasure)(TreasureTab[i].RunMethodChoose);  //ִ�е�ǰ����                   
			}
		}
}













