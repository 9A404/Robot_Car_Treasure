#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "sys.h"


#define NODEFORKNUM  	15			//��ͼ����һ�ڵ���������Ŀ * ���½ڵ���������Ŀ


/*Ѳ�߷���*/
typedef enum {FL_default,FL_circular,FL_node,FL_43_44,FL_16_44,FL_angle,FL_slow_angle,FL_middle,FL_brige,FL_brigeup,FL_brigedown,
	FL_slow,FL_quick,FL_stop,FL_quickest,FL_upPeak,FL_downPeak,FL_UpPlatform,FL_DownPlatform,
	FL_left,FL_left_45,FL_Right,NFL,NFL_slow,BACK_NFL,FL_UPRISE,FL_DOWNRISE}findLine;
		
/*·������*/
typedef enum {FREE,BRIGE,DOOR,S_BOARD_1,S_BOARD_2,S_BOARD_26_27,SEESAW,GO_TILT_R,GO_TILT_L,
							BACK_TILT_R,BACK_TILT_L,SLOPE,SLOPE_46_43,PLATFORM,PLATFORM_1,Peak,TRAPEZOID_1,TRAPEZOID_2,TRAPEZOID_3,
							DOWNPLATFORM,ALL_TILT,DOWN27_26,ANGLE,STEP,HEIGHTLITM,STEP2}typeRoadblock;	//���ϰ����š��š����ٴ������ΰ塢��б·�桢б�¡�ƽ̨���㡢���ξ��㡢���ӽڵ㶨ʱ                                                                                                                                  

	
/*��������*/
typedef enum {DOWN_SPEED,COMMON_SPEED,NOSPEED,TME,UPRISE}typeSpeed;//��̨���٣���ͨ���٣������٣�ռʱ�䣨���ڴ����ӽڵ�)

/*�ҽڵ㷽��*/
typedef enum {SEEK_PESL,SEEK_PESR,SEEK3,SEEK4,SEEK_default,NOTSEEK,SEEK_SeeSaw,SEEK_SeeSaw_back,
SEEK_PesPlatform,SEEK_Collision,SEEK_Collision_1,SEEK_7_6_15,SEEK_6_15_37,SEEK_digR,SEEK_digL}seekNodeWay;

/*ͣ������*/
typedef enum {NOTPARK,PARK1,PARK_pesR,PARK_pesR_150,PARK_pesR_200,PARK_pesR_250,PARK_pesR_300,PARK_pesR_350,PARK_pesR_400,
							PARK_default,PARK_pesL,PARK_pesL_150,PARK_pesL_200,PARK_pesL_250,PARK_pesL_300,PARK_pesL_350,PARK_pesL_400,	
							PARK_PesPlatform,PARK_Door,PARK_pesR_No,PARK_pesL_No,PARK_pesL_back,PARK_pesR_back}carPark;

/*��ͷ��ת�Ƕ�*/
typedef enum {HL_180,HL_145,HL_135,HL_105,HL_120,HL_90,HL_60,HL_45,HL_35,HL_30,
						HN_Rotate,HR_35,HR_45,HR_60,HR_90,HR_110,HR_130,HR_135,HR_145,HR_180,
						rot_LFL, rot_LFL_45,rot_RFL,rot_UL,rot_UR,Sensor_L90,Sensor_R90}carRotAngle;

/*״̬�ź�*/
typedef enum {NTBE,EIC,STANDBY}updataState;		//��Ҫִ�� ִ����� ����


/*��·����Ϣ���м�¼*/
typedef	struct{

	u8	nextNode;										//��һ���ڵ�
	u8	nnNode;											//���¸��ڵ�
	findLine      findLineWays;			//Ѳ�߷���
	typeRoadblock	typeRoadblock;		//·������
	typeSpeed typeSpeed; 				//��������
	u16 speedTime;						//����ʱ��
	seekNodeWay   seekways;					//�ҵ㷽��
	carPark  			parkways;					//ͣ������
	carRotAngle 	rotateAngle;			//��ǰ��ͷλ�û���������ת�Ƕ�
	
}linkInforTypeDef;

/*�Ե�ͼ·����Ϣ���м�¼*/
typedef	struct{

	u8	map_nextNode;										//��ͼ��һ���ڵ�
	u8	map_nnNode;											//��ͼ���¸��ڵ�
	findLine      map_findLineWays;			//��ͼѲ�߷���
	typeRoadblock	map_typeRoadblock;		//��ͼ·������
	typeSpeed map_typeSpeed; 				//��ͼ��������
	u16 map_speedTime;						//��ͼ����ʱ��
	seekNodeWay   map_seekways;					//��ͼ�ҵ㷽��
	carPark  			map_parkways;					//��ͼͣ������
	carRotAngle 	map_rotateAngle;			//��ͼ��ͷ��ת����
	
}map_linkInforTypeDef;



/*�Կ�������״̬���м�¼*/
typedef	struct{

	u8  curNode;								//��ǰ�ڵ�
	u8	nextNode;								//��һ���ڵ�
	u8	nnNode;									//���¸��ڵ�
	u8	nodeNum;								//�ڵ���
	linkInforTypeDef	linkInform;//·����Ϣ
	updataState	update;						//״̬�ź�
		

}controlCenterTypeDef;


/*������״̬���м�¼,��ÿ��·�θ���״̬�������*/
/*˼·��
ÿ����������״̬
1��NTBE����Ҫִ�У���
2��EIC��ִ����ɣ���
3��STANDBY������������ζ����Ҫ����״̬����������������״̬����ɣ�NTBE��
���磺�ҵ���Ҫ·��״̬�Ĵ�����ͣ����Ҫ�ҵ�״̬�Ĵ�����ת����Ҫ�ҵ�״̬����
*/
typedef	struct{

	updataState	F_LineState;					//Ѳ��״̬
	updataState	F_RoadBlockState;			//���ϰ�״̬
	updataState speedState;					//����״̬
	updataState seekNodeState;				//�ҵ�״̬
	updataState carParkState;					//ͣ��״̬
	updataState	RotangleState;				//ת��״̬
	
}runStateTypeDef;

void Control_Init(controlCenterTypeDef *controlp,u8*runMethod);//�������ĳ�ʼ������
void updataState_Reset(controlCenterTypeDef *p,updataState state);//���Ŀ�������״̬�ź�
unsigned char control_Update(controlCenterTypeDef *controlp,u8 nodeLength,const u8 *runMethod,const map_linkInforTypeDef(*p)[NODEFORKNUM] );//���¿������ģ�controlCenterTypeDef�ṹ�壩�Ĳ���
void runStateInit(runStateTypeDef *runState,const controlCenterTypeDef *controlp);//���ݿ���̨��ʼ·�γ�ʼ������״̬
void runStateReset(runStateTypeDef *runState,const controlCenterTypeDef *controlp);//���ݿ���̨�ж��Ƿ������µ�·�Σ�Ȼ��������������״̬
void runMethodReset(u8 runMethod[],const u8 runMethod_2[]); //����·��
//void DoorMethodUpdate(controlCenterTypeDef *controlp,u8 runMethod[],u8 DoorFlag,const u8 runMethodTableDoorAuto[][100]);   //�Զ��л�������·����
void runMethodUpdate(u8 runMethod[],u8 runMethodNum, const u8 runMethodTab[][100]); //�ӱ���и���·��
void CheckrunMethod(u8 runMethod[]); //����·����ȥ���ڼ���ƽ̨

void findLine_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);         //Ѳ������
void roadBlocksHandle_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);//�ϰ���������
void speed_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);		  //��������
void seekNode_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);       // �ҵ�����
void carPark_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState);       // ͣ������
void rotAngle_Task(controlCenterTypeDef *controlp,runStateTypeDef *runState);           //  ת������

void runStateReset1(runStateTypeDef *runState,const controlCenterTypeDef *controlp);
#endif

