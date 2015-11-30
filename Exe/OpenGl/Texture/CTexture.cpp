

#include "CTexture.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CTexture * example = new CTexture(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
CTexture::CTexture(const char * class_name) : GLApplication(class_name)
{
	/// ��ʼ���û��Զ���ĳ������
	m_Angle = 0.0f;												/**< ���ó�ʼ�Ƕ�Ϊ0 */
}

/** ��ʼ��OpenGL */
bool CTexture::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	glEnable(GL_TEXTURE_2D);                          /**< ��������ӳ�� */
	if (!Texture.LoadBitmap("image.bmp"))              /**< ����λͼ�ļ� */
	{
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< ����һ������������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//�����������2X2�������еļ�Ȩ����ƽ��ֵ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< ����������� */
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
		Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		Texture.image);

	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void CTexture::Uninit()
{
	/** �û��Զ����ж�ع��� */
	///......
	///......
	Texture.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &Texture.ID); /**< ɾ��������� */
}

/** ������º��� */
void CTexture::Update(DWORD milliseconds)
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
void CTexture::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */
	glLoadIdentity();
	/** ���ƹ��� */
	glTranslatef(0.0f, 0.0f, -7.0f);
	glRotatef(m_Angle, 1.0f, 1.0f, 0.0f);

	/** ��ʼ�����ı��� */
	glBegin(GL_QUADS);
	/// ǰ����
	glNormal3f(0.0f, 0.0f, 1.0f);								/**< ָ������ָ��۲��� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	/// �����
	glNormal3f(0.0f, 0.0f, -1.0f);								/**< ָ�����߱���۲��� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	/// ����
	glNormal3f(0.0f, 1.0f, 0.0f);								/**< ָ���������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	/// ����
	glNormal3f(0.0f, -1.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	/// �Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	/// �����
	glNormal3f(-1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();														/**< �ı��λ��ƽ��� */

	glFlush();				           /**< ǿ��ִ�����е�OpenGL���� */
}

