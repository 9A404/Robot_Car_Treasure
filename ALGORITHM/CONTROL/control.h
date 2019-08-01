#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "sys.h"


#define NODEFORKNUM  	15			//地图中下一节点岔道最多的数目 * 下下节点岔道最多的数目


/*巡线方法*/
typedef enum {FL_default,FL_circular,FL_node,FL_43_44,FL_16_44,FL_angle,FL_slow_angle,FL_middle,FL_brige,FL_brigeup,FL_brigedown,
	FL_slow,FL_quick,FL_stop,FL_quickest,FL_upPeak,FL_downPeak,FL_UpPlatform,FL_DownPlatform,
	FL_left,FL_left_45,FL_Right,NFL,NFL_slow,BACK_NFL,FL_UPRISE,FL_DOWNRISE}findLine;
		
/*路障类型*/
typedef enum {FREE,BRIGE,DOOR,S_BOARD_1,S_BOARD_2,S_BOARD_26_27,SEESAW,GO_TILT_R,GO_TILT_L,
							BACK_TILT_R,BACK_TILT_L,SLOPE,SLOPE_46_43,PLATFORM,PLATFORM_1,Peak,TRAPEZOID_1,TRAPEZOID_2,TRAPEZOID_3,
							DOWNPLATFORM,ALL_TILT,DOWN27_26,ANGLE,STEP,HEIGHTLITM,STEP2}typeRoadblock;	//无障碍、桥、门、减速带、跷跷板、倾斜路面、斜坡、平台景点、梯形景点、复杂节点定时                                                                                                                                  

	
/*加速类型*/
typedef enum {DOWN_SPEED,COMMON_SPEED,NOSPEED,TME,UPRISE}typeSpeed;//下台加速，普通加速，不加速，占时间（用于处理复杂节点)

/*找节点方法*/
typedef enum {SEEK_PESL,SEEK_PESR,SEEK3,SEEK4,SEEK_default,NOTSEEK,SEEK_SeeSaw,SEEK_SeeSaw_back,
SEEK_PesPlatform,SEEK_Collision,SEEK_Collision_1,SEEK_7_6_15,SEEK_6_15_37,SEEK_digR,SEEK_digL}seekNodeWay;

/*停车方法*/
typedef enum {NOTPARK,PARK1,PARK_pesR,PARK_pesR_150,PARK_pesR_200,PARK_pesR_250,PARK_pesR_300,PARK_pesR_350,PARK_pesR_400,
							PARK_default,PARK_pesL,PARK_pesL_150,PARK_pesL_200,PARK_pesL_250,PARK_pesL_300,PARK_pesL_350,PARK_pesL_400,	
							PARK_PesPlatform,PARK_Door,PARK_pesR_No,PARK_pesL_No,PARK_pesL_back,PARK_pesR_back}carPark;

/*车头旋转角度*/
typedef enum {HL_180,HL_145,HL_135,HL_105,HL_120,HL_90,HL_60,HL_45,HL_35,HL_30,
						HN_Rotate,HR_35,HR_45,HR_60,HR_90,HR_110,HR_130,HR_135,HR_145,HR_180,
						rot_LFL, rot_LFL_45,rot_RFL,rot_UL,rot_UR,Sensor_L90,Sensor_R90}carRotAngle;

/*状态信号*/
typedef enum {NTBE,EIC,STANDBY}updataState;		//需要执行 执行完成 待命


/*对路段信息进行记录*/
typedef	struct{

	u8	nextNode;										//下一个节点
	u8	nnNode;											//下下个节点
	findLine      findLineWays;			//巡线方法
	typeRoadblock	typeRoadblock;		//路障类型
	typeSpeed typeSpeed; 				//加速类型
	u16 speedTime;						//加速时间
	seekNodeWay   seekways;					//找点方法
	carPark  			parkways;					//停车方法
	carRotAngle 	rotateAngle;			//当前车头位置基础上再旋转角度
	
}linkInforTypeDef;

/*对地图路段信息进行记录*/
typedef	struct{

	u8	map_nextNode;										//地图下一个节点
	u8	map_nnNode;											//地图下下个节点
	findLine      map_findLineWays;			//地图巡线方法
	typeRoadblock	map_typeRoadblock;		//地图路障类型
	typeSpeed map_typeSpeed; 				//地图加速类型
	u16 map_speedTime;						//地图加速时间
	seekNodeWay   map_seekways;					//地图找点方法
	carPark  			map_parkways;					//地图停车方法
	carRotAngle 	map_rotateAngle;			//地图车头旋转方向
	
}map_linkInforTypeDef;



/*对控制中心状态进行记录*/
typedef	struct{

	u8  curNode;								//当前节点
	u8	nextNode;								//下一个节点
	u8	nnNode;									//下下个节点
	u8	nodeNum;								//节点数
	linkInforTypeDef	linkInform;//路段信息
	updataState	update;						//状态信号
		

}controlCenterTypeDef;


/*对运行状态进行记录,让每个路段根据状态有序进行*/
/*思路：
每个量有三种状态
1、NTBE（需要执行）：
2、EIC（执行完成）：
3、STANDBY（待命）：意味着需要其他状态量来触发，触发后状态将变成（NTBE）
例如：找点需要路障状态的触发、停车需要找点状态的触发、转弯需要找点状态触发
*/
typedef	struct{

	updataState	F_LineState;					//巡线状态
	updataState	F_RoadBlockState;			//找障碍状态
	updataState speedState;					//加速状态
	updataState seekNodeState;				//找点状态
	updataState carParkState;					//停车状态
	updataState	RotangleState;				//转弯状态
	
}runStateTypeDef;

void Control_Init(controlCenterTypeDef *controlp,u8*runMethod);//控制中心初始化函数
void updataState_Reset(controlCenterTypeDef *p,updataState state);//更改控制中心状态信号
unsigned char control_Update(controlCenterTypeDef *controlp,u8 nodeLength,const u8 *runMethod,const map_linkInforTypeDef(*p)[NODEFORKNUM] );//更新控制中心（controlCenterTypeDef结构体）的参数
void runStateInit(runStateTypeDef *runState,const controlCenterTypeDef *controlp);//根据控制台起始路段初始化运行状态
void runStateReset(runStateTypeDef *runState,const controlCenterTypeDef *controlp);//根据控制台判断是否来到新的路段，然后重新设置运行状态
void runMethodReset(u8 runMethod[],const u8 runMethod_2[]); //更新路线
//void DoorMethodUpdate(controlCenterTypeDef *controlp,u8 runMethod[],u8 DoorFlag,const u8 runMethodTableDoorAuto[][100]);   //自动切换过门线路函数
void runMethodUpdate(u8 runMethod[],u8 runMethodNum, const u8 runMethodTab[][100]); //从表格中更新路线
void CheckrunMethod(u8 runMethod[]); //查找路线是去到第几个平台

void findLine_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);         //巡线任务
void roadBlocksHandle_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);//障碍处理任务
void speed_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);		  //加速任务
void seekNode_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);       // 找点任务
void carPark_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);       // 停车任务
void rotAngle_Task(controlCenterTypeDef *controlp,runStateTypeDef *runState);           //  转弯任务

void runStateReset1(runStateTypeDef *runState,const controlCenterTypeDef *controlp);
#endif

