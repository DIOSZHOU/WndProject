

#include "CTriangle.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


//#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
//#pragma comment(lib, "glu32.lib")							
//#pragma comment(lib, "glaux.lib")							


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CTriangle * example = new CTriangle(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
CTriangle::CTriangle(const char * class_name) : GLApplication(class_name)
{
	/// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
}

/** ��ʼ��OpenGL */
bool CTriangle::Init()
{
	/** �û��Զ���ĳ�ʼ������ */
	/*glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true)*/;											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void CTriangle::Uninit()
{
	/** �û��Զ����ж�ع��� */
	///......
	///......
}

/** ������º��� */
void CTriangle::Update(DWORD milliseconds)
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();
	}

	if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	{
		ToggleFullscreen();
	}
	/** �û��Զ���ĸ��¹��� */
	m_Angle += (float)(milliseconds) / 15.0f;					/**< ������ת�ĽǶ� */

}

/** ���ƺ��� */
void CTriangle::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//�����Ļ����Ȼ���
	glLoadIdentity();										//���õ�ǰ��ģ�͹۲����,����ǰ���ƶ�������Ļ����.
	glTranslatef(-1.0f, 0.0f, -5.0f);						//OpenGL��Ļ����������X=Y=Z=0.0 X��������Y��������Z������
	glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);									//��ʼ���������� GL_QUADS ���ı��Σ�GL_POLYGON�������
	glColor3f(1.0f, 0.0f, 0.0f);							//�󶥵�����Ϊ��ɫ�����������ö���֮ǰ����
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();							//�����α����,ÿ��������ɫ��ͬ�������Ļ�ϣ�ƽ����ɫ(�����߶��ϻ������ڲ��ĸ������ɫ��ͨ�����ж������ɫ��ֵ)

	glLoadIdentity();					//����ģ�͹۲����
	glTranslatef(1.5f, 0.0f, -5.0f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);					//˳ʱ����Ƶ��Ƕ���ĺ���棬��ʱ�뻭�����������泯������
	glColor3f(0.0f, 1.0f, 0.0f);		//�����˵�ǰɫ�����ж������ǵ�ǰɫ, ������ɫ
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	
	glEnd();
}
