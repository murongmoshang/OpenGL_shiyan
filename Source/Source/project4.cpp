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

//ģ���������ݽṹ����
struct Point_user
{
	double x;
	double y;
	double z;
	double Intensity;
	double Dist;
};
//����һ������ֵ����Ϊvoid���������ĺ������ڵ������ݶ���
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
	for (int i = 0; i < num1; i++) {//���ո��ȡ
		infile >> Pt.x >> Pt.y >> Pt.z;
		/*if (i == 0) {
			cout << Pt.x << " " << Pt.y << " " << Pt.z << endl;
		}*/
		user_Pts.push_back(Pt);
	}
	for (int i = 0; i < num2; i++) {//���ո��ȡ
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//�趨���汳��ɫΪ��ɫ��ǰ3�������ֱ����RGB����4��������͸����
	glClear(GL_COLOR_BUFFER_BIT);			//�����ɫ������

	glPushMatrix();							//ģ����ͼ������ջ
	glTranslatef(0, 0, UP);					//ƽ�ƣ��Ժ����Ķ���ʵʩ
	glScalef(10, 10, 10);
	glColor3f(1, 1, 1);						//��������ͼԪ(����ע)ʱʹ�ø���ɫ

	/*for (auto Pt : user_Pts) {
		glVertex3f(Pt.x, Pt.y, Pt.z);
	}*/
	for (auto Pt : user_Ptt) {
		glBegin(GL_LINE_LOOP);// ׼�����ɺ�������ȷ�����߶����γɵıջ�
		glVertex3f(user_Pts[Pt.x].x, user_Pts[Pt.x].y, user_Pts[Pt.x].z);
		glVertex3f(user_Pts[Pt.y].x, user_Pts[Pt.y].y, user_Pts[Pt.y].z);
		glVertex3f(user_Pts[Pt.z].x, user_Pts[Pt.z].y, user_Pts[Pt.z].z);
		glEnd();
	}


	glPopMatrix();							//ģ����ͼ�����ջ

	glutSwapBuffers();
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
	//gluLookAt(0, 0.0, -100, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}

int main(void)
{
	points_Read("E:/gitee/open-gl_-course-experiment1/Shader/cow.txt", user_Pts, user_Ptt);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// ������ʾģʽΪ˫��������ʹ��RGB��ɫ
	glutInitWindowSize(800, 600);				//���ô��ڴ�С
	glutCreateWindow("EXP4");					// ���촰��

	glutDisplayFunc(RenderScene);				// �趨�ػ溯����ΪRenderScene;  �ػ溯���൱��MFC�е�OnDraw()

	glutReshapeFunc(ChangeSize);				// �趨�����ڸı�ʱ�Ļص�����, ������������ά������ʾ��صĲ��������贰�ں�������MFC��OnSize()��

	glutMainLoop();								// ������ѭ�����ȴ���Ϣ�ĵ�����
	return 0;
}

