/*********************************
֮�����е��ĵ��������ͬ��ע�ⷽʽϣ���ܹ��ﵽ���
����(func):opengl �򿪵�һ������
ʱ��(Time):2018/7/29
����(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include <iostream>
#include <stdio.h>
#include <GL\freeglut.h>

///<summary>
///��Ⱦ�ص�����
///</summary>
void RenderScence()
{
	//�����ɫ����
	glClear(GL_COLOR_BUFFER_BIT);

	//����ǰ�󻺴�
	glutSwapBuffers();
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
	glutCreateWindow("OpenGL ��һ������");

	//��ʼ��Ⱦ
	glutDisplayFunc(RenderScence);

	//�����ɫ����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//����ѭ��
	glutMainLoop();

	//����
	return 0;
}