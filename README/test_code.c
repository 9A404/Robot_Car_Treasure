/*************���ļ��Ĵ����Ϊ������ͼ*****************/

/*2017-7-10*/
/*���Զ����ͼ��
				sgAngleControl(HEAD,L_90);
				delay_ms(500);
				sgAngleControl(HEAD,R_90);
				delay_ms(500);
*/

/*

if(sampingStatus() == 1)
			{
				//array_u3printf(glsensor_ad_value);//����3���ģ����
				//arrayPrintf(glsensor_ad_value,12); //����1���ģ����
				glsensor_dig_value = sensorAD(glsensor_ad_value,basic_sensorThreshold);  //��ģ����ת����������
				//u3_printf("%d\r\n",sensorDigitalRank(glsensor_dig_value));
				u3_printf("%d \r\n",glsensor_dig_value);//����3���������
				//sensorBit_u3printf(glsensor_dig_value);//����3��λ���������
				
				//sensorBitPrintf(glsensor_dig_value);	//����1��λ���������																										//����������λ���

				//dSpeed=incrementalPIDcalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));//����ʽPID���
				dSpeed=positionPIDCalc(&sensorPID,sensorDigitalRank(glsensor_dig_value));   //λ��ʽPID���
				//printf("dSpedd:%d \r\n ",dSpeed);
				//printf("%f  ",sensorPID.setVaule);
				//printf("%f  ",sensorPID.kp);
				 //incrementalSpeedOut(&motorSpeed,dSpeed);	//�ڵ�ǰ���ٶ��ϵ����ٶ�
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



//	/*��һ�λ��ܷ�·��(����ڶ������ﲻ��47��ƽ̨��·��)*/
//			 if(0==flag_1)
//			 {
//				 /* �����һ��������7��ƽ̨�����ڵ�ƽ̨ɨ������37����runMethodTableTreasure�����0��·�� */
//				 if(controlp->curNode==7&&37==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(0,0,BLUE,WHITE,1);
//					//rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,0,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=1;
//				}
//				/* �����һ��������12��ƽ̨�����ڵ�ƽ̨ɨ������37������runMethodTableTreasure�����1��·�� */
//				 else if(controlp->curNode==12&&37==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(30,0,BLUE,WHITE,2);
//					//rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,1,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=1;
//				}
//				/* ����ڵ�һ���������ڵ�ƽ̨ɨ������47����ʱ�����ܷ�·�� */
//				else if(47==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(60,0,BLUE,WHITE,3);
//					flag_1=2;
//				}
//			}
//			 /*����ڶ���������37��ƽ̨���ڶ��λ��ܷ�·��(���ݱ�������ƽ̨��·��)*/
//			 else if(1 == flag_1)
//			 {
//				 /* ����ڶ����������ڵ�ƽ̨ɨ������24����runMethodTableTreasure�����2��·��*/
//				 if(24==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(90,0,BLUE,WHITE,4);
//				//	rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,2,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=0;
//				}
//				/* ����ڶ����������ڵ�ƽ̨ɨ������27����runMethodTableTreasure�����3��·��*/
//				else if(27==QR_code_u3_printf(&glHello_control)) 
//				{
//						Gui_DrawFont_Num32(0,40,BLUE,WHITE,5);
//				//	rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,3,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=0;
//				}
//			}
//			/*����ڶ���������47��ƽ̨���ڶ��λ��ܷ�·��(���ݱ�������ƽ̨��·��)*/
//			 else if(2 == flag_1)
//			 {
//				 /* ����ڶ����������ڵ�ƽ̨ɨ������24����runMethodTableTreasure�����4��·��*/
//				 if(24==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(30,40,BLUE,WHITE,6);
//				//	rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,4,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=0;
//				}
//				/* ����ڶ����������ڵ�ƽ̨ɨ������27����runMethodTableTreasure�����5��·��*/
//				else if(27==QR_code_u3_printf(&glHello_control)) 
//				{
//					Gui_DrawFont_Num32(60,40,BLUE,WHITE,7);
//				//	rotAngle_Left(180);             //����������ֱ����տ���״̬��������������ִ��ת�����񣬹��ڴ�ת��
//					runMethodUpdate(runMethod,5,runMethodTableTreasure); 
//					Control_Init(&glHello_control,runMethod);     //��ʼ������̨
//					runStateInit(&glrunState,&glHello_control);		//���ݿ���̨��ʼ·�γ�ʼ������״̬
//					flag_1=0;
//				}
//			}
