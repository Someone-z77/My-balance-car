

int16 Left_pulse,Right_pluse;
float g_Lspeed=0,g_Rspeed=0;//编码器脉冲
float g_RealSpd=0;//测量速度
float g_ExpectSpd=0;//期望速度
float Speed_out;//pid之后的输出

struct // pid 结构体
{
    float error_old;
    float error_new;
    float integral;
    float p;
    float i;
    float d;
    
}PID;