#include "include.h"
#include "Uart_DMA.h"

#define UART_DMA_TX_CHANL  10
#define UART_DMA_RX_CHANL  11


edma_handle_t uart4_edma_tx;
edma_handle_t uart4_edma_rx;
uart_edma_handle_t g_uartEdmaHandle;


/*! @brief Error codes for the UART driver. */
enum _uart_status
{
    kStatus_UART_TxBusy = MAKE_STATUS(10, 0),              /*!< Transmitter is busy. */
    kStatus_UART_RxBusy = MAKE_STATUS(10, 1),              /*!< Receiver is busy. */
    kStatus_UART_TxIdle = MAKE_STATUS(10, 2),              /*!< UART transmitter is idle. */
    kStatus_UART_RxIdle = MAKE_STATUS(10, 3),              /*!< UART receiver is idle. */
    kStatus_UART_TxWatermarkTooLarge = MAKE_STATUS(10, 4), /*!< TX FIFO watermark too large  */
    kStatus_UART_RxWatermarkTooLarge = MAKE_STATUS(10, 5), /*!< RX FIFO watermark too large  */
    kStatus_UART_FlagCannotClearManually =
        MAKE_STATUS(10, 6),                                /*!< UART flag can't be manually cleared. */
    kStatus_UART_Error = MAKE_STATUS(10, 7),               /*!< Error happens on UART. */
    kStatus_UART_RxRingBufferOverrun = MAKE_STATUS(10, 8), /*!< UART RX software ring buffer overrun. */
    kStatus_UART_RxHardwareOverrun = MAKE_STATUS(10, 9),   /*!< UART RX receiver overrun. */
    kStatus_UART_NoiseError = MAKE_STATUS(10, 10),         /*!< UART noise error. */
    kStatus_UART_FramingError = MAKE_STATUS(10, 11),       /*!< UART framing error. */
    kStatus_UART_ParityError = MAKE_STATUS(10, 12),        /*!< UART parity error. */
    kStatus_UART_BaudrateNotSupport =
        MAKE_STATUS(10, 13), /*!< Baudrate is not support in current clock source */
};



/* UART EDMA transfer handle. */
enum _uart_edma_tansfer_states
{
    kUART_TxIdle, /* TX idle. */
    kUART_TxBusy, /* TX busy. */
    kUART_RxIdle, /* RX idle. */
    kUART_RxBusy  /* RX busy. */
};
/*<! Structure definition for uart_edma_private_handle_t. The structure is private. */
typedef struct _uart_edma_private_handle
{
    UART_MemMapPtr base;
    uart_edma_handle_t *handle;
} uart_edma_private_handle_t;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*<! Private handle only used for internally. */
static uart_edma_private_handle_t s_edmaPrivateHandle[6];




static void UART_SendEDMACallback(edma_handle_t *handle, void *param, uint8_t transferDone, uint32_t tcds)
{

    uart_edma_private_handle_t *uartPrivateHandle = (uart_edma_private_handle_t *)param;

    /* Avoid the warning for unused variables. */
    handle = handle;
    tcds = tcds;

    if (transferDone)
    {
        UART_TransferAbortSendEDMA(uartPrivateHandle->base, uartPrivateHandle->handle);

        if (uartPrivateHandle->handle->callback)
        {
            uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle, kStatus_UART_TxIdle,
                                                uartPrivateHandle->handle->userData);
        }
    }
}

static void UART_ReceiveEDMACallback(edma_handle_t *handle, void *param, uint8_t transferDone, uint32_t tcds)
{

    uart_edma_private_handle_t *uartPrivateHandle = (uart_edma_private_handle_t *)param;

    /* Avoid warning for unused parameters. */
    handle = handle;
    tcds = tcds;

    if (transferDone)
    {
        /* Disable transfer. */
        UART_TransferAbortReceiveEDMA(uartPrivateHandle->base, uartPrivateHandle->handle);

        if (uartPrivateHandle->handle->callback)
        {
            uartPrivateHandle->handle->callback(uartPrivateHandle->base, uartPrivateHandle->handle, kStatus_UART_RxIdle,
                                                uartPrivateHandle->handle->userData);
        }
    }
}


/**
  * @brief    ���ڻص�����
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/14 ���ڶ�
  */
void UART_UserCallback(UART_MemMapPtr base, uart_edma_handle_t *handle, int status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        car_status.txBufferFull = false;
        car_status.txOnGoing = false;
    }

    if (kStatus_UART_RxIdle == status)
    {
        car_status.rxBufferEmpty = false;
        car_status.rxOnGoing = false;
    }
}





/**
  * @brief    ����4 + DMA����
  *
  * @param    
  *
  * @return   
  *
  * @note     K66�Ĵ���4 ���պͷ��͹���ͬһ��DMA����Դ
  *
  * @example  
  *
  * @date     2019/5/14 ���ڶ�
  */
void Uart4_DMA_Init(void)
{
    UART_Init(UART4, 115200);
    
    /* ����ʱ�� */
    SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
    SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
    
    /* ����DMA����Դ */
    DMAMUX_BASE_PTR->CHCFG[UART_DMA_TX_CHANL] = ((DMAMUX_BASE_PTR->CHCFG[UART_DMA_TX_CHANL] 
                                                 & ~DMAMUX_CHCFG_SOURCE_MASK) 
                                                 | DMAMUX_CHCFG_SOURCE(DMA_UART4)
                                                 | DMAMUX_CHCFG_ENBL_MASK);
    
//    DMAMUX_BASE_PTR->CHCFG[UART_DMA_RX_CHANL] = ((DMAMUX_BASE_PTR->CHCFG[UART_DMA_RX_CHANL] 
//                                                 & ~DMAMUX_CHCFG_SOURCE_MASK) 
//                                                 | DMAMUX_CHCFG_SOURCE(DMA_UART4)
//                                                 | DMAMUX_CHCFG_ENBL_MASK);
    
    
    
    /* ���� ���� DMA������ */
    EDMA_CreateHandle(&uart4_edma_tx, DMA_BASE_PTR, UART_DMA_TX_CHANL);
//    EDMA_CreateHandle(&uart4_edma_rx, DMA_BASE_PTR, UART_DMA_RX_CHANL);

    
    /* ���ȼ����� ��ռ���ȼ�2  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority((IRQn_Type)UART_DMA_TX_CHANL,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
    NVIC_EnableIRQ((IRQn_Type)UART_DMA_TX_CHANL);		   //ʹ��DMA�ж� 
    
//    /* ���ȼ����� ��ռ���ȼ�2  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
//    NVIC_SetPriority((IRQn_Type)UART_DMA_RX_CHANL,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
//    NVIC_EnableIRQ((IRQn_Type)UART_DMA_RX_CHANL);		   //ʹ��DMA�ж�    
//    
    /* ���� ���� DMA��� */
    s_edmaPrivateHandle[4].base = UART4_BASE_PTR;
    s_edmaPrivateHandle[4].handle = &g_uartEdmaHandle;
    
    
    
    g_uartEdmaHandle.rxState = kUART_RxIdle;
    g_uartEdmaHandle.txState = kUART_TxIdle;
    
    g_uartEdmaHandle.rxEdmaHandle = &uart4_edma_rx;
    g_uartEdmaHandle.txEdmaHandle = &uart4_edma_tx;
    
    g_uartEdmaHandle.callback = UART_UserCallback;
    
    
    if (&uart4_edma_rx)
    {
        UART4_BASE_PTR->RWFIFO = 1U;
    }
    /* Configure TX. */
    if (&uart4_edma_tx)
    {
        EDMA_SetCallback(g_uartEdmaHandle.txEdmaHandle, UART_SendEDMACallback, &s_edmaPrivateHandle[4]);
    }

    /* Configure RX. */
    if (&uart4_edma_rx)
    {
        EDMA_SetCallback(g_uartEdmaHandle.rxEdmaHandle, UART_ReceiveEDMACallback, &s_edmaPrivateHandle[4]);
    }
    
}



int UART_SendEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle, uart_transfer_t *xfer)
{


    edma_transfer_config_t xferConfig;
    int status;

    /* If previous TX not finished. */
    if (kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txState = kUART_TxBusy;
        handle->txDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        EDMA_PrepareTransfer(&xferConfig, xfer->data, sizeof(uint8_t), (void *)UART_GetDataRegisterAddress(base),
                             sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, kEDMA_MemoryToPeripheral);

        /* Store the initially configured eDMA minor byte transfer count into the UART handle */
        handle->nbytes = sizeof(uint8_t);

        /* Submit transfer. */
        EDMA_SubmitTransfer(handle->txEdmaHandle, &xferConfig);
        EDMA_StartTransfer(handle->txEdmaHandle);

        /* Enable UART TX EDMA. */
        UART_EnableTxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

int UART_ReceiveEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle, uart_transfer_t *xfer)
{


    edma_transfer_config_t xferConfig;
    int status;

    /* If previous RX not finished. */
    if (kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        handle->rxState = kUART_RxBusy;
        handle->rxDataSizeAll = xfer->dataSize;

        /* Prepare transfer. */
        EDMA_PrepareTransfer(&xferConfig, (void *)UART_GetDataRegisterAddress(base), sizeof(uint8_t), xfer->data,
                             sizeof(uint8_t), sizeof(uint8_t), xfer->dataSize, kEDMA_PeripheralToMemory);

        /* Store the initially configured eDMA minor byte transfer count into the UART handle */
        handle->nbytes = sizeof(uint8_t);

        /* Submit transfer. */
        EDMA_SubmitTransfer(handle->rxEdmaHandle, &xferConfig);
        EDMA_StartTransfer(handle->rxEdmaHandle);

        /* Enable UART RX EDMA. */
        UART_EnableRxDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}
void UART_TransferAbortSendEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle)
{


    /* Disable UART TX EDMA. */
    UART_EnableTxDMA(base, false);

    /* Stop transfer. */
    EDMA_AbortTransfer(handle->txEdmaHandle);

    handle->txState = kUART_TxIdle;
}
/*!
 * @brief Enables or disables the UART transmitter DMA request.
 *
 * This function enables or disables the transmit data register empty flag, S1[TDRE], to generate the DMA requests.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableTxDMA(UART_MemMapPtr base, uint8_t enable)
{
    if (enable)
    {

        base->C5 |= UART_C5_TDMAS_MASK;

        base->C2 |= UART_C2_TIE_MASK;
    }
    else
    {

        base->C5 &= ~UART_C5_TDMAS_MASK;

        base->C2 &= ~UART_C2_TIE_MASK;
    }
}

/*!
 * @brief Enables or disables the UART receiver DMA.
 *
 * This function enables or disables the receiver data register full flag, S1[RDRF], to generate DMA requests.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableRxDMA(UART_MemMapPtr base, uint8_t enable)
{
    if (enable)
    {

        base->C5 |= UART_C5_RDMAS_MASK;

        base->C2 |= UART_C2_RIE_MASK;
    }
    else
    {

        base->C5 &= ~UART_C5_RDMAS_MASK;

        base->C2 &= ~UART_C2_RIE_MASK;
    }
}
void UART_TransferAbortReceiveEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle)
{


    /* Disable UART RX EDMA. */
    UART_EnableRxDMA(base, false);

    /* Stop transfer. */
    EDMA_AbortTransfer(handle->rxEdmaHandle);

    handle->rxState = kUART_RxIdle;
}
int UART_TransferGetSendCountEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle, uint32_t *count)
{


    if (kUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll -
             (uint32_t)handle->nbytes *
                 EDMA_GetRemainingMajorLoopCount(handle->txEdmaHandle->base, handle->txEdmaHandle->channel);

    return kStatus_Success;
}
int UART_TransferGetReceiveCountEDMA(UART_MemMapPtr base, uart_edma_handle_t *handle, uint32_t *count)
{


    if (kUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->rxDataSizeAll -
             (uint32_t)handle->nbytes *
                 EDMA_GetRemainingMajorLoopCount(handle->rxEdmaHandle->base, handle->rxEdmaHandle->channel);

    return kStatus_Success;
}

/**
  * @brief    ���Դ���+DMA
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/14 ���ڶ�
  */
void Test_UART_DMA(void)
{
    uint8_t g_tipString[] = "UART EDMA example\r\nSend back received data\r\nEcho every 8 characters\r\n";
    uint8_t g_txBuffer[8] = {0,1,2,3,4,5,6,7};
    uint8_t g_rxBuffer[8] = {0};
    uart_transfer_t xfer;
    uart_transfer_t sendXfer;
    uart_transfer_t receiveXfer;
    Uart4_DMA_Init();
    /* �������ݵ��׵�ַ */
    xfer.data = g_tipString; 
    /* ���͵ĳ��� */
    xfer.dataSize = sizeof(g_tipString) - 1;
    car_status.txOnGoing = true;
    
    /* ��ʼ���� */
    UART_SendEDMA(UART4_BASE_PTR, &g_uartEdmaHandle, &xfer);

    /* �ȴ�������� ������ɺ�����ص����� ��λtxOnGoing */
    while (car_status.txOnGoing)
    {
    }

    /* �շ�. */
    sendXfer.data = g_txBuffer;
    sendXfer.dataSize = 8;
    receiveXfer.data = g_rxBuffer;
    receiveXfer.dataSize = 8;

    
    while (1)
    {
        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!car_status.rxOnGoing) && car_status.rxBufferEmpty)
        {
            car_status.rxOnGoing = true;
//            UART_ReceiveEDMA(UART4_BASE_PTR, &g_uartEdmaHandle, &receiveXfer);
        }

        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!car_status.txOnGoing) && car_status.txBufferFull)
        {
            car_status.txOnGoing = true;
            UART_SendEDMA(UART4_BASE_PTR, &g_uartEdmaHandle, &sendXfer);
        }

        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!car_status.rxBufferEmpty) && (!car_status.txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, 8);
            car_status.rxBufferEmpty = true;
            car_status.txBufferFull = true;
        }
    }

}
