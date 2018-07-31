/*********************************
之后所有的文档会采用相同的注解方式希望能够帮到大家
功能(func):opengl 打开第一个窗口
时间(Time):2018/7/29
作者(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include <iostream>
#include <stdio.h>
#include <GL\freeglut.h>

///<summary>
///渲染回调函数
///</summary>
void RenderScence()
{
	//清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	//交换前后缓存
	glutSwapBuffers();
}

///<summary>
///主函数
///</summary>
int main(int argc, char **argv)
{
	//初始化
	glutInit(&argc, argv);

	//显示模式
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//设置尺寸
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL 第一个窗口");

	//开始渲染
	glutDisplayFunc(RenderScence);

	//清空颜色缓存
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//开启循环
	glutMainLoop();

	//返回
	return 0;
}