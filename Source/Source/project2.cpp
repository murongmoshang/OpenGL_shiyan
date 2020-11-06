#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265

//��Ŀ�涨
int fovy2 = 60;
int znear2 = 10;
int zfar2 = 100;
int UP2 = -1;
int loolAtX = 0;
int loolAtY = 0;
int loolAtZ = 5;

void RenderScene2(void)
{
    GLfloat rt, fv, x, y, h;
    fv = 30.0 * PI / 180;
    rt = tan(fv);
    h = znear2 * rt;
    y = h / 2;
    x = h / (2 * rt);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);	//�趨���汳��ɫΪ��ɫ��ǰ3�������ֱ����RGB����4��������͸����
    glClear(GL_COLOR_BUFFER_BIT);			//�����ɫ������
   // gluLookAt(loolAtX, loolAtY, loolAtZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();							//ģ����ͼ������ջ
    glTranslatef(0, 0, UP2);					//ƽ�ƣ��Ժ����Ķ���ʵʩ

    

    glRotatef(90, 0, 1, 0);					//��ת���Ժ����Ķ���ʵʩ
    //glTranslatef(-10, 0, 0);				//ƽ�ƣ��Ժ����Ķ���ʵʩ������龰��2��
    glTranslatef(-90, 0, 0);				//ƽ�ƣ��Ժ����Ķ���ʵʩ������龰��1��

    glColor3f(1, 1, 1);						//��������ͼԪ(����ע)ʱʹ�ø���ɫ
    glBegin(GL_LINE_LOOP);					// ׼�����ɺ�������ȷ�����߶����γɵıջ�
    glVertex3f(100, h, 0);
    glVertex3f(100, -y, -x);
    glVertex3f(100, -y, x);
    glEnd();
    glPopMatrix();							//ģ����ͼ�����ջ

    glutSwapBuffers();
}

void SpecialKey2(GLint key, GLint x, GLint y)
{
    if (key == GLUT_KEY_DOWN)
    {
        loolAtZ += 5;
    }
    else if (key == GLUT_KEY_UP)
    {
        loolAtZ -= 5;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        loolAtX -= 1;
        loolAtY -= 1;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        loolAtX += 1;
        loolAtY += 1;
    }
    RenderScene2();
}

void ChangeSize2(GLsizei Wv, GLsizei Hv)
{

    glViewport(0, 0, Wv, Hv);									// ���û���(��Ϊ�ӿ�)�ڴ����ϵ�λ�úʹ�С���ӿڿ���ռ���������ڣ�Ҳ����ֻռһ����
    glMatrixMode(GL_PROJECTION);								// ָ����ǰ����ΪͶӰ����
    glLoadIdentity();											// �ѵ�λ����ѹ��ͶӰ�����ջ

    gluPerspective(fovy2, (GLfloat)Wv / (GLfloat)Hv, znear2, zfar2);	// ������4������ȷ����ͶӰ����ѹ���ջ
                                                                // ��һ������fovy��ʾ��̨���������������ɵĶ���ǵĴ�С���Զ���Ϊ��λ��
                                                                // �ڶ�������Ϊ��̨����Ŀ�߱�

    glMatrixMode(GL_MODELVIEW);									// ָ����ǰ����Ϊģ����ͼ����
    glLoadIdentity();											// ���ñ任����
    //gluLookAt(0, 0.0, 0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
void main2() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// ������ʾģʽΪ˫��������ʹ��RGB��ɫ
    glutInitWindowSize(800, 600);				//���ô��ڴ�С
    glutCreateWindow("EXP2");					// ���촰��

    glutDisplayFunc(RenderScene2);				// �趨�ػ溯����ΪRenderScene;  �ػ溯���൱��MFC�е�OnDraw()
    glutSpecialFunc(SpecialKey2);
    glutReshapeFunc(ChangeSize2);				// �趨�����ڸı�ʱ�Ļص�����, ������������ά������ʾ��صĲ��������贰�ں�������MFC��OnSize()��

    glutMainLoop();								// ������ѭ�����ȴ���Ϣ�ĵ�����
}