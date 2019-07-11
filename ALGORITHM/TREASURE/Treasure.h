#ifndef  _TREASURE_H_
#define  _TREASURE_H_


#include "sys.h"
#include "myconfig.h"

#define Treasure_Num 10

void CheckTreasureNode(controlCenterTypeDef *controlp);
typedef struct{
	
	u8 RunMethodChoose;
	u8 Scan_Code_node;				// 扫码所在节点数
	u8 Next_Code_node;				// 下一个二维码节点数
	void (*AutoTreasure)(int); // 执行函数的入口地址
		
}QRcodeTypeDef;













#endif




