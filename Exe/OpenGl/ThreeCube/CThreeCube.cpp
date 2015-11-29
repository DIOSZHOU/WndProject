

#include "CThreeCube.h"											/**< 包含头文件 */

#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>												
#include <gl\glaux.h>											


/** 创建一个程序的实例 */
GLApplication * GLApplication::Create(const char * class_name)
{
	CThreeCube * example = new CThreeCube(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** 构造函数 */
CThreeCube::CThreeCube(const char * class_name) : GLApplication(class_name)
{
	/// 初始化用户自定义的程序变量
	m_Angle = 0.0f;												/**< 设置初始角度为0 */
}

/** 初始化OpenGL */
bool CThreeCube::Init()
{
	/** 用户自定义的初始化过程 */
	/*glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true)*/;											/**< 改变OpenGL窗口大小，直接调用子类的函数 */

	return true;												/**< 成功返回 */
}

/** 用户自定义的卸载函数 */
void CThreeCube::Uninit()
{
	/** 用户自定义的卸载过程 */
	///......
	///......
}

/** 程序更新函数 */
void CThreeCube::Update(DWORD milliseconds)
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< 按ESC退出 */
	{
		TerminateApplication();
	}

	if (m_Keys.IsPressed(VK_F1) == true)						/**< 按F1切换窗口/全屏模式 */
	{
		ToggleFullscreen();
	}
	/** 用户自定义的更新过程 */
	m_Angle += (float)(milliseconds) / 15.0f;					/**< 更新旋转的角度 */

}

/** 绘制函数 */
void CThreeCube::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//清除屏幕及深度缓存
	glLoadIdentity();										//重置当前的模型观察矩阵,将当前点移动到了屏幕中心.
	glTranslatef(-1.5f, 0.0f, -6.0f);						//OpenGL屏幕中心坐标是X=Y=Z=0.0 X向右正，Y向上正，Z向外正
	glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);									//三角形都是逆时针次序绘制的
	glColor3f(1.0f, 0.0f, 0.0f);							
	glVertex3f(0.0f, 1.0f, 0.0f);	//前侧面
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);	//右侧面
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);	//左侧面
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);	//后侧面		
	glVertex3f(0.0f, 1.0f, 0.0f);			
	glColor3f(0.0f, 0.0f, 1.0f);			
	glVertex3f(-1.0f, -1.0f, -1.0f);			
	glColor3f(0.0f, 1.0f, 0.0f);			
	glVertex3f(-1.0f, -1.0f, 1.0f);			

	glEnd();							

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);				// 先右移再移入屏幕
	glRotatef(m_Angle, 1.0f, 1.0f, 1.0f);			// 在XYZ轴上旋转立方体
	glBegin(GL_QUADS);					// 开始绘制立方体
	
	glColor3f(0.0f, 1.0f, 0.0f);			// 颜色改为蓝色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左下顶点 (顶面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右下顶点 (顶面)

	glColor3f(1.0f, 0.5f, 0.0f);			// 颜色改成橙色
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右上顶点(底面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左上顶点(底面)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左下顶点(底面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(底面)

	glColor3f(1.0f, 0.0f, 0.0f);			// 颜色改成红色
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(前面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(前面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(前面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(前面)

	glColor3f(1.0f, 1.0f, 0.0f);			// 颜色改成黄色
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右上顶点(后面)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左上顶点(后面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左下顶点(后面)
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右下顶点(后面)

	glColor3f(0.0f, 0.0f, 1.0f);			// 颜色改成蓝色
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(左面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点(左面)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// 四边形的左下顶点(左面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(左面)

	glColor3f(1.0f, 0.0f, 1.0f);			// 颜色改成紫罗兰色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点(右面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(右面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(右面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(右面)

	glEnd();
}

/*
必须将OpenGL屏幕想象成一张很大的画纸，后面还带着许多透明的层。差不多就是个由大量的点组成的立方体。
这些点从左至右、从上至下、从前到后的布满了这个立方体。如果您能想象的出在屏幕的深度方向，应该在设计新3D对象时没有任何问题。
*/