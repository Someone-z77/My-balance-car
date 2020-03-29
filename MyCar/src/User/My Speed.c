#include "include.h" 


int16 Left_pulse,Right_pluse;
float g_Lspeed=0,g_Rspeed=0;//����������
float g_RealSpd=0;//�����ٶ�
float g_ExpectSpd=0;//�����ٶ�   �ǵó�ʼ��
float Speed_out;//pid֮������

struct // pid �ṹ��
{
    float error_old;
    float error_new;
    float integral;
    float p;
    float i;
    float d;
    
}PID;



/*------------------------------------------------------*/  
int16  read_CNT_R()//������Ҫȷ��һ�����ұ�������Ӧ�Ĺ�jio
{
    short val;   
    val = FTM_CNT_REG(FTM1);    
    FTM_CNT_REG(FTM1) = 0;    //��ձ�־λ         

    return val;
}
int16 read_CNT_L()
{
    short val;   
    val = FTM_CNT_REG(FTM1);    
    FTM_CNT_REG(FTM1) = 0;    //��ձ�־λ         

    return val;
}
/*---------------------------------------------------------*/
void Get_speed()
{
     Left_pulse = read_CNT_L();
     Right_pluse = read_CNT_R();
     
     //����һ��СС���˲�
     g_Lspeed = 0.3*Left_pulse +0.7*g_Lspeed;
     g_Rspeed = 0.3*Right_pluse  +0.7*g_Rspeed;
     
     //�������Ǽ����ٶ�,Ҳ��һ��СС���˲�
     g_RealSpd=0.1*g_RealSpd+0.3*(g_Lspeed+g_Rspeed)*0.5;//���������һϵ�е���������
       
}
void Speed_PID()
{
     //
     PID.error_old = PID.error_new;
     PID.error_new =  g_ExpectSpd-g_RealSpd;
     PID.integral+=PID.error_new;
     
     Speed_out= PID.p*PID.error_new+PID.i*PID.integral+PID.d*(PID.error_new-PID.error_old);
     //���pwm��
}




