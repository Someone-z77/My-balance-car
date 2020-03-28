#include "include.h"
#include "MK60_SPI.h"

SPI_MemMapPtr SPIN[3] = {SPI0_BASE_PTR, SPI1_BASE_PTR, SPI2_BASE_PTR}; //定义三个指针数组保存 SPIx 的地址



#define SPI_TX_WAIT(SPIn)     while(  ( SPI_SR_REG(SPIn) & SPI_SR_TXRXS_MASK ) == 1 ) //等待发送 完成
#define SPI_RX_WAIT(SPIn)     while(  ( SPI_SR_REG(SPIn) & SPI_SR_RFDF_MASK ) == 0 )  //等待发送 FIFO为非空
#define SPI_EOQF_WAIT(SPIn)   while(  (SPI_SR_REG(SPIn) & SPI_SR_EOQF_MASK ) == 0 )   //等待传输完成


/**
  * @brief    SPI初始化
  *
 *  @param      spin            SPI模块(SPI0、SPI1、SPI2)
 *  @param      SPIn_PCSn_e     片选管脚编号
 *  @param      master          片选管脚编号
 *  @param      mode            0: CLK空闲时刻为高电平 在第一个CLK跳边沿（下降沿）捕获数据
 *  @param      mode            1: CLK空闲时刻为高电平 在第二个CLK跳边沿（上升沿）捕获数据
 *  @param      mode            2: CLK空闲时刻为低电平 在第一个CLK跳边沿（上升沿）捕获数据
 *  @param      mode            3: CLK空闲时刻为低电平 在第二个CLK跳边沿（下降沿）捕获数据
 *  @param      SPI_CFG         SPI主从机模式选择 
 *  @param      baud            baud MHz
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 星期一
  */
uint32 SPI_Init(SPI_Type *spin, SPI_PCSn_e pcs, SPI_CFG master,uint8_t mode, uint32 baud)
{
    uint8  br,pbr;
    uint32 clk = bus_clk*1000000/baud;
    uint32 Scaler[] = {2,4,6,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
    uint32  Prescaler[] = {2,3,5,7};
    uint32 fit_clk,fit_br=0,fit_pbr,min_diff =~0,diff;
    uint32 tmp;
    uint32_t temp = 0;
    //计算CS到第一个SCK的时间
    uint8 pcssck,cssck,fit_pcssck,fit_cssck;

    //使能SPI模块时钟，配置SPI引脚功能
    if(spin == SPI0)
    {

        SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;

        //进行管脚复用
        PORTX[PTX(SPI0_SCK_PIN)]->PCR[PTn(SPI0_SCK_PIN)] |= ALT2;
        PORTX[PTX(SPI0_SOUT_PIN)]->PCR[PTn(SPI0_SOUT_PIN)] |= ALT2;
        PORTX[PTX(SPI0_SIN_PIN)]->PCR[PTn(SPI0_SIN_PIN)] |= ALT2;

        if(pcs & SPI_PCS0)
            PORTX[PTX(SPI0_PCS0_PIN)]->PCR[PTn(SPI0_PCS0_PIN)] |= ALT2;

        if(pcs & SPI_PCS1)
            PORTX[PTX(SPI0_PCS1_PIN)]->PCR[PTn(SPI0_PCS1_PIN)] |= ALT2;

        if(pcs & SPI_PCS2)
            PORTX[PTX(SPI0_PCS2_PIN)]->PCR[PTn(SPI0_PCS2_PIN)] |= ALT2;

        if(pcs & SPI_PCS3)
            PORTX[PTX(SPI0_PCS3_PIN)]->PCR[PTn(SPI0_PCS3_PIN)] |= ALT2;

        if(pcs & SPI_PCS4)
            PORTX[PTX(SPI0_PCS4_PIN)]->PCR[PTn(SPI0_PCS4_PIN)] |= ALT2;

        if(pcs & SPI_PCS5)
            PORTX[PTX(SPI0_PCS5_PIN)]->PCR[PTn(SPI0_PCS5_PIN)] |= ALT2;
    }
    else if(spin == SPI1)
    {
        SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;
        PORTX[PTX(SPI1_SCK_PIN)]->PCR[PTn(SPI1_SCK_PIN)] |= ALT2;
        PORTX[PTX(SPI1_SOUT_PIN)]->PCR[PTn(SPI1_SOUT_PIN)] |= ALT2;
        PORTX[PTX(SPI1_SIN_PIN)]->PCR[PTn(SPI1_SIN_PIN)] |= ALT2;

        if(pcs & SPI_PCS0)
            PORTX[PTX(SPI1_PCS0_PIN)]->PCR[PTn(SPI1_PCS0_PIN)] |= ALT2;

        if(pcs & SPI_PCS1)
            PORTX[PTX(SPI1_PCS1_PIN)]->PCR[PTn(SPI1_PCS1_PIN)] |= ALT2;

        if(pcs & SPI_PCS2)
            PORTX[PTX(SPI1_PCS2_PIN)]->PCR[PTn(SPI1_PCS2_PIN)] |= ALT2;

        if(pcs & SPI_PCS3)
            PORTX[PTX(SPI1_PCS3_PIN)]->PCR[PTn(SPI1_PCS3_PIN)] |= ALT2;

    }
    else if(spin == SPI2)
    {
        SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;

        PORTX[PTX(SPI2_SCK_PIN)]->PCR[PTn(SPI2_SCK_PIN)] |= ALT2;
        PORTX[PTX(SPI2_SOUT_PIN)]->PCR[PTn(SPI2_SOUT_PIN)] |= ALT2;
        PORTX[PTX(SPI2_SIN_PIN)]->PCR[PTn(SPI2_SIN_PIN)] |= ALT2;

        if(pcs & SPI_PCS0)
            PORTX[PTX(SPI2_PCS0_PIN)]->PCR[PTn(SPI2_PCS0_PIN)] |= ALT2;

        if(pcs & SPI_PCS1)
            PORTX[PTX(SPI2_PCS1_PIN)]->PCR[PTn(SPI2_PCS1_PIN)] |= ALT2;
    }
    else
    {
        //传递进来的 spi 模块有误，直接判断断言失败
//        ASSERT(0);
    }

    SPI_MCR_REG(spin) = ( 0
                                | SPI_MCR_CLR_TXF_MASK     //清空 Tx FIFO 计数器
                                | SPI_MCR_CLR_RXF_MASK     //清空 Rx FIFO 计数器
                                | SPI_MCR_HALT_MASK        //停止SPI传输
                              );

    /*************  清标志位  ***************/
    SPI_SR_REG(spin) = (0
                              | SPI_SR_EOQF_MASK    //发送队列空了，发送完毕
                              | SPI_SR_TFUF_MASK    //传输FIFO下溢标志位，SPI为从机模式，Tx FIFO为空，而外部SPI主机模式启动传输，标志位就会置1，写1清0
                              | SPI_SR_TFFF_MASK    //传输FIFO满标志位。 写1或者DMA控制器发现传输FIFO满了就会清0。 0表示Tx FIFO满了
                              | SPI_SR_RFOF_MASK    //接收FIFO溢出标志位。
                              | SPI_SR_RFDF_MASK    //接收FIFO损耗标志位，写1或者DMA控制器发现传输FIFO空了就会清0。0表示Rx FIFO空
                             );


    //根据主从机模式设置工作模式。MCU提供最大主机频率是1/2主频，最大从机频率是1/4主频
    if(master == MASTER)
    {
        SPI_MCR_REG(spin) =  (0
                                    |  SPI_MCR_MSTR_MASK        //Master,主机模式
                                    |  SPI_MCR_PCSIS(pcs)
                                    |  SPI_MCR_PCSIS_MASK
                                   );


        for(br = 0;br < 0x10;br++)
        {
            for(pbr = 0;pbr < 4;pbr++)
            {
                tmp = Scaler[br] * Prescaler[pbr];
                diff = abs(tmp - baud);
                if((diff == 0) || (min_diff > diff))
                {
                    //记住 最佳配置
                    min_diff = diff;
                    fit_br = br;
                    fit_pbr = pbr;
                    if(diff == 0)     
                        goto SPI_CLK_EXIT;
                    

                }

            }
        }

SPI_CLK_EXIT:
        fit_clk =  bus_clk *1000000 /(Scaler[fit_br] * Prescaler[fit_pbr]);

        //需要算一下 CS 到 CLK 的时间（波特率的半周期）,满足条件： (1<<(CSSCK + 1 ))*( 2*PCSSCK+1) = fclk /(2*  baud)
        clk =  bus_clk*1000000/fit_clk/2;
        min_diff = ~0;
        fit_cssck = 0x0F;
        fit_pcssck = 3;
        for(cssck = 0;cssck<=0x0F;cssck++)
        {
            tmp = 1<<(cssck+1) ;
            pcssck = (clk/tmp-1)/2;
            if(pcssck>3)continue;       //不能超过 3
            tmp = tmp * (2*pcssck+1);
            diff = abs(tmp-clk);
            if(min_diff > diff)
            {
                //记住 最佳配置
                min_diff = diff;
                fit_cssck = cssck;
                fit_pcssck = pcssck;

                    
                goto SPI_CSSCK_EXIT;

            }
        }

SPI_CSSCK_EXIT:

       
       temp =    (0
                           //| SPI_CTAR_DBR_MASK    //双波特率 ，假设 DBR=1，CPHA=1，PBR=00，得SCK Duty Cycle 为 50/50
                           
                           //| SPI_CTAR_CPHA_MASK   //数据在SCK上升沿改变（输出），在下降沿被捕捉（输入读取）。如果是0，则反之。  w25x16在上升沿读取数据；NRF24L01在上升沿读取数据
                           | SPI_CTAR_PBR(fit_pbr)        //波特率分频器 ，0~3 对应的分频值Prescaler为 2、3、5、7

                           | SPI_CTAR_PDT(0x00)     //延时因子为 PDT*2+1 ，这里PDT为3，即延时因子为7。PDT为2bit
                           | SPI_CTAR_BR(fit_br)         //波特率计数器值 ,当BR<=3,分频Scaler 为 2*（BR+1） ，当BR>=3，分频Scaler 为 2^BR  。BR为4bit
                           //SCK 波特率 = (Bus clk/Prescaler) x [(1+DBR)/Scaler ]          fSYS 为 Bus clock
                           //              50M / 2         x [ 1  /  2  ] = 25M   这里以最大的来算
                           
                           //| SPI_CTAR_CPOL_MASK   //时钟极性，1表示 SCK 不活跃状态为高电平,   NRF24L01 不活跃为低电平
                           | SPI_CTAR_FMSZ(0x07)    //每帧传输 7bit+1 ，即8bit （FMSZ默认就是8）
                           // | SPI_CTAR_LSBFE_MASK //1为低位在前。

                           // 下面两个参数是调整 CS 信号来了到第一个CLK的时间
                           | SPI_CTAR_CSSCK(fit_cssck)    // x ：0~0x0F
                           | SPI_CTAR_PCSSCK(fit_pcssck)    //设置片选信号有效到时钟第一个边沿出现的延时的预分频值。tcsc延时预分频 2*x+1； x 0~3
                          );
       if((mode & 1))
           temp |= SPI_CTAR_CPHA_MASK;
       if((mode >> 1) == 0)
           temp |= SPI_CTAR_CPOL_MASK;
        SPI_CTAR_REG(spin, 0) = temp;
    }
    else
    {
        //默认从机模式
        SPI_CTAR_SLAVE_REG(spin, 0) = (0
                                             | SPI_CTAR_SLAVE_FMSZ(0x07)
                                             | SPI_CTAR_SLAVE_CPOL_MASK
                                             | SPI_CTAR_SLAVE_CPHA_MASK
                                            );
    }


    SPI_MCR_REG(spin) &= ~SPI_MCR_HALT_MASK;     //启动SPI传输。1为暂停，0为启动

    return fit_clk;

}


/**
  * @brief    SPI 读写函数
  *
  * @param      spin            SPI模块(SPI0、SPI1、SPI2)
  * @param      SPIn_PCSn_e     片选管脚编号
  * @param      modata          发送的数据缓冲区地址(不需要接收则传 NULL)
  * @param      midata          发送数据时接收到的数据的存储地址(不需要接收则传 NULL) 
  * @param      len             读写长度
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/27 星期一
  */
void SPI_RadeWrite(SPI_Type *spin, SPI_PCSn_e pcs, uint8 *modata, uint8 *midata, uint32 len)
{
    uint32 i = 0;
    do
    {
        /*************  清标志位  ***************/
        SPI_SR_REG(spin) = (0
                                  | SPI_SR_EOQF_MASK    //发送队列空了，发送完毕标志
                                  | SPI_SR_TFUF_MASK    //传输FIFO下溢标志位，SPI为从机模式，Tx FIFO为空，而外部SPI主机模式启动传输，标志位就会置1，写1清0
                                  | SPI_SR_TFFF_MASK    //传输FIFO满标志位。 写1或者DMA控制器发现传输FIFO满了就会清0。 0表示Tx FIFO满了
                                  | SPI_SR_RFOF_MASK    //接收FIFO溢出标志位。
                                  | SPI_SR_RFDF_MASK    //接收FIFO损耗标志位，写1或者DMA控制器发现传输FIFO空了就会清0。0表示Rx FIFO空
                                 );


        /************** 清FIFO计数器 **************/
        SPI_MCR_REG(spin)    |=  (0
                                        | SPI_MCR_CLR_TXF_MASK  //写1清 Tx FIFO 计数器
                                        | SPI_MCR_CLR_RXF_MASK  //写1清 Rx FIFO 计数器
                                       );

    }
    while( (SPI_SR_REG(spin) & SPI_SR_RFDF_MASK));            //如果 Rx FIFO 非空，则清FIFO.

    /***************** 发送len-1个数据 *******************/                                                ;
    for(i = 0; i < (len - 1); i++)
    {
        SPI_PUSHR_REG(spin) = (0
                                     | SPI_PUSHR_CTAS(0)             //选择CTAR0寄存器
                                     | SPI_PUSHR_CONT_MASK           //1为 传输期间保持PCSn信号 ，即继续传输数据
                                     | SPI_PUSHR_PCS(pcs)
                                     | SPI_PUSHR_TXDATA(modata[i])     //要传输的数据
                                    );

        while(!(SPI_SR_REG(spin) & SPI_SR_RFDF_MASK));        //RFDF为1，Rx FIFO is not empty.
        if(midata != NULL)
        {
            midata[i] = (uint8)SPI_POPR_REG(spin);                  //保存接收到的数据
        }
        else
        {
            SPI_POPR_REG(spin);
        }
        SPI_SR_REG(spin) |= SPI_SR_RFDF_MASK;
    }

    /***************** 发送最后一个数据 *******************/
    SPI_PUSHR_REG(spin) = (0
                                 | SPI_PUSHR_CTAS(0)                 //选择CTAR0寄存器
                                 | SPI_PUSHR_PCS(pcs)
                                 | SPI_PUSHR_EOQ_MASK                //1为 传输SPI最后的数据
                                 | SPI_PUSHR_TXDATA(modata[i])
                                );

    SPI_EOQF_WAIT(spin);                                            //等待发送完成。(要及时把RX FIFO的东西清掉，不然这里就无限等待)

    while( !(SPI_SR_REG(spin) & SPI_SR_RFDF_MASK));           //RFDF为1，Rx FIFO is not empty.
    if(midata != NULL)
    {
        midata[i] = (uint8)SPI_POPR_REG(spin);                  //保存接收到的数据
    }
    else
    {
        SPI_POPR_REG(spin);
    }
    SPI_SR_REG(spin) |= SPI_SR_RFDF_MASK;                     //写1清空RFDF，标记Rx FIFO 是空的
}


