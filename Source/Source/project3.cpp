#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265

//题目规定
int fovy3 = 60;
int znear3 = 10;
int zfar3 = 100;
int a3 = -20;
void RenderScene3(void)
{
    GLfloat rt, fv;
    fv = 30.0 * PI / 180;
    rt = tan(fv);
    //300=10*600/(2*a*rt)//视口高度的一半计算公式
    a3 = -10 / rt;
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);	//设定画面背景色为绿色，前3个参数分别代表RGB，第4个参数是透明度
    glClear(GL_COLOR_BUFFER_BIT);			//清除颜色缓冲区

    glPushMatrix();							//模型视图矩阵入栈
    //glTranslatef(0, 0, UP);					//平移，对后续的顶点实施
    glColor3f(1, 1, 1);						//画后续的图元(见附注)时使用该颜色
    glBegin(GL_LINE_LOOP);					// 准备画由后续各点确定的线段所形成的闭环
    glVertex3f(-5, 5, a3);//左上角
    glVertex3f(-5, -5, a3);
    glVertex3f(5, -5, a3);
    glVertex3f(5, 5, a3);
    glEnd();
    glPopMatrix();							//模型视图矩阵出栈

    glutSwapBuffers();
}


void ChangeSize3(GLsizei Wv, GLsizei Hv)
{

    glViewport(0, 0, Wv, Hv);									// 设置画面(称为视口)在窗口上的位置和大小，视口可能占满整个窗口，也可能只占一部分
    glMatrixMode(GL_PROJECTION);								// 指定当前矩阵为投影矩阵
    glLoadIdentity();											// 把单位矩阵压入投影矩阵堆栈

    gluPerspective(fovy3, (GLfloat)Wv / (GLfloat)Hv, 10, 100);	// 把由这4个参数确定的投影矩阵压入堆栈
                                                                // 第一个参数fovy表示棱台上下两个侧面所成的二面角的大小，以度数为单位，
                                                                // 第二个参数为棱台底面的宽高比

    glMatrixMode(GL_MODELVIEW);									// 指定当前矩阵为模型视图矩阵
    glLoadIdentity();											// 重置变换矩阵
    //gluLookAt(0, 0.0, 0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}
void main3() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// 设置显示模式为双缓冲区，使用RGB颜色
    glutInitWindowSize(800, 600);				//设置窗口大小
    glutCreateWindow("EXP3");					// 构造窗口

    glutDisplayFunc(RenderScene3);				// 设定重绘函数名为RenderScene;  重绘函数相当于MFC中的OnDraw()
   glutReshapeFunc(ChangeSize3);				// 设定当窗口改变时的回调函数, 用于重置与三维场景显示相关的参数。重设窗口函数类似MFC的OnSize()。

    glutMainLoop();								// 进入主循环，等待消息的到来。
}