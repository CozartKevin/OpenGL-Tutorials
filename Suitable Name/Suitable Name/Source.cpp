#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Const Vertex Shader definition
const char* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Const Fragment Shader definition
const char* fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"	FragColor - vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

//Function Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main()
{

//Library and Window Setup

	//GLFW and GLAD verifications
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//Viewport and framebuffer resizing
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//Object creation setups
	
	//Vertices of triangle in NDC (normalized Device Coordinates)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//Vertex Buffer Object (VBO)
	unsigned int VBO; //Creating the Vertex buffer object
	glGenBuffers(1, &VBO); //Generating/assigning the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binding VBO to the Buffer Array
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Binding buffer data to the buffer array

	//Vertex Shader Object 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	
	//Fragment Shader Object 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//Vertex Shader compile-time checker
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Linking Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//2. use our shader program when we want to render an object
	glUseProgram(shaderProgram);
	//3. now draw that object
	//someOpenGLFunctionThatDrawsOurTriangle();

	//Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//..:: Initialization Code (Done once (unless your object frequently changes)) :: .. 
	// 1. bind vertex array object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	


	
//Render Loop

	// render loop (Main driver for render processing)
	while (!glfwWindowShouldClose(window))
	{

		


		// input processing function call
		processInput(window);

		// rendering commands 
		glClearColor(1.0f, 0.0f, 0.894f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawing Code
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

//GLFW Termination and function return
	glfwTerminate();
	return 0;

}

//Function Bodies
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

