#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;
#include"glut/glut.h"
#include<math.h>

#define PI 3.14159265


int fovy = 60;
int znear = 10;
int zfar = 100;
int UP = -10;

//模型输入数据结构设置
struct Point_user
{
	double x;
	double y;
	double z;
	double Intensity;
	double Dist;
};
//构建一个返回值类型为void类型容器的函数用于点云数据读入
void points_Read(string str_Path, vector<Point_user>& user_Pts, vector<Point_user>& user_Ptt)
{
	ifstream infile;
	infile.open(str_Path);
	if (!infile)
	{
		cout << "error" << endl;
		system("pause");
	}
	string str;
	double t1, t2, t3;
	Point_user Pt;
	int num1, num2;
	infile >> num1 >> num2;
	//cout << num1 << " " << num2 << endl;
	for (int i = 0; i < num1; i++) {//按空格读取
		infile >> Pt.x >> Pt.y >> Pt.z;
		/*if (i == 0) {
			cout << Pt.x << " " << Pt.y << " " << Pt.z << endl;
		}*/
		user_Pts.push_back(Pt);
	}
	for (int i = 0; i < num2; i++) {//按空格读取
		infile >> Pt.x >> Pt.y >> Pt.z;
		/*if (i == 0) {
			cout << Pt.x << " " << Pt.y << " " << Pt.z << endl;
		}*/
		user_Ptt.push_back(Pt);
	}
}

vector<Point_user> user_Pts, user_Ptt;

void RenderScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//设定画面背景色为绿色，前3个参数分别代表RGB，第4个参数是透明度
	glClear(GL_COLOR_BUFFER_BIT);			//清除颜色缓冲区

	glPushMatrix();							//模型视图矩阵入栈
	glTranslatef(0, 0, UP);					//平移，对后续的顶点实施
	glScalef(10, 10, 10);
	glColor3f(1, 1, 1);						//画后续的图元(见附注)时使用该颜色

	/*for (auto Pt : user_Pts) {
		glVertex3f(Pt.x, Pt.y, Pt.z);
	}*/
	for (auto Pt : user_Ptt) {
		glBegin(GL_LINE_LOOP);// 准备画由后续各点确定的线段所形成的闭环
		glVertex3f(user_Pts[Pt.x].x, user_Pts[Pt.x].y, user_Pts[Pt.x].z);
		glVertex3f(user_Pts[Pt.y].x, user_Pts[Pt.y].y, user_Pts[Pt.y].z);
		glVertex3f(user_Pts[Pt.z].x, user_Pts[Pt.z].y, user_Pts[Pt.z].z);
		glEnd();
	}


	glPopMatrix();							//模型视图矩阵出栈

	glutSwapBuffers();
}



void ChangeSize(GLsizei Wv, GLsizei Hv)
{

	glViewport(0, 0, Wv, Hv);									// 设置画面(称为视口)在窗口上的位置和大小，视口可能占满整个窗口，也可能只占一部分
	glMatrixMode(GL_PROJECTION);								// 指定当前矩阵为投影矩阵
	glLoadIdentity();											// 把单位矩阵压入投影矩阵堆栈

	gluPerspective(fovy, (GLfloat)Wv / (GLfloat)Hv, 10, 100);	// 把由这4个参数确定的投影矩阵压入堆栈
																// 第一个参数fovy表示棱台上下两个侧面所成的二面角的大小，以度数为单位，
																// 第二个参数为棱台底面的宽高比

	glMatrixMode(GL_MODELVIEW);									// 指定当前矩阵为模型视图矩阵
	glLoadIdentity();											// 重置变换矩阵
	//gluLookAt(0, 0.0, -100, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}

int main(void)
{
	points_Read("E:/gitee/open-gl_-course-experiment1/Shader/cow.txt", user_Pts, user_Ptt);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// 设置显示模式为双缓冲区，使用RGB颜色
	glutInitWindowSize(800, 600);				//设置窗口大小
	glutCreateWindow("EXP4");					// 构造窗口

	glutDisplayFunc(RenderScene);				// 设定重绘函数名为RenderScene;  重绘函数相当于MFC中的OnDraw()

	glutReshapeFunc(ChangeSize);				// 设定当窗口改变时的回调函数, 用于重置与三维场景显示相关的参数。重设窗口函数类似MFC的OnSize()。

	glutMainLoop();								// 进入主循环，等待消息的到来。
	return 0;
}

