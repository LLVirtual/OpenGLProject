#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL\glew.h> //包含glew 来获取所有必须的opengl 头文件

class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	~Shader();
	//程序ID
	GLuint Program;
	
public:
	void setInt(const std::string &name, int value);
	void Use();
	char *loadshaderTex(const char * fileName);

};

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
	//1.从文件路径中获取顶点/片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//抛出异常
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件缓冲
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
	//编译着色器
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

void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}
#endif // !SHADER_H

