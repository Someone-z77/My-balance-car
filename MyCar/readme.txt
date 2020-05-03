2020·5·3
优化改进
1.Parameter_Init内容下面读取部分改了
2.Test_ExtiKEY,改名改内容把LED初始化移出，把优先级改为（0，2）
3.Test_Uart改为Init_Uart_andexit名
4.PTB20中断加了Parameter_Init();  把参数初始化的方式移到中断
5.AD_max_min改了，加上了flash
6.PIT_exitInit加上，修改了原来的初始化
7.PIT_TimeStart，PIT_TimeGet，PIT_Close用来计数，看看执行程序时长是否大于5ms（速度采样间隔）
8.PIT0_IRQHandler改了，PORTB_IRQHandler改了
9.主函数很多变化

9.5.void PIT_exitInit(int pitx,uint32_t time_ms,uint32_t PreemptPriority, uint32_t SubPriority);
	里面输入变量写错了

