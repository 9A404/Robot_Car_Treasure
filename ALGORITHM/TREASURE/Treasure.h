#ifndef  _TREASURE_H_
#define  _TREASURE_H_


#include "sys.h"
#include "myconfig.h"

#define Treasure_Num 10

void CheckTreasureNode(controlCenterTypeDef *controlp);
typedef struct{
	
	u8 RunMethodChoose;
	u8 Scan_Code_node;				// ɨ�����ڽڵ���
	u8 Next_Code_node;				// ��һ����ά��ڵ���
	void (*AutoTreasure)(int); // ִ�к�������ڵ�ַ
		
}QRcodeTypeDef;













#endif




