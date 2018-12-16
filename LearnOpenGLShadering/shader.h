#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL\glew.h> //����glew ����ȡ���б����opengl ͷ�ļ�

class Shader
{
public:
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~Shader();
	//����ID
	GLuint Program;

public:
	void Use();
	char *loadshaderTex(const char * fileName);

};

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
	//1.���ļ�·���л�ȡ����/Ƭ����ɫ��
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//�׳��쳣
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//��ȡ�ļ�����
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();


	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//vShaderCode = loadshaderTex(vertexPath);
	//fShaderCode = loadshaderTex(fragmentPath);
	//������ɫ��
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error" << std::endl;
	}
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error" << std::endl;
	}

	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR";
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(this->Program);
}

char  * Shader::loadshaderTex(const char * fileName)
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
#endif // !SHADER_H

