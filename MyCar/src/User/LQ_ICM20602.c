
#include "include.h"
#include "LQ_ICM20602.h"

Angle_Sensor Attitude_data;             //��̬�ṹ��
Angle_Sensor Attitude_offset;           //��Ư�ṹ��
#ifdef LQ_TFT1_8
void Test_ICM20602(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    UART_Init(UART4, 115200);
    char  txt[30];
	short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ���� 
    TFTSPI_P8X16Str(2,0,"LQ ICM20602 Test",u16RED,u16BLUE);
    printf("\r\nLQ ICM20602 Test");
    if(ICM20602_Init())
    {
        TFTSPI_P8X16Str(2,0,"ICM20602 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
        sprintf((char*)txt,"ax:%06d",aacx);
        TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"ay:%06d",aacy);
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"az:%06d",aacz);
        TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gx:%06d",gyrox);
        TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gy:%06d",gyroy);
        TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gz:%06d",gyroz);
        TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLUE);

        printf("\r\nAX: %d  ",aacx); 
        printf("\r\nAY: %d  ",aacy);
        printf("\r\nAZ: %d  ",aacz); 
        printf("\r\nGX: %d  ",gyrox);
        printf("\r\nGY: %d  ",gyroy); 
        printf("\r\nGZ: %d  ",gyroz);
        delayms(100);
        printf("*********************");
    }
    
}
#endif


#ifdef LQ_OLED
void Test_ICM20602(void)
{
    char  txt[30];
	  float ax,ay,az,gx,gy,gz;
          float gyrox_offset,gyroy_offset,gyroz_offset;
    UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
    OLED_P8x16Str(15,0,"ICM20602 Test"); 
    printf("\r\nLQ ICM20602 Test");
    
    if(ICM20602_Init())
    {
    
        OLED_P8x16Str(15,2,"ICM20602 Test Fail");
        while(1);
    }
    
        
    while(1)
    {
      
           
        ICM20602_Attitude_Read();
        
        sprintf((char *)txt,"%.3f",Attitude_data.acc_x);
        printf("\r\nx_acc: %.3f ",Attitude_data.acc_x);

        printf("\r\nx_gyro: %.3f ",Attitude_data.gyro_x);
        printf("\r\nx_gyro: %.3f ",Attitude_offset.gyro_x);
        printf("\r\nx_gyro: %.3f ",Attitude_data.gyro_x-Attitude_offset.gyro_x);
        
        vcan_sendware(txt);
        delayms(100);
        printf("\n*********************\n");
        
    }
    
}
#endif


uint8_t ICM20602_Init(void)
{
    uint8_t res;
    SPI_Init(SPI1, SPI_PCS1, MASTER, 1, 10);            //ICM20602 ֧��10M SPI
    delayms(100);
    res=ICM_Read_Byte(WHO_AM_I);                        //��ȡICM20602��ID
    if(res!=ICM20602_ID)                                 //����ID��ȷ
    {
        printf("ID=%#X\r\n",res);
        printf("ICM20602 is fail!\n");
    }
    else  printf("ICM20602 is OK!\n");
    res = 0;
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//��λ
    delayms(100);  //��ʱ100ms
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//����
    delayms(100);  //��ʱ100ms

    ICM_Set_Gyro_Fsr(3);			       //�����Ǵ�����,��2000dps   
    ICM_Set_Accel_Fsr(3);				   //���ٶȴ�����,��16g
    
    ICM_Write_Byte(ICM_SAMPLE_RATE_REG,0x07);//���ò�����
    ICM_Write_Byte(ICM_CFG_REG,0x02);//��ͨ�˲�
    ICM_Write_Byte(ACCEL_CONFIG_2,0x18);//���ٶȸ�ͨ�˲�
      
    //ICM_Set_Rate(1000);					   //���ò�����1000Hz
    //ICM_Write_Byte(ICM_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //�ر������ж�
    ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����

    delayms(100);
    Gyro_offset();//��������Ư
    return 0;
}
/*-------------------------------------------------*/
void ICM_Set_Gyro_Fsr(uint8_t fsr)//���������������̷�Χ
{
	ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);  
         // fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
}

/*-------------------------------------------------*/
void ICM_Set_Accel_Fsr(uint8_t fsr)//���ü��ٶȴ����������̷�Χ 
{
	ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);
        //fsr:0,��2g;1,��4g;2,��8g;3,��16g
}

/*-------------------------------------------------*/
void ICM_Set_LPF(uint16_t lpf)//�������ֵ�ͨ�˲���  
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	ICM_Write_Byte(ICM_CFG_REG,data);
}

/*-------------------------------------------------*/
void ICM_Set_Rate(uint16_t rate)//���ò�����
{
	//rate:4~1000(Hz)
         uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	ICM_Write_Byte(ICM_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	ICM_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}


/*�õ�������ֵ(ԭʼֵ)
  gx,gy,gz:������x,y,z���ԭʼ����(������)*/

void ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[7]; 
	ICM_Read_Len(ICM_GYRO_XOUTH_REG,6,buf);
    
    *gx=((uint16_t)buf[1]<<8)|buf[2];  
    *gy=((uint16_t)buf[3]<<8)|buf[4];  
    *gz=((uint16_t)buf[5]<<8)|buf[6];
    
}

/*�õ����ٶ�ֵ(ԭʼֵ)*/

void ICM_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[7];  
	ICM_Read_Len(ICM_ACCEL_XOUTH_REG,6,buf);
    
    *ax=((uint16_t)buf[1]<<8)|buf[2];  
    *ay=((uint16_t)buf[3]<<8)|buf[4];  
    *az=((uint16_t)buf[5]<<8)|buf[6];
    
}

/*�õ��Ӽ�ֵ�����ٶ�ֵ(ԭʼֵ)*/

void ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
    uint8_t buf[15];  
	ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);
    
    *ax=((uint16_t)buf[1]<<8)|buf[2];  
    *ay=((uint16_t)buf[3]<<8)|buf[4];  
    *az=((uint16_t)buf[5]<<8)|buf[6];
    *gx=((uint16_t)buf[9]<<8)|buf[10];  
    *gy=((uint16_t)buf[11]<<8)|buf[12];  
    *gz=((uint16_t)buf[13]<<8)|buf[14];
	
}

void ICM20602_Attitude_Read(void)
{
    short aacx,aacy,aacz;	        //���ٶ�ԭʼ����
    short gyrox,gyroy,gyroz;        //������ԭʼ����
    ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);

    Attitude_data.acc_x = (float)aacx/2048;    //  ��λg(9.8m/s^2)
    Attitude_data.acc_y = (float)aacy/2048;
    Attitude_data.acc_z = (float)aacz/2048;
  
    Attitude_data.gyro_x= (float)gyrox/16.40;       // ��λ ��/s
    Attitude_data.gyro_y = (float)gyroy/16.40;
    Attitude_data.gyro_z = (float)gyroz/16.40;

}

void Gyro_offset(void)//��������Ư
{
    uint16  count=0;
    ICM20602_Attitude_Read();
    while(count<1000)
    {
      Attitude_offset.acc_x+=Attitude_data.acc_x;
      Attitude_offset.acc_y+=Attitude_data.acc_y;
      Attitude_offset.acc_z+=Attitude_data.acc_z;
      Attitude_offset.gyro_x+=Attitude_data.gyro_x;
      Attitude_offset.gyro_y+=Attitude_data.gyro_y;
      Attitude_offset.gyro_z+=Attitude_data.gyro_z;
      count++;
    }
    Attitude_offset.acc_x/=1000;
    Attitude_offset.acc_x/=1000;
    Attitude_offset.acc_x/=1000;
    Attitude_offset.gyro_x/=1000;
    Attitude_offset.gyro_y/=1000;
    Attitude_offset.gyro_z/=1000;
    
}

/**
  * @brief    SPI ������
  *
  * @param    reg   ���ļĴ�����ַ
  * @param    len   ����
  * @param    buf   ��Ŷ������� �ĵ�ַ
  *
  * @return   
  *
  * @note     
  * 
  * @example  
  *
  * @date     2019/5/27 ����һ
  */

void ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{   
    buf[0] = reg | 0x80;
    /* д��Ҫ���ļĴ�����ַ */
    SPI_RadeWrite(SPI1, SPI_PCS1, buf, buf, len + 1);

}


/**
  * @brief    SPI д
  *
  * @param    reg   д�ļĴ�����ַ
  * @param    value Ҫд��ֵ
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 ����һ
  */
void ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //�ȷ��ͼĴ���
    buff[1] = value;        //�ٷ�������

    SPI_RadeWrite(SPI1, SPI_PCS1, buff, buff, 2); //����buff�����ݣ����ɼ��� buff��
}

/**
  * @brief    SPI ��
  *
  * @param    reg   ���ļĴ�����ַ
  *
  * @return   ����������
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 ����һ
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8 buff[2];
    buff[0] = reg | 0x80;          //�ȷ��ͼĴ���

    SPI_RadeWrite(SPI1, SPI_PCS1, buff, buff,  2);
    

    return buff[1];
}
