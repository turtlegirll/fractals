#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<glad/glad.h>

class EBO {
public:
	
	//ID ref to ebo
	GLuint ID;
	
	//constructor that generates ebo and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !EBO_CLASS_H
