#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 1280, HEIGHT = 720;
const char* WINDOW_TITLE = "WINDOW TITLE";

// Vertex Array Object, Vertex Buffer Object, Shader program
GLuint VAO, VBO, programShader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

// Vertex Shader source code
// 'in' means that this is an input from the previous stage (buffer - CreateTriangle function)
// 'out' means the ouptut that will go to the next stage (fragment shader), in this case
static const char* vShader = "									\n\
#version 330													\n\
layout(location = 0) in vec3 pos;								\n\
																\n\
void main()														\n\
{																\n\
	gl_Position = vec4(pos.x *0.1, pos.y *0.1, pos.z*0.9, 1.0); \n\
}";

// Fragment Shader source code
static const char* fShader = "									\n\
#version 330													\n\
out vec4 colorFrag;												\n\
void main()														\n\
{																\n\
	colorFrag = vec4(1.0, 0.3, 0.2, 1.0);						\n\
}";

// Create the triangle and store the data in buffers
void createTriangle() {
	// Create vertices array (x, y, z) - Remember anti-clockwise for front face
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, // Bottom left
		1.0f, -1.0f, 0.0f, // Bottom right
		0.0f, 1.0f, 0.0f, // Top middle
	};

	// Generate Vertex Array Object
	glGenVertexArrays(1, &VAO); // Generate 1 vertex array and store the ID in VAO (Multiple must be stored in an array)
	glBindVertexArray(VAO); // Select the vertex array to use (bind it)

	// Generate Vertex Buffer Object
	glGenBuffers(1, &VBO); // Generate 1 buffer and store the ID in VBO (Multiple must be stored in an array)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Select the VBO array to use and bind it to the GL_ARRAY_BUFFER target.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Allocate vertices data to the GL_ARRAY_BUFFER target. GL_STATIC_DRAW means the data will most likely not change at all or very rarely.

	// Set up vertex attribute pointers
	glVertexAttribPointer(
		0,	// Select the attribue 0 for the vertex shader. This is the same as the layout(location = 0) in the vertex shader.
		3,	// 3 means that each vertex has 3 components (x, y, z)
		GL_FLOAT,	// Data type of each component
		GL_FALSE,	// Normalise data?
		0,	// Stride - the space between each vertex (0 means tightly packed, same as sizeof(GL_FLOAT)*3)
		0	// Offset of the first component
	);
	glEnableVertexAttribArray(0); // Enable the vertex attribute at index 0 (the one we just set up with glVertexAttribPointer)

	// Unbind VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO from the GL_ARRAY_BUFFER target
	glBindVertexArray(0); // Unbind the VAO

}

// Add a shader to the shader program, given the shader source code and the shader type (vertex or fragment) and return the shader ID
GLuint addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	// Create the shader object, set the source code, and compile it
	GLuint theShader = glCreateShader(shaderType);
	glShaderSource(theShader, 1, theCode, codeLength);
	return theShader;
}

// Check for shader compilation errors and print them to the console
bool checkShaderCompilation(GLuint shaderProgram, GLenum statusEnum) {
	GLint result;
	GLchar eLog[1024] = { 0 };
	glGetProgramiv(shaderProgram, statusEnum, &result);
	
	if (result) {
		return true;
	}
	std::cout << "ERROR: ";
	switch (statusEnum) {
		case(GL_LINK_STATUS):
			std::cout << "Linking shader program failed: ";
			break;
		case(GL_VALIDATE_STATUS):
			std::cout << "Validating shader program failed: ";
			break;
		case(GL_COMPILE_STATUS):
			std::cout << "Compiling shader failed: ";
			break;
	}
	std::cout << eLog << std::endl;
}

// Compile the vertex and fragment shaders, add them to the shader program, and link the program
bool compileShaders() {

	// Create shader program and store at global variable
	programShader = glCreateProgram();
	if (!programShader) {
		std::cerr << "Error creating shader program" << std::endl;
		return false;
	}
	GLuint shaderID;
	
	// Add Vertex Shader
	shaderID = addShader(programShader, vShader, GL_VERTEX_SHADER);
	if (!checkShaderCompilation(programShader, GL_COMPILE_STATUS)) {
		return false;
	}
	glAttachShader(programShader, shaderID);

	// Add Fragment Shader
	shaderID = addShader(programShader, fShader, GL_FRAGMENT_SHADER);
	if (!checkShaderCompilation(programShader, GL_COMPILE_STATUS)) {
		return false;
	}
	glAttachShader(programShader, shaderID);

	// Link Program
	glLinkProgram(programShader);
	if (!checkShaderCompilation(programShader, GL_LINK_STATUS)) {
		return false;
	}

	// Validate Program
	glValidateProgram(programShader);
	if (!checkShaderCompilation(programShader, GL_VALIDATE_STATUS)) {
		return false;
	}
	
	return true;
}

int main() {
	// Initialise GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version 3.3, using core profile, forward compatible
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!mainWindow) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}

	// Get buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Create the triangle and compile the shaders
	createTriangle();
	compileShaders();

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow)) {
		// Get + Handle user input events
		glfwPollEvents();

		//Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programShader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);

		// Swap buffers
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}