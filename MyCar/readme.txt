2020��5��3
�Ż��Ľ�
1.Parameter_Init���������ȡ���ָ���
2.Test_ExtiKEY,���������ݰ�LED��ʼ���Ƴ��������ȼ���Ϊ��0��2��
3.Test_Uart��ΪInit_Uart_andexit��
4.PTB20�жϼ���Parameter_Init();  �Ѳ�����ʼ���ķ�ʽ�Ƶ��ж�
5.AD_max_min���ˣ�������flash
6.PIT_exitInit���ϣ��޸���ԭ���ĳ�ʼ��
7.PIT_TimeStart��PIT_TimeGet��PIT_Close��������������ִ�г���ʱ���Ƿ����5ms���ٶȲ��������
8.PIT0_IRQHandler���ˣ�PORTB_IRQHandler����
9.�������ܶ�仯

9.5.void PIT_exitInit(int pitx,uint32_t time_ms,uint32_t PreemptPriority, uint32_t SubPriority);
	�����������д����

