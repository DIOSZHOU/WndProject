#ifndef _CTRIANGLE_H_EBA7F95E_59DE_478D_AA3E_7D1471BAABAB_
#define _CTRIANGLE_H_EBA7F95E_59DE_478D_AA3E_7D1471BAABAB_
/*
*************************************************************************
模块名  : CTriangle
文件名  : CTriangle.h
实现功能: 
作者    : 周健
版本    :
-------------------------------------------------------------------------
备注    : 尝试之前的窗口静态库未成功，直接把MFC风格弄成静态库，以后窗口程序
		   可以直接继承即可
-------------------------------------------------------------------------
修改记录: 画一个三角形
创建时间：2015.11.29  2:02   
*************************************************************************
* 版本所有(c)    保留所有权利                                           *
************************************************************************/

#include "GLFrame.h"												/**< 包含基本的框架类 */

/** 从GL_Application派生出一个子类 */
class CTriangle : GLApplication
{
public:
	bool	Init();										/**< 执行所有的初始化工作，如果成功函数返回true */
	void	Uninit();										/**< 执行所有的卸载工作 */
	void	Update(DWORD milliseconds);							/**< 执行所有的更新操作，传入的参数为两次操作经过的时间，以毫秒为单位 */
	void	Draw();												/**< 执行所有的绘制操作 */

private:
	friend class GLApplication;								/**< 父类为它的一个友元类，可以用来创建程序的实例，见函数GL_Application * GL_Application::Create(const char * class_name) */
	CTriangle(const char * class_name);						/**< 构造函数 */
	/** 用户自定义的程序变量 */
	float	m_Angle;											/**< 使用它来旋转三角形 */
};


#endif	// __EXAMPLE_H__

/*
1.OpenGl是一种状态机
  绘制3D图形，有很多变量影响他的绘制(对象是不是与背景混合，是否正面/背面剔除),这类变量的集合称为管线的状态。OpenGL用一种状态模型来
  追踪所有的OPengl状态变量。当一个状态被设置后，他就一直保持这个状态，直到其他函数对它进行修改为止。许多状态只能简单的打开或关闭，
  例如深度测试，打开/关闭，打开深度测试的集合绘图将会被检查以确保在进行渲染前总会在任何定位于他后面对象的前方。
  glEnable(GLenum capability);
  glDisable(GLenum capability);
  Glboolean glIsEnabled(GLenum capability);		//判断某个状态变量是否打开

  如果需要对状态变量进行临时修改，可以用glPushAttrib(),glPushClientAttrib()把状态变量的集合保存在一个属性栈中，对
  他们进行临时的修改，以后再用glPopAttrib()或glPopClientAttrib()恢复这些值.
*/