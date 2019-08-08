#include "control.h"
#include "myconfig.h"

/*通过一个表示出地图巡线方法 路障类型 加速类型 加速时间 找节点方法 停车方法 车头旋转角度*/

const map_linkInforTypeDef mapInformation[][NODEFORKNUM]={
/*节点*/	{	{0,0,},			},//没有用到				

/*1节点*/	{	{2,1,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_default,HN_Rotate},
				{2,3,FL_default,PLATFORM_1,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{2,5,FL_default,PLATFORM_1,NOSPEED,0,SEEK_default,NOTPARK,rot_LFL},	},//1节点前往的节点	参数： 巡线方法 路障类型 找节点方法 停车方法 车头旋转角度			

/*2节点*/	{	{1,2,FL_slow,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_default,HR_180},
				{3,4,FL_slow,BRIGE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{5,9,FL_default,SLOPE,NOSPEED,0,SEEK_default,PARK_pesL,HL_120},
				{5,6,FL_default,SLOPE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},},//2节点			

/*3节点*/	{	{2,1,FL_brige,FREE,NOSPEED,0,SEEK_default,PARK_default,HN_Rotate},
				{4,3,FL_slow,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{5,9,FL_slow,STEP,NOSPEED,0,SEEK_default,PARK_pesL_200,HL_35},
				{5,6,FL_slow,STEP,NOSPEED,0,SEEK_default,PARK_pesR,HR_135},
				{5,12,FL_slow,STEP,NOSPEED,0,SEEK_default,PARK_pesL,HL_45},
				{5,10,FL_slow,STEP,NOSPEED,0,SEEK_default,PARK_pesL,HL_45},			},//3节点		
	
/*4节点*/	{	{3,5,FL_slow,PLATFORM,NOSPEED,0,SEEK_default,NOTPARK,rot_RFL},	},//4节点	

/*5节点*/	{	{2,1,FL_slow,S_BOARD_1,NOSPEED,0,SEEK_default,NOTPARK,rot_RLF_35},
				{6,7,FL_quick,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{6,8,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,rot_RFL},
				{9,10,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{12,7,FL_default,FREE,COMMON_SPEED,90,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{12,10,FL_default,FREE,COMMON_SPEED,92,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{10,11,FL_default,FREE,COMMON_SPEED,37,SEEK_default,NOTPARK,rot_LFL},	},      

/*6节点*/	{	{7,6,FL_default,FREE,COMMON_SPEED,48,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{8,6,FL_default,FREE,COMMON_SPEED,50,SEEK_Collision,NOTPARK,HL_180},
				{14,15,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},
				{5,2,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,rot_LFL},
				{7,12,FL_default,FREE,COMMON_SPEED,50,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{41,13,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{42,14,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{14,37,FL_default,FREE,NOSPEED,0,SEEK_PESL,PARK_pesR,HL_90},
				{15,37,FL_default,FREE,COMMON_SPEED,73,SEEK_6_15_37,NOTPARK,HN_Rotate},	},
						
/*7节点*/	{	{6,5,FL_default,PLATFORM,COMMON_SPEED,50,SEEK_PESR,NOTPARK,HN_Rotate},
				{6,14,FL_default,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},
				{12,10,FL_default,PLATFORM,COMMON_SPEED,80,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{6,42,FL_default,PLATFORM,COMMON_SPEED,50,SEEK_default,PARK_pesR,HR_90},
				{6,8,FL_slow,PLATFORM,COMMON_SPEED,50,SEEK_default,PARK_pesL,HL_135},
				{6,15,FL_default,PLATFORM,COMMON_SPEED,35,SEEK_digR,NOTPARK,rot_RFL},},
						
/*8节点*/ {		{6,7,FL_slow,FREE,COMMON_SPEED,45,SEEK4,PARK_pesR_250,HR_145},
				{6,42,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},	},

  /*9节点*/ {		{10,12,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{10,11,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_30},
				{5,6,FL_quick,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{5,2,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR_150,HR_130},
				{39,15,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{39,9,FL_slow,FREE,NOSPEED,0,SEEK_Collision_1,PARK_Door,HL_180},
				{40,13,FL_slow,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{40,9,FL_slow,FREE,NOSPEED,0,SEEK_Collision_1,PARK_Door,HL_180},
				{6,41,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},},

/*10节点*/{		{12,10,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{11,10,FL_default,FREE,COMMON_SPEED,40,SEEK_Collision,NOTPARK,HL_180},
				{9,5,FL_quick,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{24,36,FL_default,GO_TILT_L,NOSPEED,0,SEEK_default,PARK_pesR,HR_135},
				{9,39,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90,},
				{9,40,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_45,},
				{12,7,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{12,6,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{6,8,FL_default,FREE,COMMON_SPEED,80,SEEK_default,PARK_pesL,HR_35}},         

/*11节点*/{		{10,9,FL_default,FREE,COMMON_SPEED,40,SEEK_default,PARK_pesL_200,HR_35},
				{10,12,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL_200,HL_120},
				{10,24,FL_quick,FREE,COMMON_SPEED,0,SEEK_default,PARK_pesL,HL_35}	,
				{10,6,FL_default,FREE,COMMON_SPEED,40,SEEK_default,PARK_pesL_200,HR_45},},

/*12节点*/{		{10,9,FL_quick,PLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{10,24,FL_default,PLATFORM,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{10,11,FL_default,PLATFORM,COMMON_SPEED,10,SEEK_default,PARK_pesR_200,HR_135},
				{7,6,FL_default,PLATFORM,COMMON_SPEED,217,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{6,8,FL_default,FREE,COMMON_SPEED,150,SEEK_PESL,NOTPARK,rot_RFL},},

/*13节点*/{		{14,35,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_45},
				{15,30,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HR_45}, 
				{40,9,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate}, 
				{41,6,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},},

/*14节点*/{		{15,9,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HL_90},
				{37,36,FL_default,FREE,NOSPEED, 0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{16,17,FL_quick,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{35,36,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{44,16,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{44,43,FL_middle,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{42,6,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{37,36,FL_default,FREE,COMMON_SPEED, 0,SEEK_PesPlatform,PARK_PesPlatform,HR_180},
				{6,5,FL_quick,FREE,COMMON_SPEED,22,SEEK4,PARK_pesL,HR_90},
				{16,44,FL_default,ANGLE,NOSPEED,0,SEEK_default,PARK_pesR_150,HR_130},},

/*15节点*/{		{9,5,FL_quick,FREE,COMMON_SPEED,20,SEEK4,PARK_pesR,HL_90},
				{31,32,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{36,24,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_45},
				{30,31,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{13,40,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},
				{13,41,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{14,35,FL_default,FREE,COMMON_SPEED,53,SEEK4,PARK_pesL,HL_90},
				{39,9,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{37,14,FL_default,FREE,COMMON_SPEED,35,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{37,15,FL_default,FREE,COMMON_SPEED,40,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{14,16,FL_default,HEIGHTLITM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate}},

/*16节点*/{		{17,18,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL_No,HL_90},
				{14,38,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{44,45,FL_16_44,FREE,TME,30,SEEK_SeeSaw,NOTPARK,HN_Rotate},
				{44,14,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{14,6,FL_16_44,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},	},
	
/*17节点*/{		{18,20,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{18,19,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{37,36,FL_quick,FREE,NOSPEED, 0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},	\
				{16,14,FL_node,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{43,44,FL_slow,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{43,16,FL_slow,ANGLE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{14,6,FL_default,FREE,COMMON_SPEED,50,SEEK4,PARK_pesL,HL_90},},
							
/*18节点*/{		{20,21,FL_slow,FREE,COMMON_SPEED,40,SEEK4,PARK_pesL_No,HL_90},
				{19,18,FL_slow,FREE,NOSPEED,0,SEEK_Collision_1,NOTPARK,HN_Rotate},
				{17,37,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},
				{17,43,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},
				{17,14,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},},

/*19节点*/{		{18,17,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},
				{18,20,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HR_90},	},

/*20节点*/{		{21,22,FL_default,FREE,COMMON_SPEED,20,SEEK4,PARK_pesL_No,HL_90},
				{18,17,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{18,19,FL_default,FREE,COMMON_SPEED,40,SEEK_default,PARK_pesR,HR_90}},

/*21节点*/{		{22,23,FL_default,FREE,COMMON_SPEED,25,SEEK_default,PARK_pesR_150,HR_135},
				{20,18,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},	
				{20,17,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},},

/*22节点*/{		{23,24,FL_default,FREE,COMMON_SPEED,30,SEEK_default,PARK_pesR_250,HR_145},
				{21,20,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},
				{23,25,FL_default,FREE,COMMON_SPEED,30,SEEK_default,PARK_pesR_250,HL_45}},

/*23节点*/{		{33,38,FL_slow,BACK_TILT_L,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{24,23,FL_default,Peak,NOSPEED,0,NOTSEEK,PARK_PesPlatform,HN_Rotate},
				{25,26,FL_default,STEP2,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},
				{22,21,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL_150,HL_145},
				{33,31,FL_slow,BACK_TILT_L,NOSPEED,0,SEEK4,PARK_pesL,HR_90},
				{33,34,FL_slow,BACK_TILT_L,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
        {25,28,FL_default,STEP2,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},},
	
/*24节点*/{		{36,37,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_60},
				{10,9,FL_slow,BACK_TILT_R,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{10,11,FL_slow,BACK_TILT_R,NOSPEED,0,SEEK4,PARK_pesL,HR_45},
				{36,15,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_60},
				{23,25,FL_default,DOWNPLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{36,17,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_60},
				{23,22,FL_downPeak,DOWNPLATFORM,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},
				{23,33,FL_default,DOWNPLATFORM,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},},

/*25节点*/{		{26,27,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesL_No,HL_90},
				{33,34,FL_slow,BACK_TILT_R,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{33,31,FL_slow,BACK_TILT_R,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{33,38,FL_slow,BACK_TILT_R,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{23,22,FL_slow,FREE,NOSPEED,0,SEEK_default,NOTPARK,HR_35},
				{28,50,FL_default,HEIGHTLITM,NOSPEED,0,SEEK_default,PARK_pesL_No,HL_90},
				{23,24,FL_slow,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate}},

/*26节点*/{		{27,26,FL_default,S_BOARD_26_27,NOSPEED,0,NOTSEEK,PARK_PesPlatform,HN_Rotate},
				{25,23,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL_No,HL_90},
				{25,28,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},},

/*27节点*/{		{26,25,FL_default,S_BOARD_27_26,NOSPEED,0,SEEK4,PARK_pesR_No,HR_90},	},

/*28节点*/{		{50,49,FL_default,FREE,NOSPEED,0,SEEK_default,NOTPARK,rot_LFL_45},
				{50,30,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{25,26,FL_default,HEIGHTLITM,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},},

/*29节点*/{		{36,37,},	},

/*30节点*/{		{31,32,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{31,33,FL_middle,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HN_Rotate},
				{39,9,FL_default,DOOR,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{15,13,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_45},
				{15,39,FL_middle,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{50,28,FL_default,STEP,NOSPEED,0,SEEK_default,PARK_pesR_No,HR_90}},
	
	
/*31节点*/{		{32,31,FL_slow,FREE,NOSPEED,0,SEEK_Collision_1,NOTPARK,HN_Rotate},
				{33,34,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{33,23,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{30,15,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{30,39,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{33,25,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{9,5,FL_default,FREE,COMMON_SPEED,40,SEEK4,PARK_pesR,HL_90},
				{15,9,FL_quick,FREE,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{30,50,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL_No,HL_90},
				{15,14,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},},
							
/*32节点*/{		{31,15,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HR_90},
				{31,30,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},},

/*33节点*/{		{23,24,FL_slow,GO_TILT_R,TME,13,SEEK_default,NOTPARK,HN_Rotate},
				{25,26,FL_default,GO_TILT_L,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},
				{38,15,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{34,35,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HR_90},
				{38,37,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},
				{31,32,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{31,30,FL_middle,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},}, 
						
						
/*34节点*/{		{35,36,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{33,31,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},	},

/*35节点*/{		{36,35,FL_slow,FREE,NOSPEED,0,SEEK_Collision_1,NOTPARK,HN_Rotate},
				{14,37,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_90},
				{14,16,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{34,33,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{14,42,FL_default,FREE,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{14,6,FL_middle,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{6,5,FL_default,FREE,COMMON_SPEED,55,SEEK4,PARK_pesL,HR_90},},

/*36节点*/{		{37,36,FL_default,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{24,10,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},
				{15,38,FL_quick,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{35,14,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HR_90},
				{35,6,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HR_90},
				{17,18,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{15,30,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},
				{15,30,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},
				{15,39,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HR_90},
				{35,34,BACK_NFL,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_90},},

						
/*37节点*/{		{36,24,FL_default,PLATFORM,NOSPEED,0,SEEK4,PARK_pesR,HR_135},
				{36,15,FL_quick,PLATFORM,NOSPEED,0,SEEK_default,NOTPARK,HN_Rotate},
				{14,16,FL_default,PLATFORM,COMMON_SPEED,143,SEEK4,NOTPARK,HN_Rotate},
				{15,14,FL_default,PLATFORM,COMMON_SPEED,40,SEEK_PESL,NOTPARK,HN_Rotate},
				{14,35,FL_default,PLATFORM,COMMON_SPEED,140,SEEK_default,PARK_pesL,HL_90},
				{17,18,FL_default,PLATFORM,COMMON_SPEED,250,SEEK_default,PARK_pesL_No,HL_90},
				{15,31,FL_default,PLATFORM,COMMON_SPEED,45,SEEK_default,PARK_pesL,HL_90}},

/*38节点*/{		{33,23,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{15,36,FL_default,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{37,36,FL_quick,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{14,35,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesL,HL_90},},

/*39节点*/{ 	{15,30,FL_slow,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{9,5,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HL_90},
				{9,40,FL_slow,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HL_135},},

/*40节点*/{		{13,14,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate},
				{9,6,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_135},
				{9,5,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HL_135}, },

/*41节点*/{ 	{13,15,FL_default,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HN_Rotate}, },

/*42节点*/{		{14,44,FL_default,FREE,COMMON_SPEED, 65,SEEK4,PARK_pesR,HR_90},
				{14,37,FL_default,FREE,COMMON_SPEED, 65,SEEK4,PARK_pesR,HL_90},
				{6,5,FL_default,FREE,COMMON_SPEED, 65,SEEK_default,PARK_pesL,HR_90},},

/*43节点*/{		{44,14,FL_43_44,FREE,NOSPEED,0,SEEK_PESL,NOTPARK,HL_30},
				{16,44,FL_16_44,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HL_35},
				{16,17,FL_circular,FREE,NOSPEED,0,SEEK_default,PARK_pesR_250,HR_145},
				{17,18,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesL_No,HL_90},
				{44,37,FL_43_44,FREE,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{16,14,FL_43_44,FREE,NOSPEED,0,SEEK_default,PARK_pesR,HL_30},},

/*44节点*/{		{14,38,FL_default,FREE,NOSPEED,0,SEEK4,NOTPARK,HN_Rotate},
				{45,46,FL_slow,SEESAW,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{43,17,FL_node,FREE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{37,36,FL_slow,FREE,COMMON_SPEED,275,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{14,6,FL_default,FREE,COMMON_SPEED,30,SEEK4,PARK_pesL,HL_90},},

/*45节点*/{		{46,47,FL_circular,FREE,NOSPEED,0,SEEK_default,PARK_pesL,HL_90},},

/*46节点*/{		{47,46,FL_slow,FREE,NOSPEED,0,SEEK_PesPlatform,PARK_PesPlatform,HN_Rotate},
				{43,16,FL_circular,SLOPE,NOSPEED,0,SEEK_PESR,NOTPARK,HN_Rotate},
				{43,44,FL_circular,SLOPE,NOSPEED,0,SEEK_default,PARK_pesR,HL_30},
				{48,43,FL_16_44,FREE,NOSPEED,30,SEEK_SeeSaw_back,NOTPARK,HN_Rotate},},

/*47节点*/{		{46,43,FL_default,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesR,HL_105},
				{46,48,FL_slow,PLATFORM,NOSPEED,0,SEEK_default,PARK_pesR,HL_105},},

/*48节点*/{		{43,44,FL_slow,SEESAW,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{43,16,FL_slow,SEESAW,NOSPEED,0,NOTSEEK,NOTPARK,HN_Rotate},
				{43,17,FL_slow,SEESAW,NOSPEED,0,SEEK_default,PARK_pesR_250,HR_180},
				{16,44,FL_slow,SEESAW,NOSPEED,0,SEEK_default,PARK_pesR,HL_35}},

/*49节点*/{	  {15,9,FL_default,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},	
				{37,49}		},
 
/*50节点*/{	  {30,31,FL_slow,FREE,NOSPEED,0,SEEK4,PARK_pesR,HR_90},	
		    {49,15,FL_default,FREE,COMMON_SPEED,15,SEEK4,PARK_pesR_200,HL_45},
				{28,25,FL_default,FREE,NOSPEED,0,SEEK_default,PARK_pesR_No,HR_90},}
};























//障碍物为门的线路为:9,39,15;   9,40,13;      



//从门前的节点回到门前障碍物不是门，是无障碍物，例如9,40,9障碍物不是门










