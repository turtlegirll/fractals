#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <chrono>
#include "glm/glm.hpp" 
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


bool dragging = false;
double lastX, lastY;

int maxIterations = 100;
float zoom = 1.0f;

glm::vec2 center(-0.5f, 0.0f);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom *= (yoffset > 0) ? 0.9f : 1.1f; 
	std::cout << "Zoom: " << zoom << " | Center: (" << center.x << ", " << center.y << ")" << std::endl;

	}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			dragging = true;
			glfwGetCursorPos(window, &lastX, &lastY);
		}
		else if (action == GLFW_RELEASE) {
			dragging = false;
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (dragging) {
		double dx = xpos - lastX; 
		double dy = ypos - lastY;

		center.x -= dx * zoom * 0.005f; 
		center.y += dy * zoom * 0.005f; 

		lastX = xpos; 
		lastY = ypos;
	}
}


int main() {

	glfwInit();

	//opengl version + modern functions thanks to core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLfloat vertices[] =
	{
		-1.0f,-1.0f, //bottom left
		1.0f,-1.0f,	//bottom right
		-1.0f,1.0f,	//top left
		1.0f,1.0f,	//top right


	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0,1,2,
		1,3,2
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

	Shader shaderProgram("fractal.vert", "fractal.frag");

	VAO VAO1;

	//make VAO the current vao by binding it
	VAO1.Bind();

	//generate vbo/ebo and link it to vertices/indices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	//links vbo to vao and binds vbo
	VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "zoom");
	GLuint uniID2 = glGetUniformLocation(shaderProgram.ID, "center");
	GLuint uniID3 = glGetUniformLocation(shaderProgram.ID, "maxIterations");


	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwSetScrollCallback(window, scroll_callback); 


	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, zoom);
		glUniform2f(uniID2, center.x,center.y);
		glUniform1i(uniID3, maxIterations);

		VAO1.Bind(); //tell opengl we wanna use this vao
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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