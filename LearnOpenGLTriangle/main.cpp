#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 800;

float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};
unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
int success;
char infoLog[512];


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

void Init()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif


}

void CompileShaders()
{
	//build and compile our shader program
	const char *vertexShdersouce = loadshaderTex("shader.vs");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShdersouce, NULL);
	glCompileShader(vertexShader);
	/*
	判断编译器是否成功
	*/
	glGetShaderiv(vertexShader, GL_COMPILE, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fragmentShadersouce = loadshaderTex("shader.fs");
	glShaderSource(fragmentShader, 1, &fragmentShadersouce, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	}

	//激活
	shaderProgram = glCreateProgram();
	//和连接

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//判断对错
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//激活和使用

}

void CreateVertexBuffer()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //缓冲类型
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
}
int main()
{
	Init();

	// glfw window creation												 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LLVIRTUAL--LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers GLAD是用来管理OpenGL的函数指针的
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

 
	// set up vertex data (and buffer(s)) and configure vertex attributes
	//
	// ------------------------------------------------------------------
	CompileShaders();
	

	CreateVertexBuffer();


	while (!glfwWindowShouldClose(window))
	{
		// 键盘输入----------
		processInput(window);
		//背景色-------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		
		glUseProgram(shaderProgram);
		//邦定vertexArray		
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	//delete some thing
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
