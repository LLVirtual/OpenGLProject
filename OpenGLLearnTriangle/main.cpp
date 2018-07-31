/*********************************
之后所有的文档会采用相同的注解方式希望能够帮到大家
功能(func):opengl 画三角形
时间(Time):2018/7/29
作者(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include"math3D.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

#pragma comment(lib,"glew32.lib")
//定义无整型变量
GLuint VBO;


///<summary>
///渲染回调函数
///</summary>
static void RenderScence()
{
	//清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	//开启顶点属性
	glEnableVertexAttribArray(0);

	//绑定缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//告诉管线怎么解析bufer 中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//开始绘制几何图形 绘制三角形
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	//交换前后缓存
	glutSwapBuffers();

	//
	glFlush();
}

///<summary>
///创建定点缓冲器
///</summary>
static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);



	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


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
	glutCreateWindow("OpenGL 画三角形");

	//开始渲染
	glutDisplayFunc(RenderScence);

	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	//清空颜色缓存
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//创建顶点缓冲器
	CreateVertexBuffer();
	//开启循环
	glutMainLoop();

	//返回
	return 0;
}