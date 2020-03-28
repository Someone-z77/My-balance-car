#include "include.h"
#include "ImageProcess.h"


/**
  * @brief    图像处理
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/15 星期三
  */
void ImageProcess(volatile uint8_t tmImage[IMAGEH][IMAGEW])
{
    Get_Use_Image();      //从采集图像数据中取出自己想要使用的大小
    Get_01_Value(1);      //二值化图像数据
}
