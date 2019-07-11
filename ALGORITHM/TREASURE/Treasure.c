#include "carpark.h"
#include "usart3.h"
#include "Treasure.h"
//u8 QR_node=0;
void (*RunMethodTreasure)(int); //指针函数


/*

* 函数介绍：根据宝物位置更改路线
* 输入参数：num,用于确定宝物切换路线表格里面那一条路线
* 输出参数：无
* 返回值  ：无
* 作者    ：@林浩杰

*/
void Treasure(int num)
{
//	char buff[2];
//	u8 i=0,j=0,k=0;
	//Gui_DrawFont_Num32(0,0,BLUE,WHITE,1);
	//rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
	runMethodUpdate(runMethod,num,runMethodTableTreasure); 
	Control_Init(&glHello_control,runMethod);     //初始化控制台
	runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
}

/*

* 函数介绍：路线选择
第一个参数为需要从路线表格切换的第几条路线RunMethodChoose、
第二个参数为在哪个平台扫码RunMethodChoose、
第三个参数为在平台上扫到的二维码是什么Next_Code_node、
第四个为函数指针
* 输入参数：无
* 输出参数：无
* 返回值  ：无
* 作者    ：@林浩杰

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

* 函数介绍：从上面的表格查找宝物需要切换的路线
* 输入参数：控制台结构体
* 输出参数：无
* 返回值  ：无
* 作者    ：@林浩杰

*/
void CheckTreasureNode(controlCenterTypeDef *controlp)
{
	int i;
	for(i=0;i<Treasure_Num;i++)
		{
			/*如果车在当前节点等于扫码结构体的扫码所在节点数
			并且(利用蓝牙在平台上扫到的二维码数值等于扫码结构体的下一宝物所在节点数或者利用OTG在平台上扫到的二维码数值等于扫码结构体的下一宝物所在节点数)为真*/
			if(controlp->curNode==TreasureTab[i].Scan_Code_node && (QR_code_u3_printf(&glHello_control)==TreasureTab[i].Next_Code_node))
			{
				RunMethodTreasure = TreasureTab[i].AutoTreasure;      //把对应的函数赋给RunMethodTreasure
				(*RunMethodTreasure)(TreasureTab[i].RunMethodChoose);  //执行当前函数                   
			}
		}
}













