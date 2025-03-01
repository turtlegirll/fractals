#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



int main() {

	glfwInit();

	//opengl version + modern functions thanks to core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] =
	{
		-0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f, 1.0f, 0.0f, 0.0f,	// Lower left corner
		0.5f,		-0.5f * float(sqrt(3)) / 3,		0.0f, 1.0f, 0.0f, 0.0f,	// Lower right corner
		0.0f,		0.5f * float(sqrt(3)) * 2 / 3,	0.0f, 1.0f, 0.7f, 0.0f,	// Upper corner
		-0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f, 1.0f, 0.7f, 0.0f,	// Inner left
		0.5f / 2,	0.5f * float(sqrt(3)) / 6,		0.0f, 0.3f, 0.4f, 0.4f,	// Inner right
		0.0f,		-0.5f * float(sqrt(3)) / 3,		0.0f ,0.4f, 0.5f, 0.6f,	// Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1 // Lower right triangle
	};

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


	//interpret the shaders through buffer -> Vertex buffer object (we have a packed object with vertex data)
	//for opengl to find the object we need vertex array object vao
	//which stores pointers to one or more vbo and tells opengl to interpret that
	//vao needs to be generated before vbo

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;

	//make VAO the current vao by binding it
	VAO1.Bind();

	//generate vbo/ebo and link it to vertices/indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	//links vbo to vao and binds vbo
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//gets reference value of uniform from vbo
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		//assigns a value to the uniform
		//has to be done after activating the shader program
		glUniform1f(uniID, -0.4f);

		VAO1.Bind(); //tell opengl we wanna use this vao
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//cleanup
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}