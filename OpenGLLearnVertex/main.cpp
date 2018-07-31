/*********************************
֮�����е��ĵ��������ͬ��ע�ⷽʽϣ���ܹ��ﵽ���
����(func):opengl ������
ʱ��(Time):2018/7/29
����(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include "math3D.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

#pragma comment(lib,"glew32.lib")
//���������ͱ���
GLuint VBO;


///<summary>
///��Ⱦ�ص�����
///</summary>
static void RenderScence()
{
	//�����ɫ����
	glClear(GL_COLOR_BUFFER_BIT);

	//������������
	glEnableVertexAttribArray(0);

	//�󶨻�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//���߹�����ô����bufer �е�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//��ʼ���Ƽ���ͼ��
	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);

	//����ǰ�󻺴�
	glutSwapBuffers();
}

///<summary>
///�������㻺����
///</summary>
static void CreateVertexBuffer()
{
	Vector3f vertice[1];
	vertice[0] = Vector3f(0, 0, 0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �󶨶�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);


}

///<summary>
///������
///</summary>
int main(int argc, char **argv)
{
	//��ʼ��
	glutInit(&argc, argv);

	//��ʾģʽ
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//���óߴ�
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL ������");

	//��ʼ��Ⱦ
	glutDisplayFunc(RenderScence);

	// ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	//�����ɫ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//�������㻺����
	CreateVertexBuffer();
	//����ѭ��
	glutMainLoop();

	//����
	return 0;
}