//======================================================================
/**
*  @file  CBMPLoader.h
*
*  项目描述： 纹理映射
*  文件描述:  载入位图类 
*  适用平台： Windows98/2000/NT/XP
*  
*  作者：     BrightXu
*  电子邮件:  huoxini@hotmail.com
*  创建日期： 2006-11-23	
*  修改日期： 2006-11-26
*	
*/																			
//======================================================================

#ifndef __CBMPLOADER_H__
#define __CBMPLOADER_H__

#include<windows.h>        /**< 包含windows.h文件 */
#include<stdio.h>          /**< 包含stdio.h文件 */

#define BITMAP_ID 0x4D42	/**< 位图文件的标志 */

/** 位图载入类 */
class CBMPLoader
{
   public:
      CBMPLoader();
      ~CBMPLoader();

      bool LoadBitmap(char *filename); /**< 装载一个bmp文件 */
      void FreeImage();                /**< 释放图像数据 */

      unsigned int ID;                 /**< 生成纹理的ID号 */
      int imageWidth;                  /**< 图像宽度 */
      int imageHeight;                 /**< 图像高度 */
      unsigned char *image;            /**< 指向图像数据的指针 */
};

#endif //__CBMPLOADER_H__

