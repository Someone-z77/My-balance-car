

int16 Left_pulse,Right_pluse;
float g_Lspeed=0,g_Rspeed=0;//����������
float g_RealSpd=0;//�����ٶ�
float g_ExpectSpd=0;//�����ٶ�
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