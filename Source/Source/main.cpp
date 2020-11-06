#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265

//��Ŀ�涨
int fovy = 60;
int znear = 10;
int zfar = 100;
int UP = -10;
void RenderScene(void)
{
    GLfloat rt, fv, x, y, h;
    fv = 30.0 * PI / 180;
    rt = tan(fv);
    h = znear * rt;
    y = h / 2;
    x = 3 * (h / 2) * rt;
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);	//�趨���汳��ɫΪ��ɫ��ǰ3�������ֱ����RGB����4��������͸����
    glClear(GL_COLOR_BUFFER_BIT);			//�����ɫ������

    glPushMatrix();							//ģ����ͼ������ջ
    glTranslatef(0, 0, UP);					//ƽ�ƣ��Ժ����Ķ���ʵʩ
    glColor3f(1, 1, 1);						//��������ͼԪ(����ע)ʱʹ�ø���ɫ
    glBegin(GL_LINE_LOOP);					// ׼�����ɺ�������ȷ�����߶����γɵıջ�
    glVertex3f(0, h, 0);
    glVertex3f(-x, -y, 0);
    glVertex3f(x, -y, 0);
    glEnd();
    glPopMatrix();							//ģ����ͼ�����ջ

    glutSwapBuffers();
}

void SpecialKey(GLint key, GLint x, GLint y)
{
    if (key == GLUT_KEY_UP)
    {
        if (UP >= -95)UP -= 5;
    }
    RenderScene();
}

void ChangeSize(GLsizei Wv, GLsizei Hv)
{

    glViewport(0, 0, Wv, Hv);									// ���û���(��Ϊ�ӿ�)�ڴ����ϵ�λ�úʹ�С���ӿڿ���ռ���������ڣ�Ҳ����ֻռһ����
    glMatrixMode(GL_PROJECTION);								// ָ����ǰ����ΪͶӰ����
    glLoadIdentity();											// �ѵ�λ����ѹ��ͶӰ�����ջ

    gluPerspective(fovy, (GLfloat)Wv / (GLfloat)Hv, 10, 100);	// ������4������ȷ����ͶӰ����ѹ���ջ
                                                                // ��һ������fovy��ʾ��̨���������������ɵĶ���ǵĴ�С���Զ���Ϊ��λ��
                                                                // �ڶ�������Ϊ��̨����Ŀ�߱�

    glMatrixMode(GL_MODELVIEW);									// ָ����ǰ����Ϊģ����ͼ����
    glLoadIdentity();											// ���ñ任����
    //gluLookAt(0, 0.0, 0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
int main() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// ������ʾģʽΪ˫��������ʹ��RGB��ɫ
    glutInitWindowSize(800, 600);				//���ô��ڴ�С
    glutCreateWindow("EXP1");					// ���촰��

    glutDisplayFunc(RenderScene);				// �趨�ػ溯����ΪRenderScene;  �ػ溯���൱��MFC�е�OnDraw()
    glutSpecialFunc(SpecialKey);
    glutReshapeFunc(ChangeSize);				// �趨�����ڸı�ʱ�Ļص�����, ������������ά������ʾ��صĲ��������贰�ں�������MFC��OnSize()��

    glutMainLoop();								// ������ѭ�����ȴ���Ϣ�ĵ�����
    return 0;
}