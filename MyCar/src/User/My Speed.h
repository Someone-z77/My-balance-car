


void  Get_speed();
void  Speed_PID();

typedef struct  PID_parameter // pid ½á¹¹Ìå
{
    float error_old;
    float error_new;
    float integral;
    float p;
    float i;
    float d;
    
}Speed_pid;

extern Speed_pid  PID_R;
extern Speed_pid  PID_L;