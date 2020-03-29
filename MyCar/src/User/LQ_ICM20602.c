
#include "include.h"
#include "LQ_ICM20602.h"

Angle_Sensor Attitude_data;             //姿态结构体
Angle_Sensor Attitude_offset;           //零漂结构体
#ifdef LQ_TFT1_8
void Test_ICM20602(void)
{
    TFTSPI_Init(1);                //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    UART_Init(UART4, 115200);
    char  txt[30];
	short aacx,aacy,aacz;	        //加速度传感器原始数据
	short gyrox,gyroy,gyroz;        //陀螺仪原始数据 
    TFTSPI_P8X16Str(2,0,"LQ ICM20602 Test",u16RED,u16BLUE);
    printf("\r\nLQ ICM20602 Test");
    if(ICM20602_Init())
    {
        TFTSPI_P8X16Str(2,0,"ICM20602 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据  
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
    OLED_Init();                  //LCD初始化
    OLED_CLS();                   //LCD清屏
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
    SPI_Init(SPI1, SPI_PCS1, MASTER, 1, 10);            //ICM20602 支持10M SPI
    delayms(100);
    res=ICM_Read_Byte(WHO_AM_I);                        //读取ICM20602的ID
    if(res!=ICM20602_ID)                                 //器件ID正确
    {
        printf("ID=%#X\r\n",res);
        printf("ICM20602 is fail!\n");
    }
    else  printf("ICM20602 is OK!\n");
    res = 0;
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//复位
    delayms(100);  //延时100ms
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//唤醒
    delayms(100);  //延时100ms

    ICM_Set_Gyro_Fsr(3);			       //陀螺仪传感器,±2000dps   
    ICM_Set_Accel_Fsr(3);				   //加速度传感器,±16g
    
    ICM_Write_Byte(ICM_SAMPLE_RATE_REG,0x07);//设置采样率
    ICM_Write_Byte(ICM_CFG_REG,0x02);//低通滤波
    ICM_Write_Byte(ACCEL_CONFIG_2,0x18);//加速度高通滤波
      
    //ICM_Set_Rate(1000);					   //设置采样率1000Hz
    //ICM_Write_Byte(ICM_CFG_REG,0x02);      //设置数字低通滤波器   98hz
    ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //关闭所有中断
    ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C主模式关闭
    ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
    ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作

    delayms(100);
    Gyro_offset();//陀螺仪零漂
    return 0;
}
/*-------------------------------------------------*/
void ICM_Set_Gyro_Fsr(uint8_t fsr)//设置陀螺仪满量程范围
{
	ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);  
         // fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
}

/*-------------------------------------------------*/
void ICM_Set_Accel_Fsr(uint8_t fsr)//设置加速度传感器满量程范围 
{
	ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);
        //fsr:0,±2g;1,±4g;2,±8g;3,±16g
}

/*-------------------------------------------------*/
void ICM_Set_LPF(uint16_t lpf)//设置数字低通滤波器  
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
void ICM_Set_Rate(uint16_t rate)//设置采样率
{
	//rate:4~1000(Hz)
         uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	ICM_Write_Byte(ICM_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
 	ICM_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}


/*得到陀螺仪值(原始值)
  gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)*/

void ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[7]; 
	ICM_Read_Len(ICM_GYRO_XOUTH_REG,6,buf);
    
    *gx=((uint16_t)buf[1]<<8)|buf[2];  
    *gy=((uint16_t)buf[3]<<8)|buf[4];  
    *gz=((uint16_t)buf[5]<<8)|buf[6];
    
}

/*得到加速度值(原始值)*/

void ICM_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[7];  
	ICM_Read_Len(ICM_ACCEL_XOUTH_REG,6,buf);
    
    *ax=((uint16_t)buf[1]<<8)|buf[2];  
    *ay=((uint16_t)buf[3]<<8)|buf[4];  
    *az=((uint16_t)buf[5]<<8)|buf[6];
    
}

/*得到加计值、角速度值(原始值)*/

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
    short aacx,aacy,aacz;	        //加速度原始数据
    short gyrox,gyroy,gyroz;        //陀螺仪原始数据
    ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);

    Attitude_data.acc_x = (float)aacx/2048;    //  单位g(9.8m/s^2)
    Attitude_data.acc_y = (float)aacy/2048;
    Attitude_data.acc_z = (float)aacz/2048;
  
    Attitude_data.gyro_x= (float)gyrox/16.40;       // 单位 °/s
    Attitude_data.gyro_y = (float)gyroy/16.40;
    Attitude_data.gyro_z = (float)gyroz/16.40;

}

void Gyro_offset(void)//陀螺仪零漂
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
  * @brief    SPI 连续读
  *
  * @param    reg   读的寄存器地址
  * @param    len   长度
  * @param    buf   存放读出数据 的地址
  *
  * @return   
  *
  * @note     
  * 
  * @example  
  *
  * @date     2019/5/27 星期一
  */

void ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{   
    buf[0] = reg | 0x80;
    /* 写入要读的寄存器地址 */
    SPI_RadeWrite(SPI1, SPI_PCS1, buf, buf, len + 1);

}


/**
  * @brief    SPI 写
  *
  * @param    reg   写的寄存器地址
  * @param    value 要写的值
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 星期一
  */
void ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //先发送寄存器
    buff[1] = value;        //再发送数据

    SPI_RadeWrite(SPI1, SPI_PCS1, buff, buff, 2); //发送buff里数据，并采集到 buff里
}

/**
  * @brief    SPI 读
  *
  * @param    reg   读的寄存器地址
  *
  * @return   读出的数据
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 星期一
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8 buff[2];
    buff[0] = reg | 0x80;          //先发送寄存器

    SPI_RadeWrite(SPI1, SPI_PCS1, buff, buff,  2);
    

    return buff[1];
}
