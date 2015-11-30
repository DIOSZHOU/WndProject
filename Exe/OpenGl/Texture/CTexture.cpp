

#include "CTexture.h"											/**< 包含头文件 */

#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>												
#include <gl\glaux.h>											


/** 创建一个程序的实例 */
GLApplication * GLApplication::Create(const char * class_name)
{
	CTexture * example = new CTexture(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** 构造函数 */
CTexture::CTexture(const char * class_name) : GLApplication(class_name)
{
	/// 初始化用户自定义的程序变量
	m_Angle = 0.0f;												/**< 设置初始角度为0 */
}

/** 初始化OpenGL */
bool CTexture::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true);											/**< 改变OpenGL窗口大小，直接调用子类的函数 */

	glEnable(GL_TEXTURE_2D);                          /**< 启用纹理映射 */
	if (!Texture.LoadBitmap("image.bmp"))              /**< 载入位图文件 */
	{
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< 生成一个纹理对象名称 */
	/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//离像素最近的2X2纹素阵列的加权线性平均值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< 创建纹理对象 */
	/** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
		Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		Texture.image);

	return true;												/**< 成功返回 */
}

/** 用户自定义的卸载函数 */
void CTexture::Uninit()
{
	/** 用户自定义的卸载过程 */
	///......
	///......
	Texture.FreeImage();              /** 释放纹理图像占用的内存 */
	glDeleteTextures(1, &Texture.ID); /**< 删除纹理对象 */
}

/** 程序更新函数 */
void CTexture::Update(DWORD milliseconds)
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
void CTexture::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< 清楚缓存 */
	glLoadIdentity();
	/** 绘制过程 */
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);

	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 前侧面
	glNormal3f(0.0f, 0.0f, 1.0f);								/**< 指定法线指向观察者 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	/// 后侧面
	glNormal3f(0.0f, 0.0f, -1.0f);								/**< 指定法线背向观察者 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);								/**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	/// 底面
	glNormal3f(0.0f, -1.0f, 0.0f);								/**< 指定法线朝下 */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	/// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);								/**< 指定法线朝右 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	/// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);								/**< 指定法线朝左 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();														/**< 四边形绘制结束 */

	glFlush();				           /**< 强制执行所有的OpenGL命令 */
}

