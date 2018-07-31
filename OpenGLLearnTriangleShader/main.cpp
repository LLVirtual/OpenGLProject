/*********************************
之后所有的文档会采用相同的注解方式希望能够帮到大家
功能(func):opengl 画三角形 采用着色器代码编写
时间(Time):2018/7/31
作者(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include"math3D.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include<iostream>
#include<fstream>
#include <assert.h>
#pragma comment(lib,"glew32.lib")
//定义无整型变量
GLuint VBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
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


void AddShader(GLuint shaderProgram, const char * pShaderText, GLenum ShaderType)
{
	GLuint shaderobj = glCreateShader(ShaderType);

	// 检查是否定义成功
	if (shaderobj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	//定义shader 的代码源
	const GLchar *p[1];
	p[0] = pShaderText;
	
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);

	glShaderSource(shaderobj, 1, p, Lengths);
	//编译shader对象
	glCompileShader(shaderobj);

	//检查和shader 相关的错误
	GLint success;
	glGetShaderiv(shaderobj, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderobj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	//将编译好的shader 对象绑定到program object 程序对象上
	glAttachShader(shaderProgram, shaderobj);


}
///<summary>
///按照字节读取shder 文件，否则会出现错误不能用
///</summary>
char *loadshaderTex(const char * fileName)
{
	char* shaderText = NULL;

	GLint shaderLength = 0;

	FILE *fp;

	fp = fopen(fileName, "r");

	if (fp != NULL)

	{

		//get the char length 

		while (fgetc(fp) != EOF)

		{

			shaderLength++;

		}

		rewind(fp);



		shaderText = (GLchar*)malloc(shaderLength);

		if (shaderText != NULL)

		{

			fread(shaderText, 1, shaderLength, fp);

		}

		shaderText[shaderLength] = '\0';

		fclose(fp);

	}

	return shaderText;
}

void CompileShaders()
{
	GLuint ShaderProgram = glCreateProgram();
	// 检查是否创建成功
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
	// 存储着色器文本的字符串缓冲
	std::string vs, fs;
	// 分别读取着色器文件中的文本到字符串缓冲区
	// 添加顶点着色器和片段着色器
	vs = loadshaderTex(pVSFileName);
	fs = loadshaderTex(pFSFileName);


	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// 链接shader着色器程序，并检查程序相关错误
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 检查验证在当前的管线状态程序是否可以被执行
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 设置到管线声明中来使用上面成功建立的shader程序
	glUseProgram(ShaderProgram);


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
	glutCreateWindow("OpenGL 画三角形使用shader");

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

	//编译着色器
	// 编译着色器
	CompileShaders();

	//开启循环
	glutMainLoop();

	//返回
	return 0;
}