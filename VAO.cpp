#include"VAO.h"


VAO::VAO(){

	glGenVertexArrays(1, &ID);


}

void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset) {

	VBO.Bind();
	
	//configures vertex attr so that opengl knows how to read the VBO
	glVertexAttribPointer(layout, numComponent, type, GL_FALSE, stride, offset);

	//enable vertex attr so opengl knows how to use it
	glEnableVertexAttribArray(layout);

	VBO.Unbind();

}

//make VAO the current vao by binding it
void VAO::Bind() {
	glBindVertexArray(ID);
}

//bind VAO to 0 so that we dont accidentally modify the VAO we created 
// -> 'unbinding here'
void VAO::Unbind() {
	glBindVertexArray(0);

}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}
