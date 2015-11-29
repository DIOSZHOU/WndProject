

#include "CTriangle.h"											/**< 包含头文件 */

#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>												
#include <gl\glaux.h>											


//#pragma comment(lib, "opengl32.lib")							/**< 包含OpenGL链接库文件 */
//#pragma comment(lib, "glu32.lib")							
//#pragma comment(lib, "glaux.lib")							


/** 创建一个程序的实例 */
GLApplication * GLApplication::Create(const char * class_name)
{
	CTriangle * example = new CTriangle(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** 构造函数 */
CTriangle::CTriangle(const char * class_name) : GLApplication(class_name)
{
	/// 初始化用户自定义的程序变量
	m_Angle = 0.0f;												/**< 设置初始角度为0 */
}

/** 初始化OpenGL */
bool CTriangle::Init()
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
void CTriangle::Uninit()
{
	/** 用户自定义的卸载过程 */
	///......
	///......
}

/** 程序更新函数 */
void CTriangle::Update(DWORD milliseconds)
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
void CTriangle::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//清除屏幕及深度缓存
	glLoadIdentity();										//重置当前的模型观察矩阵,将当前点移动到了屏幕中心.
	glTranslatef(-1.0f, 0.0f, -5.0f);						//OpenGL屏幕中心坐标是X=Y=Z=0.0 X向右正，Y向上正，Z向外正
	glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);									//开始绘制三角形 GL_QUADS 画四边形，GL_POLYGON画多边形
	glColor3f(1.0f, 0.0f, 0.0f);							//左顶点设置为红色，必须在设置顶点之前设置
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();							//三角形被填充,每个顶点颜色不同，在中心汇合，平滑着色(对于线段上或多边形内部的各点的颜色将通过所有顶点的颜色插值)

	glLoadIdentity();					//重置模型观察矩阵。
	glTranslatef(1.5f, 0.0f, -5.0f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);					//顺时针绘制的是对象的后表面，逆时针画出来的是正面朝向我们
	glColor3f(0.0f, 1.0f, 0.0f);		//设置了当前色后所有东西都是当前色, 单调着色
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	
	glEnd();
}
