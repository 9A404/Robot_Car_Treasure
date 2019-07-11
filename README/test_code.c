/*************本文件的代码均为测试用图*****************/

/*2017-7-10*/
/*测试舵机用图：
				sgAngleControl(HEAD,L_90);
				delay_ms(500);
				sgAngleControl(HEAD,R_90);
				delay_ms(500);
*/

/*

if(sampingStatus() == 1)
			{
				//array_u3printf(glsensor_ad_value);//串口3输出模拟量
				//arrayPrintf(glsensor_ad_value,12); //串口1输出模拟量
				glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  //将模拟量转化成数字量
				//u3_printf("%d\r\n",sensorDigitalRank(glsensor_dig_value));
				u3_printf("%d \r\n",glsensor_dig_value);//串口3输出数字量
				//sensorBit_u3printf(glsensor_dig_value);//串口3按位输出数字量
				
				//sensorBitPrintf(glsensor_dig_value);	//串口1按位输出数字量																										//将数字量按位输出

				//dSpeed=incrementalPIDcalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));//增量式PID输出
				dSpeed=positionPIDCalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));   //位置式PID输出
				//printf("dSpedd:%d \r\n ",dSpeed);
				//printf("%f  ",sensorPID.setVaule);
				//printf("%f  ",sensorPID.kp);
				 //incrementalSpeedOut(&motorSpeed,dSpeed);	//在当前的速度上叠加速度
				 positionSpeedOut(motorSpeed.leftSpeed,motorSpeed.rightSpeed,dSpeed);
				 //u3_printf(" %d ds:%d left:%d right:%d \r\n",sensorDigitalRank(glsensor_dig_value),dSpeed,motorSpeed.leftSpeed,motorSpeed.rightSpeed);
				//u3_printf("ds:%d\r\n",dSpeed);
				//printf("left:%d \r\n",motorSpeed.leftSpeed);
				//printf("right:%d \r\n",motorSpeed.rightSpeed);
				
				//printf("digital:%d ",glsensor_dig_value );
				//printf("\r\n");
			}
*/





//					speedAdjustment(0,0);
//					Lcd_Clear(WHITE);
//					while(runMethod[i]!=0)
//					{
//						sprintf(buff,"%d",runMethod[i]);
//						Gui_DrawFont_GBK16(0+20*j,40+20*k,BLUE,WHITE,buff);
//						i++;
//						if(j<6)
//							j++;
//						else 
//						j=0;
//						if(j==0)
//							k++;
//					}
//					while(1)
//					{
//						keyFlag = keyScan(0);
//						if(keyFlag==KEY0_UP) break;
//					}



//	/*第一次换跑法路线(如果第二个宝物不在47号平台换路线)*/
//			 if(0==flag_1)
//			 {
//				 /* 如果第一个宝物在7号平台，所在的平台扫码结果是37，换runMethodTableTreasure里面的0号路线 */
//				 if(controlp->curNode==7&&37==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(0,0,BLUE,WHITE,1);
//					//rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,0,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=1;
//				}
//				/* 如果第一个宝物在12号平台，所在的平台扫码结果是37，，换runMethodTableTreasure里面的1号路线 */
//				 else if(controlp->curNode==12&&37==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(30,0,BLUE,WHITE,2);
//					//rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,1,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=1;
//				}
//				/* 如果在第一个宝物所在的平台扫码结果是47，暂时不换跑法路线 */
//				else if(47==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(60,0,BLUE,WHITE,3);
//					flag_1=2;
//				}
//			}
//			 /*如果第二个宝物在37号平台，第二次换跑法路线(根据宝物所在平台换路线)*/
//			 else if(1 == flag_1)
//			 {
//				 /* 如果第二个宝物所在的平台扫码结果是24，换runMethodTableTreasure里面的2号路线*/
//				 if(24==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(90,0,BLUE,WHITE,4);
//				//	rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,2,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=0;
//				}
//				/* 如果第二个宝物所在的平台扫码结果是27，换runMethodTableTreasure里面的3号路线*/
//				else if(27==QR_code_u3_printf(&glHello_control)) 
//				{
//						Gui_DrawFont_Num32(0,40,BLUE,WHITE,5);
//				//	rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,3,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=0;
//				}
//			}
//			/*如果第二个宝物在47号平台，第二次换跑法路线(根据宝物所在平台换路线)*/
//			 else if(2 == flag_1)
//			 {
//				 /* 如果第二个宝物所在的平台扫码结果是24，换runMethodTableTreasure里面的4号路线*/
//				 if(24==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(30,40,BLUE,WHITE,6);
//				//	rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,4,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=0;
//				}
//				/* 如果第二个宝物所在的平台扫码结果是27，换runMethodTableTreasure里面的5号路线*/
//				else if(27==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(60,40,BLUE,WHITE,7);
//				//	rotAngle_Left(180);             //由于在下面直接清空控制状态，在主函数不会执行转弯任务，故在此转弯
//					runMethodUpdate(runMethod,5,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //初始化控制台
//					runStateInit(&glrunState,&glHello_control);		//根据控制台起始路段初始化运行状态
//					flag_1=0;
//				}
//			}
