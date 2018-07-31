/*********************************
֮�����е��ĵ��������ͬ��ע�ⷽʽϣ���ܹ��ﵽ���
����(func):opengl �������� ������ɫ�������д
ʱ��(Time):2018/7/31
����(Autor):LU HONG XIAO come from DaLian University of Technology
**********************************/

#include"math3D.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include<iostream>
#include<fstream>
#include <assert.h>
#pragma comment(lib,"glew32.lib")
//���������ͱ���
GLuint VBO;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
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

	//��ʼ���Ƽ���ͼ�� ����������
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	//����ǰ�󻺴�
	glutSwapBuffers();

	//
	glFlush();
}

///<summary>
///�������㻺����
///</summary>
static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);



	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �󶨶�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


}


void AddShader(GLuint shaderProgram, const char * pShaderText, GLenum ShaderType)
{
	GLuint shaderobj = glCreateShader(ShaderType);

	// ����Ƿ���ɹ�
	if (shaderobj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	//����shader �Ĵ���Դ
	const GLchar *p[1];
	p[0] = pShaderText;
	
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);

	glShaderSource(shaderobj, 1, p, Lengths);
	//����shader����
	glCompileShader(shaderobj);

	//����shader ��صĴ���
	GLint success;
	glGetShaderiv(shaderobj, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderobj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	//������õ�shader ����󶨵�program object ���������
	glAttachShader(shaderProgram, shaderobj);


}
///<summary>
///�����ֽڶ�ȡshder �ļ����������ִ�������
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
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}
	// �洢��ɫ���ı����ַ�������
	std::string vs, fs;
	// �ֱ��ȡ��ɫ���ļ��е��ı����ַ���������
	// ��Ӷ�����ɫ����Ƭ����ɫ��
	vs = loadshaderTex(pVSFileName);
	fs = loadshaderTex(pFSFileName);


	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	glUseProgram(ShaderProgram);


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
	glutCreateWindow("OpenGL ��������ʹ��shader");

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

	//������ɫ��
	// ������ɫ��
	CompileShaders();

	//����ѭ��
	glutMainLoop();

	//����
	return 0;
}