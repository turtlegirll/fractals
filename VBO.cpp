#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//store verticies in the vbo
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);

}

//bind VBO to 0 so that we dont accidentally modify the VBO we created 
// -> 'unbinding here'
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}