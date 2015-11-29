#ifndef _CTHREECUBE_H_D4C53EAB_E8D5_4F8E_A3D0_987B9BBC2411__
#define _CTHREECUBE_H_D4C53EAB_E8D5_4F8E_A3D0_987B9BBC2411__

/*
*************************************************************************
模块名  : CThreeCube
文件名  : CThreeCube.h
实现功能: 
作者    : 周健
版本    :
-------------------------------------------------------------------------
备注    : 画一个三角体和正方体，代码为NEHE的。
-------------------------------------------------------------------------
修改记录: 画一个三角形
创建时间：2015.11.29  18:51   
*************************************************************************
* 版本所有(c)    保留所有权利                                           *
************************************************************************/

#include "GLFrame.h"												/**< 包含基本的框架类 */

/** 从GL_Application派生出一个子类 */
class CThreeCube : GLApplication
{
public:
	bool	Init();										/**< 执行所有的初始化工作，如果成功函数返回true */
	void	Uninit();										/**< 执行所有的卸载工作 */
	void	Update(DWORD milliseconds);							/**< 执行所有的更新操作，传入的参数为两次操作经过的时间，以毫秒为单位 */
	void	Draw();												/**< 执行所有的绘制操作 */

private:
	friend class GLApplication;								/**< 父类为它的一个友元类，可以用来创建程序的实例，见函数GL_Application * GL_Application::Create(const char * class_name) */
	CThreeCube(const char * class_name);						/**< 构造函数 */
	/** 用户自定义的程序变量 */
	float	m_Angle;											/**< 使用它来旋转三角形 */
};


#endif	// __CTHREECUBE_H__

