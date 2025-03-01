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
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	
	glfwInit();

	//opengl version + modern functions thanks to core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "fractals", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window"<<std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//configures opengl
	gladLoadGL();

	//x,y bottom left to top right
	glViewport(0, 0, 800, 800);

	


	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

/*
	bool toggle = false;
	auto lastTime = glfwGetTime();
	float angle = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		double currTime = glfwGetTime();

		if (currTime - lastTime >= 0.1) {

			angle += 0.1f;
			lastTime = currTime;
		}

		
		glClearColor(sin(angle),cos(angle),tan(angle),1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
*/
	//cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}