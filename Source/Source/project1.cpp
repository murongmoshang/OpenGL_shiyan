#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265

//��Ŀ�涨
int fovy1 = 60;
int znear1 = 10;
int zfar1 = 100;
int UP1 = -10;
void RenderScene1(void)
{
    GLfloat rt, fv, x, y, h;
    fv = 30.0 * PI / 180;
    rt = tan(fv);//tan(30)
    h = znear1 * rt;
    y = h / 2;
    x = h / (2 * rt);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);	//�趨���汳��ɫΪ��ɫ��ǰ3�������ֱ����RGB����4��������͸����
    glClear(GL_COLOR_BUFFER_BIT);			//�����ɫ������

    glPushMatrix();							//ģ����ͼ������ջ
    //glTranslatef(0, 0, UP1);					//ƽ�ƣ��Ժ����Ķ���ʵʩ
    glColor3f(1, 1, 1);						//��������ͼԪ(����ע)ʱʹ�ø���ɫ
    glBegin(GL_LINE_LOOP);					// ׼�����ɺ�������ȷ�����߶����γɵıջ�
    glVertex3f(0, h, UP1);
    glVertex3f(-x, -y, UP1);
    glVertex3f(x, -y, UP1);
    glEnd();
    glPopMatrix();							//ģ����ͼ�����ջ

    glutSwapBuffers();
}

void SpecialKey1(GLint key, GLint x, GLint y)
{
    if (key == GLUT_KEY_UP)
    {
        if (UP1 > -100)UP1 -= 5;
    }

    RenderScene1();
}

void ChangeSize1(GLsizei Wv, GLsizei Hv)
{

    glViewport(0, 0, Wv, Hv);									// ���û���(��Ϊ�ӿ�)�ڴ����ϵ�λ�úʹ�С���ӿڿ���ռ���������ڣ�Ҳ����ֻռһ����
    glMatrixMode(GL_PROJECTION);								// ָ����ǰ����ΪͶӰ����
    glLoadIdentity();											// �ѵ�λ����ѹ��ͶӰ�����ջ

    gluPerspective(fovy1, (GLfloat)Wv / (GLfloat)Hv, znear1, zfar1);	// ������4������ȷ����ͶӰ����ѹ���ջ
                                                                // ��һ������fovy��ʾ��̨���������������ɵĶ���ǵĴ�С���Զ���Ϊ��λ��
                                                                // �ڶ�������Ϊ��̨����Ŀ�߱�

    glMatrixMode(GL_MODELVIEW);									// ָ����ǰ����Ϊģ����ͼ����
    glLoadIdentity();											// ���ñ任����
    //gluLookAt(0, 0.0, 0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
int main1() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// ������ʾģʽΪ˫��������ʹ��RGB��ɫ
    glutInitWindowSize(800, 600);				//���ô��ڴ�С
    glutCreateWindow("EXP1");					// ���촰��

    glutDisplayFunc(RenderScene1);				// �趨�ػ溯����ΪRenderScene;  �ػ溯���൱��MFC�е�OnDraw()
    glutSpecialFunc(SpecialKey1);
    glutReshapeFunc(ChangeSize1);				// �趨�����ڸı�ʱ�Ļص�����, ������������ά������ʾ��صĲ��������贰�ں�������MFC��OnSize()��

    glutMainLoop();								// ������ѭ�����ȴ���Ϣ�ĵ�����
    return 0;
}