#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265

//��Ŀ�涨
int fovy3 = 60;
int znear3 = 10;
int zfar3 = 100;
int a3 = -20;
void RenderScene3(void)
{
    GLfloat rt, fv;
    fv = 30.0 * PI / 180;
    rt = tan(fv);
    //300=10*600/(2*a*rt)//�ӿڸ߶ȵ�һ����㹫ʽ
    a3 = -10 / rt;
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);	//�趨���汳��ɫΪ��ɫ��ǰ3�������ֱ����RGB����4��������͸����
    glClear(GL_COLOR_BUFFER_BIT);			//�����ɫ������

    glPushMatrix();							//ģ����ͼ������ջ
    //glTranslatef(0, 0, UP);					//ƽ�ƣ��Ժ����Ķ���ʵʩ
    glColor3f(1, 1, 1);						//��������ͼԪ(����ע)ʱʹ�ø���ɫ
    glBegin(GL_LINE_LOOP);					// ׼�����ɺ�������ȷ�����߶����γɵıջ�
    glVertex3f(-5, 5, a3);//���Ͻ�
    glVertex3f(-5, -5, a3);
    glVertex3f(5, -5, a3);
    glVertex3f(5, 5, a3);
    glEnd();
    glPopMatrix();							//ģ����ͼ�����ջ

    glutSwapBuffers();
}


void ChangeSize3(GLsizei Wv, GLsizei Hv)
{

    glViewport(0, 0, Wv, Hv);									// ���û���(��Ϊ�ӿ�)�ڴ����ϵ�λ�úʹ�С���ӿڿ���ռ���������ڣ�Ҳ����ֻռһ����
    glMatrixMode(GL_PROJECTION);								// ָ����ǰ����ΪͶӰ����
    glLoadIdentity();											// �ѵ�λ����ѹ��ͶӰ�����ջ

    gluPerspective(fovy3, (GLfloat)Wv / (GLfloat)Hv, 10, 100);	// ������4������ȷ����ͶӰ����ѹ���ջ
                                                                // ��һ������fovy��ʾ��̨���������������ɵĶ���ǵĴ�С���Զ���Ϊ��λ��
                                                                // �ڶ�������Ϊ��̨����Ŀ�߱�

    glMatrixMode(GL_MODELVIEW);									// ָ����ǰ����Ϊģ����ͼ����
    glLoadIdentity();											// ���ñ任����
    //gluLookAt(0, 0.0, 0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
void main3() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// ������ʾģʽΪ˫��������ʹ��RGB��ɫ
    glutInitWindowSize(800, 600);				//���ô��ڴ�С
    glutCreateWindow("EXP3");					// ���촰��

    glutDisplayFunc(RenderScene3);				// �趨�ػ溯����ΪRenderScene;  �ػ溯���൱��MFC�е�OnDraw()
   glutReshapeFunc(ChangeSize3);				// �趨�����ڸı�ʱ�Ļص�����, ������������ά������ʾ��صĲ��������贰�ں�������MFC��OnSize()��

    glutMainLoop();								// ������ѭ�����ȴ���Ϣ�ĵ�����
}