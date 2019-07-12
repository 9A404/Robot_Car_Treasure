#include "control.h"
#include "string.h"
#include "myconfig.h"

extern const map_linkInforTypeDef mapInformation[][NODEFORKNUM];


/*sizeof(runMethod) / sizeof(runMethod[0])得到数组元素个数*/

///*

//* 函数介绍：控制中心初始化函数
//* 输入参数：controlp(更新的控制中心名字)curNode(当前节点编号)nextNode（下一节点编号）nnNode（下下节点编号）nodeNum（路线中待跑编号的位置）
//* 输出参数：无
//* 返回值  ：无
//* 作者    ：@断忆

//*/
//void Control_Init(controlCenterTypeDef *controlp,u8 curNode,u8 nextNode,u8 nnNode,u8 nodeNum)
//{
//	memset(controlp,0,sizeof(controlCenterTypeDef));//对控制中心结构体清零
//	
//	controlp->curNode =	curNode;
//	controlp->nextNode = nextNode;
//	controlp->nnNode	 = nnNode;
//	controlp->nodeNum	= nodeNum;
//	controlp->update	=	EIC;

//}



/*

* 函数介绍：更改控制中心状态信号
* 输入参数：p(控制中心名字)	updataState（输入状态信号）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void updataState_Reset(controlCenterTypeDef *p,updataState state)
{
	p->update = state;
}




/*

* 函数介绍：将路段信息更新到控制中心
* 输入参数：controlp(更新的控制中心名字)p(地图规则表)
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
static void	linkInformUpdate(controlCenterTypeDef *controlp,const map_linkInforTypeDef(*p)[NODEFORKNUM])
{
		int i;
		for(i = 0;i < NODEFORKNUM;i++)
			{
				if(controlp->nextNode == (*(p+controlp->curNode)+i)->map_nextNode)
				{
					if(controlp->nnNode == (*(p+controlp->curNode)+i)->map_nnNode)
					{
						controlp->linkInform.findLineWays = (*(p+controlp->curNode)+i)->map_findLineWays;
						controlp->linkInform.typeRoadblock = (*(p+controlp->curNode)+i)->map_typeRoadblock;
						controlp->linkInform.typeSpeed = (*(p+controlp->curNode)+i)->map_typeSpeed;
						controlp->linkInform.speedTime = (*(p+controlp->curNode)+i)->map_speedTime;
						controlp->linkInform.seekways = (*(p+controlp->curNode)+i)->map_seekways;
						controlp->linkInform.parkways = (*(p+controlp->curNode)+i)->map_parkways;
						controlp->linkInform.rotateAngle = (*(p+controlp->curNode)+i)->map_rotateAngle;
						break;
					}
				}
			
			}


}
/*

* 函数介绍：控制中心初始化函数
* 输入参数：controlp(更新的控制中心名字)curNode(当前节点编号)nextNode（下一节点编号）nnNode（下下节点编号）nodeNum（路线中待跑编号的位置）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void Control_Init(controlCenterTypeDef *controlp,u8*runMethod)
{
	memset(controlp,0,sizeof(controlCenterTypeDef));//对控制中心结构体清零
	
	controlp->curNode =	runMethod[0];
	controlp->nextNode = runMethod[1];
	controlp->nnNode	 = runMethod[2];
	controlp->nodeNum	= 3;
	controlp->update	=	EIC;

}

/*

* 函数介绍：更新控制中心（controlCenterTypeDef结构体）的参数。注意：只有当到达新节点的时候才会更新
* 输入参数：controlp（控制中心）、nodeLength（路线节点总个数）runMethod（路线数组）p（地图规则）
* 输出参数：无
* 返回值  ：1(更新成功)0(更新失败)
* 作者    ：@断忆

*/
	unsigned char control_Update(controlCenterTypeDef *controlp,u8 nodeLength,const u8 *runMethod,const map_linkInforTypeDef(*p)[NODEFORKNUM] )
	{
		if(controlp->update == EIC)
		{
			/*找出接下来寻迹的路段并将信息更新到控制中心*/
			linkInformUpdate(controlp,p);
			
			/*更新控制中心curNode、nextNode、nnNode*/
			if(controlp->nodeNum < nodeLength)
				{
					controlp->curNode = controlp->nextNode;
					controlp->nextNode = controlp->nnNode;
					controlp->nnNode = runMethod[controlp->nodeNum];
					controlp->nodeNum++;
				}
			else
				{
					controlp->curNode = controlp->nextNode;
					controlp->nextNode = controlp->nnNode;
				}
			
				/*将控制中心的状态标志位设置成NTBE*/
			updataState_Reset(controlp,NTBE);
		
		return 1;
		}
		return 0;
	}
	





/*

* 函数介绍：根据控制台起始路段初始化运行状态
* 输入参数：runState(运行状态记录器的地址) controlp（控制台的地址）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/	
void runStateInit(runStateTypeDef *runState,const controlCenterTypeDef *controlp)
{
		runState->F_LineState = NTBE;					//需要执行	
		runState->F_RoadBlockState = (controlp->linkInform.typeRoadblock==FREE)?EIC:NTBE; //没有路障的时候就（执行完成），有路障就（需要执行）
		runState->speedState = STANDBY;			//待命状态等待路障来触发
		runState->seekNodeState = STANDBY;		//待命状态等待“加速处于EIC”来触发
		runState->carParkState = STANDBY;			//待命状态等待“找点处于EIC”触发
		runState->RotangleState = STANDBY;		//待命状态等待“停车处于EIC”触发
}	
	
	
	
	
	
/*

* 函数介绍：根据控制台判断是否来到新的路段，然后重新设置运行状态
* 输入参数：runState(运行状态记录器的地址) controlp（控制台的地址）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/

void runStateReset(runStateTypeDef *runState,const controlCenterTypeDef *controlp)
{
		runState->F_LineState = ((controlp->curNode==controlp->nextNode)&&(controlp->nextNode==controlp->nnNode))?EIC:NTBE;						//需要执行		
		runState->F_RoadBlockState = (controlp->linkInform.typeRoadblock==FREE)?EIC:NTBE; //没有路障的时候就（执行完成），有路障就（需要执行）
		runState->speedState = STANDBY;			//待命状态等待路障来触发
		runState->seekNodeState = STANDBY;		//待命状态等待“加速处于EIC”来触发
		runState->carParkState = STANDBY;	//待命状态等待“找点处于EIC”触发
		runState->RotangleState = STANDBY;	//待命状态等待“停车处于EIC”触发

}

void runStateReset1(runStateTypeDef *runState,const controlCenterTypeDef *controlp){
	
		runState->F_LineState = EIC;
		runState->F_RoadBlockState = EIC;
	    runState->seekNodeState = EIC;
	    runState->carParkState = EIC;
	    runState->RotangleState = EIC;
}
/*

* 函数介绍：重置奔跑路线
* 输入参数：runMethod(储存被替换奔跑路线) runMethod_2（存储替换的奔跑的路线）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void runMethodReset(u8 runMethod[],const u8 runMethod_2[])
{
	u8 i=0;
	/*数组清零*/
	while(runMethod[i]!= 0)
	{
		runMethod[i]= 0;
		i++;
	}
	/*更新路线*/
	i=0;
	while(runMethod_2[i] != 0)
	{
		runMethod[i] = runMethod_2[i];
		i++;
	}
	
}
/*

* 函数介绍：查找路线去到第几个平台，方便切换路线
* 输入参数：runMethod(储存被替换奔跑路线)
* 输出参数：无
* 返回值  ：无
* 作者    ：@林

*/
void CheckrunMethod(u8 runMethod[])
{
	u8 i=0;
	/*如果查找到路线中包含有37或者47号，返回1*/
	while(runMethod[i]!= 0)
	{
		if(runMethod[i]==37 || runMethod[i]==47) 
		{
			RunMethod_Check=1;
			break;
		}
		i++;
	}
	
	/*继续如果查找到路线中包含有27或者24号，返回2*/
	i=0;
	while(runMethod[i]!= 0)
	{
		if(runMethod[i]==27 || runMethod[i]==24) 
		{
			RunMethod_Check=2;
			break;
		}
		i++;
	}
	
}


/*

* 函数介绍：从奔跑路线表格中选择奔跑路线
* 输入参数：runMethod(储存被替换奔跑路线) runMethodNum(第几条路线)runMethodTab（路线表）
* 输出参数：无
* 返回值  ：无
* 作者    ：@断忆

*/
void runMethodUpdate(u8 runMethod[],u8 runMethodNum, const u8 runMethodTab[][100])
{
	u8 i=0;
	/*数组清零*/
	while(runMethod[i]!= 0)
	{
		runMethod[i]= 0;
		i++;
	}
	/*更新路线*/
	i=0;
	while(runMethodTab[runMethodNum][i] != 0)
	{
		runMethod[i] = runMethodTab[runMethodNum][i];
		i++;
	}
	
}









/*

* 函数介绍：巡线任务
* 输入参数：controlp（控制台的地址） runState(运行状态记录器的地址)
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的巡线方法执行相应方法,根据运行状态决定是否运行
* 作者    ：@断忆

*/
void findLine_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
		#ifdef Fast_FL
		if(runState->F_LineState == NTBE)
		{
			switch(controlp->linkInform.findLineWays)
			{
				case FL_default: 	 flMethod_default();break;
				case FL_node: 	 flMethod_node();break;
				case FL_43_44: 	 flMethod_43_44();break;
				case FL_16_44: 	 flMethod_16_44();break;
				case FL_circular: 	 flMethod_circular();break;
				case FL_middle: 	 flMethod_middle();break;
				case FL_brige: 	 	 flMethod_brige();break;
				case FL_brigeup:   flMethod_brige_up();break;
				case FL_brigedown: flMethod_brige_down();break;
				case FL_slow:			 flMethod_slow();break;
				case FL_UpPlatform:	flMethod_UpPlatform();break;
				case FL_DownPlatform:	flMethod_DownPlatform();break;
				case FL_quick:		 flMethod_quick();break;
				case FL_stop :		 flMethod_stop();break;
				case FL_quickest	:flMethod_quickest();	break;
				case FL_upPeak		:flMethod_upPeak();break;
				case FL_downPeak	:flMethod_downPeak();break;
				case FL_left			:flMethod_left();break;
				case FL_Right			:flMethod_right();break;
				case NFL: 			 speedAdjustment(2090,2100);break;
				case FL_angle:   flMethod_NFL();break;
				case FL_slow_angle :flMethod_NFL_slow();break;
				case NFL_slow:   speedAdjustment(1100,1100);break;
				case BACK_NFL:   speedAdjustment(-1300,-1315);break;
				case FL_UPRISE:	 flMethod_upRise();break;
				case FL_DOWNRISE:flMethod_downRise();break;
				default:  break;
			}
		}
		#endif
		
		#ifdef Slow_FL
		if(runState->F_LineState == NTBE)
		{
			switch(controlp->linkInform.findLineWays)
			{
				case FL_default: 	 flMethod_slow();break;
				case FL_node: 	   flMethod_node();break;
				case FL_43_44: 	 flMethod_43_44();break;
				case FL_16_44: 	 flMethod_16_44();break;
				case FL_circular: 	 flMethod_circular();break;
				case FL_middle: 	 flMethod_slow();break;
				case FL_brige: 	 	 flMethod_brige();break;
				case FL_brigeup:   flMethod_brige_up();break;
				case FL_brigedown: flMethod_brige_down();break;
				case FL_slow:			 flMethod_slow();break;
				case FL_UpPlatform:	flMethod_UpPlatform();break;
				case FL_DownPlatform:	flMethod_DownPlatform();break;
				case FL_quick:		 flMethod_slow();break;
				case FL_stop :		 flMethod_stop();break;
				case FL_quickest	:flMethod_slow();	break;
				case FL_upPeak		:flMethod_upPeak();break;
				case FL_downPeak	:flMethod_downPeak();break;
				case FL_left			:flMethod_left();break;
				case FL_Right			:flMethod_right();break;
				case NFL: 			 speedAdjustment(2090,2000);break;
				case NFL_slow:   speedAdjustment(1100,1100);break;
				case BACK_NFL:   speedAdjustment(-1300,-1315);break;
				default:  break;
			}
		}
		#endif
		else if(runState->F_LineState == EIC)
			{
				
				if(3 == runTimes)
				{
//					delay_ms(1000);
//					delay_ms(1000);
					runTimes = 1;
					speedAdjustment(0,0);  //停车
					Treasure_all_Flag = 0;
				}
				
				else if(4 == runTimes)
				{
					speedAdjustment(0,0);  //停车
					runTimes = 5;
					//u3_printf("\nFinish!\n");
					Gui_DrawFont_GBK16(0,80,RED,WHITE,"Finish");
					while(1)
					{
						/*当有按键按下就跳出*/
						keyFlag = keyScan(0);
						if(keyFlag==KEY4_ESC)
						{
							keyFlag = 0;
							Gui_DrawFont_GBK16(0,100,RED,WHITE,"ESC_Again");
							break;
						}
					}
				}	
			}
	
	
}



/*

* 函数介绍：路障解决任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的路障类型判断出路障并执行处理方法，
* 作者    ：@断忆

*/
void roadBlocksHandle_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if((runState->F_RoadBlockState==NTBE) && (runState->F_LineState != EIC))
	{
		switch(controlp->linkInform.typeRoadblock)
		{
			case FREE :{
									runState->F_RoadBlockState = EIC;
									#ifdef BlueTooth_Debug
										u3_printf("FREE_EIC\r\n ");
									#endif
									}break;
			case ANGLE:if(1 == Angle_read())
									{
										runState->F_RoadBlockState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("Bright_EIC\r\n");
										#endif
									}break; 
			case BRIGE:if(1 == BlockHandleMethod_Brige())
									{
										runState->F_RoadBlockState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("Bright_EIC\r\n");
										#endif
									}break;  
			case DOOR	:if(1==BlockHandleMethod_DOOR())
									{
										runState->F_RoadBlockState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("Door_EIC\r\n ");
										#endif
									}break;
			case S_BOARD_1:	if(1==BlockHandleMethod_S_BOARD_1())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("S_BOARD_EIC\r\n");
												#endif
											}break;
			case S_BOARD_2:	if(1==BlockHandleMethod_S_BOARD_2())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("S_BOARD_EIC\r\n");
												#endif
											}break;
			case S_BOARD_26_27:	if(1==BlockHandleMethod_26_27())
													{
														runState->F_RoadBlockState = EIC;
														#ifdef BlueTooth_Debug
															u3_printf("S_BOARD_EIC\r\n");
														#endif
													}break;
			case SEESAW:	if(1==BlockHandleMethod_Seesaw())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("SEESAW_EIC\r\n");
											#endif
										}break;
		
			case GO_TILT_R: if(1 == BlockHandleMethod_GO_Tilt_R())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("GO_Tilt_R_EIC\r\n");
												#endif
											}break;
			case GO_TILT_L: if(1 == BlockHandleMethod_GO_Tilt_L())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("GO_Tilt_L_EIC\r\n");
												#endif
											}break;
			case BACK_TILT_R:if(1 == BlockHandleMethod_BACK_TILT_R())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("BACK_Tilt_R_EIC\r\n");
												#endif
											}break;
			case BACK_TILT_L:if(1 == BlockHandleMethod_BACK_TILT_L())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
												u3_printf("BACK_Tilt_L_EIC\r\n");
												#endif
											}break;
			case ALL_TILT   :if(1 == BlockHandleMethod_Crossing_All_TILT())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("ALL_TILT_EIC\r\n");
												#endif
											}break;
			
			case SLOPE :if(1 == BlockHandleMethod_Slope ())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("SLOPE_EIC\r\n");
											#endif
										}break;
			 case STEP :if(1 == BlockHandleMethod_Step ())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("SLOPE_EIC\r\n");
											#endif
										}break;
			
			case PLATFORM:if(1 == BlockHandleMethod_Platform ())
										{
											runState->F_RoadBlockState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("Platform_EIC\r\n");
											#endif
										}break;
			case PLATFORM_1:if(1 == BlockHandleMethod_Platform_1 ())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("Platform_1_EIC\r\b");
												#endif
											}break;
			case Peak:if(1 == BlockHandleMethod_Peak())
								{
									runState->F_RoadBlockState = EIC;
									#ifdef BlueTooth_Debug
										u3_printf("upPlatform_EIC\r\n");
									#endif
									
								}break;
			case DOWNPLATFORM:if(1 ==  BlockHandleMethod_downPlatform())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("downPlatform_EIC\r\n");
													#endif
												}break;
			case DOWN27_26   :if(1 == BlockHandleMethod_down_27_26())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("down27_26_EIC\r\n");
													#endif
												}break;
			
			case TRAPEZOID_1:if(1 == BlockHandleMethod_Trapezoid_1())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("Trapezoid_1_EIC\r\n");
												#endif
											}break;
			case TRAPEZOID_2:if(1 == BlockHandleMethod_Trapezoid_2())
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("Trapezoid_2_EIC\r\n");
												#endif
											}break;
			case TRAPEZOID_3:if(1 == BlockHandleMethod_Trapezoid_3())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("Trapezoid_3_EIC\r\n");
													#endif
												}break;
			
			case TIME				:if(1 == BlockHandleMethod_TIME ())			 
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("TIME_EIC\r\n");
													#endif
												}break;
			case TIME_1			:if(1 == BlockHandleMethod_TIME_1 ())		 
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("TIME_EIC_1\r\n");
												#endif
											}break;
			case TIME_2			:if(1 == BlockHandleMethod_TIME_2 ())		 
											{
												runState->F_RoadBlockState = EIC;
												#ifdef BlueTooth_Debug
													u3_printf("TIME_EIC_2\r\n");
												#endif
											}break;
			case TIME_44_43			:if(1 == BlockHandleMethod_TIME_44_43 ())		 
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("TIME_EIC_3\r\n");
													#endif
												}break;
		case TIME_45_46			:if(1 == BlockHandleMethod_TIME_45_46 ())		 
								{
									runState->F_RoadBlockState = EIC;
									#ifdef BlueTooth_Debug
										u3_printf("TIME_EIC_3\r\n");
									#endif
								}break;
					
			case SPEEDTIME_11_10:if(1 == BlockHandleMethod_speedtime_11_10())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
													#endif
												}break;
		case SPEEDTIME_5_10:if(1 == BlockHandleMethod_speedtime_5_10())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
													#endif
												}break;
        case SPEEDTIME_8_6:if(1 == BlockHandleMethod_speedtime_8_6())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
													#endif
												}break;		
			case SPEEDTIME_6_15:if(1 == BlockHandleMethod_speedtime_6_15())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
													#endif
												}break;																
			case SPEEDTIME_2:if(1 == BlockHandleMethod_speedtime_2())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("SeedT_2_EIC\r\n");
													#endif
												}break;
			case SPEEDTIME_7_6:if(1 == BlockHandleMethod_speedtime_7_6())
												{
													runState->F_RoadBlockState = EIC;
													#ifdef BlueTooth_Debug
														u3_printf("SeedT_7_6_EIC\r\n");
													#endif
												}break;
			case SPEEDTIME_36_17	:if(1 == BlockHandleMethod_speedtime_36_17 ())
															{
																runState->F_RoadBlockState = EIC;
																#ifdef BlueTooth_Debug
																	u3_printf("SeedT_36_17_EIC\r\n");
																#endif
															}break;
			case SPEEDTIME_44_37	:if(1 == BlockHandleMethod_speedtime_44_37()) 
														{
															runState->F_RoadBlockState = EIC;
															#ifdef BlueTooth_Debug
																u3_printf("SeedT_17_37_EIC\r\n");
															#endif
														}break;
			case SPEEDTIME_14_37  :if(1 == BlockHandleMethod_speedtime_14_37()) 
															{
																runState->F_RoadBlockState = EIC;
																#ifdef BlueTooth_Debug
																	u3_printf("SeedT_17_37_EIC \r\n");
																#endif
															}break;
			case SPEEDTIME_6_7:if(1 == BlockHandleMethod_speedtime_6_7())
													{
														runState->F_RoadBlockState = EIC;
														#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
														#endif
													}break;
			case SPEEDTIME_5_12:if(1 == BlockHandleMethod_speedtime_5_12())
													{
														runState->F_RoadBlockState = EIC;
														#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
														#endif
													}break;
		    case SPEEDTIME_12_6:if(1 == BlockHandleMethod_speedtime_12_6())
													{
														runState->F_RoadBlockState = EIC;
														#ifdef BlueTooth_Debug
															u3_printf("SeedT_1_EIC\r\n");
														#endif
													}break;
			default:  			break;
		}
	}
	
}


/*

* 函数介绍：加速任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他	  ：根据控制台的路段信息的找点方法执行相应方法
* 作者    ：@袁梓聪

*/
void speed_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState){

	if(runState->speedState == NTBE){
		
		switch(controlp->linkInform.typeSpeed){
			
			case DOWN_SPEED:if(1 == Speed_downMethod(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case COMMON_SPEED:if(1 == Speed_commonMethod(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case NOSPEED:if(1)
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case TME:if(1 == Take_up_time(controlp->linkInform.speedTime))
							{
								runState->speedState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
		}
			
	}
	else if(runState->speedState == STANDBY)
	{
		if(runState->F_RoadBlockState == EIC)
			runState->speedState = NTBE;	
	}

}



/*

* 函数介绍：找点任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他	  ：根据控制台的路段信息的找点方法执行相应方法
* 作者    ：@断忆

*/
void seekNode_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->seekNodeState == NTBE)
	{
		switch(controlp->linkInform.seekways)
		{
			case SEEK_PESL:if(1 == seekNodeMethod_pesL())
							{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESL_EIC\r\n");
								#endif
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case SEEK_PESR:if(1 == seekNodeMethod_pesR())
							{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_PESR_EIC\r\n");
								#endif
								
								
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case SEEK3:if(1 == seekNodeMethod_4())
						{
							runState->seekNodeState=EIC;
							#ifdef BlueTooth_Debug
								u3_printf("SSEEK3_EIC\r\n");
							#endif
					
					
							#ifdef LED_Debug
								led_flash();
							#endif
						}break;
			case SEEK4:if(1 == seekNodeMethod_10())
						{
							runState->seekNodeState=EIC;
							#ifdef BlueTooth_Debug
								u3_printf("SEEK4_EIC\r\n");
							#endif
					
							#ifdef LED_Debug
								led_flash();
							#endif
						}break;
			case SEEK_default:if(1 == seekNodeMethod_default())
							{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_default_EIC\r\n");
								#endif
									
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
		   case SEEK_7_6_15:if(1 == seekNodeMethod_7_6_15())
							{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_default_EIC\r\n");
								#endif
									
								#ifdef LED_Debug
									led_flash();
								#endif
						}break;
			case SEEK_6_15_37:if(1 == seekNodeMethod_6_15_37())
							{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("SEEK_default_EIC\r\n");
								#endif
									
								#ifdef LED_Debug
									led_flash();
								#endif
							}break;
			case NOTSEEK:if(1)
						{
								runState->seekNodeState=EIC;
								#ifdef BlueTooth_Debug
									u3_printf("NOTSEEK_EIC\r\n");
								#endif
							
								#ifdef LED_Debug
									led_flash();
								#endif
						}break;
			case SEEK_PesPlatform:if(1==seekNodeMethod_pesPlatform())
								{
									runState->seekNodeState=EIC;
									#ifdef BlueTooth_Debug
										u3_printf("SEEK_PesPlatform\r\n");
									#endif
									
									#ifdef LED_Debug
									led_flash();
									#endif
								}break;
			case SEEK_Collision:if(1==seekNodeMethod_Collision())
								{
									runState->seekNodeState=EIC;
									#ifdef BlueTooth_Debug
										u3_printf("SEEK_Collision\r\n");
									#endif
											
											
									#ifdef LED_Debug
										led_flash();
									#endif
								}break;
			case SEEK_Collision_1:if(1==seekNodeMethod_Collision_1())
								{
									runState->seekNodeState=EIC;
									#ifdef BlueTooth_Debug
										u3_printf("SEEK_Collision_1\r\n");
									#endif
											
											
									#ifdef LED_Debug
										led_flash();
									#endif
								}break;
			case SEEK_SeeSaw:if(1==seekNodeMethod_SeeSaw())
							{
									runState->seekNodeState=EIC;
									#ifdef BlueTooth_Debug
										u3_printf("SEEK_SeeSaw\r\n");
									#endif
										
									#ifdef LED_Debug
										led_flash();
									#endif
							}break;
			case SEEK_SeeSaw_back:if(1==seekNodeMethod_SeeSaw_back())
								{
									runState->seekNodeState=EIC;
									#ifdef BlueTooth_Debug
										u3_printf("SEEK_SeeSaw\r\n");
									#endif
										
									#ifdef LED_Debug
										led_flash();
									#endif
							}break;
			default: 		break;
		
		}
	
	}
	else if(runState->seekNodeState == STANDBY)
	{
		if(runState->speedState == EIC)
			runState->seekNodeState = NTBE;	
	}
	
}
/*

* 函数介绍：停车任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的停车方法执行相应方法
* 作者    ：@断忆

*/
void carPark_Task(const controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->carParkState == NTBE)
	{
		switch(controlp->linkInform.parkways)
			{
				case NOTPARK:{
									runState->carParkState = EIC;
				            		#ifdef BlueTooth_Debug
										u3_printf("NOTPARK_EIC\r\n");
									#endif
							}break;
				case PARK1:		if(1){
											runState->carParkState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("PARK1_EIC\r\n");
											#endif
									}break;
				case PARK_pesR:		if(1 == parkMethod_pesR())
									{
										runState->carParkState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("PARK_pesR_EIC\r\n");
										#endif
									}break;
				case PARK_default:if(1 == parkMethod_default())
									{
										runState->carParkState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("PARK_default_EIC\r\n");
										#endif
									}break;
				case PARK_pesL:		if(1 == parkMethod_pesL())
									{
										runState->carParkState = EIC;
										#ifdef BlueTooth_Debug
											u3_printf("PARK_pesL_EIC\r\n");
										#endif
									}break;
				case PARK_PesPlatform:	if(1==parkMethod_pesPlatform(&glHello_control))
										{
											runState->carParkState = EIC;
											#ifdef BlueTooth_Debug
												u3_printf("PARK_PesPlatform_EIC\r\n");
											#endif
										}break;
				default:break;		
			}
	
	}
	else if(runState->carParkState == STANDBY)
		{
			if(runState->seekNodeState == EIC)
				runState->carParkState=NTBE;	
		}
}

/*

* 函数介绍：转弯任务
* 输入参数：runStateconst(运行状态记录器) controlp（控制台）
* 输出参数：无
* 返回值  ：无
* 其他		：根据控制台的路段信息的转弯方法执行相应方法
* 作者    ：@断忆

*/
void rotAngle_Task(controlCenterTypeDef *controlp,runStateTypeDef *runState)
{
	if(runState->RotangleState == NTBE)
	{
		switch(controlp->linkInform.rotateAngle)
		{
			case HN_Rotate:if(1)
													{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("NotRotAngle_EIC\n\n");
														#endif
													}break;
			case HR_35:	if(1 == rotAngleMethod_R35())
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_35_EIC\n\n");
														#endif
													}break;
			case HR_45:	if(1 == rotAngle_Right(45)) 
								{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_45_EIC\n\n");
														#endif
													}break;
			case HR_60: if(1 == rotAngle_Right(65))	
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_60_EIC\n\n");
														#endif
													}break;
			case HR_90 :if(1 == rotAngle_Right(90))
												{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_90_EIC\n\n");
														#endif
													}break;
			case HR_110:if(1 == rotAngle_Right(110))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_110_EIC\n\n");
														#endif
													}break;
			case HR_135:if(1 ==	rotAngle_Right(135))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_135_EIC\n\n");
														#endif
													}break;
			case HR_130:if(1 ==	rotAngle_Right(130))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_135_EIC\n\n");
														#endif
													}break;
			case HR_145:if(1 == rotAngle_Right(150))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_145_EIC\n\n");
														#endif
													}break;
			case HR_180:if(1 == rotAngle_Right(180))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HR_180_EIC\n\n");
														#endif
													}break;
	    case rot_RFL:if(1 == rotAngleMethod_RFL())
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("rot_RFL_EIC\n\n");
														#endif
													}break;
			case rot_UR :if(1 == rotAngle_UR(90))
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("rot_UR_EIC\n\n");
														#endif
													}break;
			
			case HL_30 :if(1 == rotAngle_Left(15))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_35_EIC\n\n");
														#endif
													}break;
			case HL_35 :if(1 == rotAngle_Left(35))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_35_EIC\n\n");
														#endif
													}break;
			case HL_45 :if(1 == rotAngle_Left(45))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_45_EIC\n\n");
														#endif
													}break;
			case HL_60 :if(1 == rotAngle_Left(60))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_60_EIC\n\n");
														#endif
													}break;
			case HL_90 :if(1 == rotAngle_Left(90))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_90_EIC\n\n");
														#endif
													}break;
			case HL_120 :if(1 == rotAngle_Left(120))
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_120_EIC\n\n");
														#endif
													}break;
			case HL_105 :if(1 == rotAngle_Left(105))
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_110_EIC\n\n");
														#endif
													}break;
			case HL_135:if(1 == rotAngle_Left(135))
								{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_135_EIC\n\n");
														#endif
													}break;
			case HL_145:if(1 == rotAngle_Left(145))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_145_EIC\n\n");
														#endif
													}break;
			case HL_180:if(1 == rotAngle_Left(180))
									{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("HL_180_EIC\n\n");
														#endif
													}break;
			case rot_LFL:if(1 == rotAngleMethod_LFL())
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("rot_LFL_EIC\n\n");
														#endif
													}break;
			case rot_UL :if(1 == rotAngle_UL(90))
										{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("rot_UL_EIC\n\n");
														#endif
													}break;
			case Sensor_L90:if(1==rotAngle_UL_crossroad()) 
											{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("Sensor_L90_EIC\n\n");
														#endif
													}break;
			case Sensor_R90:if(1==rotAngle_UR_crossroad()) 
											{
														runState->RotangleState=EIC;
														runState->F_LineState=EIC;
														updataState_Reset(controlp,EIC);
														#ifdef BlueTooth_Debug
															u3_printf("Sensor_R90_EIC\n\n");
														#endif
													}break;
			default    :break;	
		}
	}
	else if(runState->RotangleState == STANDBY)
		{
			if(runState->carParkState == EIC)
				runState->RotangleState=NTBE;
		}
}










	
	


