#ifndef __LQ_ICM20602_H
#define __LQ_ICM20602_H




#define MPU6050_ADDR  0xD0  //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
#define MPU6050_ID	  0x68	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define ICM20602_ID	  0x12	//IIC��ַ�Ĵ���(Ĭ����ֵ0x12��ֻ��)
//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
//MPU6500���ڲ��Ĵ���
#define ICM_SELF_TESTX_REG		0X0D	//�Լ�Ĵ���X
#define ICM_SELF_TESTY_REG		0X0E	//�Լ�Ĵ���Y
#define ICM_SELF_TESTZ_REG		0X0F	//�Լ�Ĵ���Z
#define ICM_SELF_TESTA_REG		0X10	//�Լ�Ĵ���A
#define ICM_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define ICM_CFG_REG				0X1A	//���üĴ���
#define ICM_GYRO_CFG_REG		0X1B	//���������üĴ���
#define ICM_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define	ACCEL_CONFIG_2           0x1D
#define ICM_MOTION_DET_REG		0X1F	//�˶���ֵⷧ���üĴ���
#define ICM_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���

#define ICM_I2CMST_STA_REG		0X36	//IIC����״̬�Ĵ���
#define ICM_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define ICM_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define ICM_INT_STA_REG			0X3A	//�ж�״̬�Ĵ���

#define ICM_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define ICM_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define ICM_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define ICM_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define ICM_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define ICM_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define ICM_TEMP_OUTH_REG		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define ICM_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

#define ICM_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define ICM_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define ICM_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define ICM_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define ICM_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define ICM_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���

#define ICM_I2CSLV0_DO_REG		0X63	//IIC�ӻ�0���ݼĴ���
#define ICM_I2CSLV1_DO_REG		0X64	//IIC�ӻ�1���ݼĴ���
#define ICM_I2CSLV2_DO_REG		0X65	//IIC�ӻ�2���ݼĴ���
#define ICM_I2CSLV3_DO_REG		0X66	//IIC�ӻ�3���ݼĴ���

#define ICM_I2CMST_DELAY_REG	0X67	//IIC������ʱ����Ĵ���
#define ICM_SIGPATH_RST_REG		0X68	//�ź�ͨ����λ�Ĵ���
#define ICM_MDETECT_CTRL_REG	0X69	//�˶������ƼĴ���
#define ICM_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define ICM_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define ICM_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define ICM_FIFO_CNTH_REG		0X72	//FIFO�����Ĵ����߰�λ
#define ICM_FIFO_CNTL_REG		0X73	//FIFO�����Ĵ����Ͱ�λ
#define ICM_FIFO_RW_REG			0X74	//FIFO��д�Ĵ���
#define WHO_AM_I		        0X75	//����ID�Ĵ���

void Test_ICM20602(void);
uint8_t ICM_Read_Byte(uint8_t reg);
void  ICM_Write_Byte(uint8_t reg,uint8_t value);
void  ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf);
void  ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz);
void  ICM_Get_Accelerometer(short *ax,short *ay,short *az);
void  ICM_Get_Gyroscope(short *gx,short *gy,short *gz);
short ICM_Get_Temperature(void);
void  ICM_Set_Rate(uint16_t rate);
void  ICM_Set_LPF(uint16_t lpf);
void  ICM_Set_Accel_Fsr(uint8_t fsr);
void  ICM_Set_Gyro_Fsr(uint8_t fsr);
void ICM20602_Attitude_Read(void);
void Gyro_offset(void);//��������Ư

uint8_t ICM20602_Init(void);

typedef struct Angle_sensor_structure
{
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float acc_x;
  float acc_y;
  float acc_z;

}Angle_Sensor;
extern Angle_Sensor  Attitude_data;
extern Angle_Sensor Attitude_offset;
#endif