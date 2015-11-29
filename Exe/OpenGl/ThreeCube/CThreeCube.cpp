

#include "CThreeCube.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CThreeCube * example = new CThreeCube(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
CThreeCube::CThreeCube(const char * class_name) : GLApplication(class_name)
{
	/// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
}

/** ��ʼ��OpenGL */
bool CThreeCube::Init()
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
void CThreeCube::Uninit()
{
	/** �û��Զ����ж�ع��� */
	///......
	///......
}

/** ������º��� */
void CThreeCube::Update(DWORD milliseconds)
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
void CThreeCube::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//�����Ļ����Ȼ���
	glLoadIdentity();										//���õ�ǰ��ģ�͹۲����,����ǰ���ƶ�������Ļ����.
	glTranslatef(-1.5f, 0.0f, -6.0f);						//OpenGL��Ļ����������X=Y=Z=0.0 X��������Y��������Z������
	glRotatef(m_Angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);									//�����ζ�����ʱ�������Ƶ�
	glColor3f(1.0f, 0.0f, 0.0f);							
	glVertex3f(0.0f, 1.0f, 0.0f);	//ǰ����
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);	//�Ҳ���
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);	//�����
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);	//�����		
	glVertex3f(0.0f, 1.0f, 0.0f);			
	glColor3f(0.0f, 0.0f, 1.0f);			
	glVertex3f(-1.0f, -1.0f, -1.0f);			
	glColor3f(0.0f, 1.0f, 0.0f);			
	glVertex3f(-1.0f, -1.0f, 1.0f);			

	glEnd();							

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);				// ��������������Ļ
	glRotatef(m_Angle, 1.0f, 1.0f, 1.0f);			// ��XYZ������ת������
	glBegin(GL_QUADS);					// ��ʼ����������
	
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ��Ϊ��ɫ
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����϶��� (����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����϶��� (����)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����¶��� (����)
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����¶��� (����)

	glColor3f(1.0f, 0.5f, 0.0f);			// ��ɫ�ĳɳ�ɫ
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)

	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ�ĳɺ�ɫ
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(ǰ��)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(ǰ��)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(ǰ��)
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(ǰ��)

	glColor3f(1.0f, 1.0f, 0.0f);			// ��ɫ�ĳɻ�ɫ
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����¶���(����)
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����¶���(����)

	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ�ĳ���ɫ
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(����)

	glColor3f(1.0f, 0.0f, 1.0f);			// ��ɫ�ĳ�������ɫ
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(����)
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)

	glEnd();
}

/*
���뽫OpenGL��Ļ�����һ�źܴ�Ļ�ֽ�����滹�������͸���Ĳ㡣�����Ǹ��ɴ����ĵ���ɵ������塣
��Щ��������ҡ��������¡���ǰ����Ĳ�������������塣�����������ĳ�����Ļ����ȷ���Ӧ���������3D����ʱû���κ����⡣
*/