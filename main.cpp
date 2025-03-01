#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 1.0f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {

	glfwInit();

	//opengl version + modern functions thanks to core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
	-1.0f,-1.0f,0.0f,
	0.0f,0.0f,0.0f,
	0.7f, -1.0f, 0.0f };

	GLFWwindow* window = glfwCreateWindow(800, 800, "fractals", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//configures opengl
	gladLoadGL();

	//x,y bottom left to top right
	glViewport(0, 0, 800, 800);


	//creates vbo and gets reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//attach shader to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//same shit with fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//link all shaders together into shader programm
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//interpret the shaders through buffer -> Vertex buffer object (we have a packed object with vertex data)
	//for opengl to find the object we need vertex array object vao
	//which stores pointers to one or more vbo and tells opengl to interpret that
	//vao needs to be generated before vbo

	//refereence container for vao and vbo
	GLuint VAO, VBO;

	//1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//make VAO the current vao by binding it
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//store verticies in the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configures vertex attr so that opengl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//enable vertex attr so opengl knows how to use it
	glEnableVertexAttribArray(0);

	//bind VBO and VAO to 0 so that we dont accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); //tell opengl we wanna use this vao
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);


		glfwPollEvents();
	}

	//cleanup

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}