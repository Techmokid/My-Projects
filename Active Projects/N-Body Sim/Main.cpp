//Custom code setup
#include "functions.h"

#define windowWidth 1600
#define windowHeight 900

#define particleCount 10

struct _vec2 { float x; float y; };
struct Color { float r; float g; float b; };

struct Body {
    _vec2 position;
    _vec2 velocity;
	Color color;
	float mass;
	bool collided;
};


int main() {
	StartWindow(windowWidth,windowHeight);
	GLFWwindow* window = GetCurrentActiveWindow();
	
	std::vector<Body> bodies;
	for (int i = 0; i < particleCount; i++) {
		Body b;
		b.position.x = getRandomFloat(0.4,0.6);
		b.position.y = getRandomFloat(0.4,0.6);
		b.velocity.x = getRandomFloat(-0.0001,0.0001);
		b.velocity.y = getRandomFloat(-0.0001,0.0001);
		b.color.r = getRandomFloat(0,1);
		b.color.g = getRandomFloat(0,1);
		b.color.b = getRandomFloat(0,1);
		b.mass = getRandomFloat(1,100);
		b.collided = false;
		
		bodies.push_back(b);
	}
	
	// Set up the code for the vertex shader
	float quadVertices[] = {
        // positions   
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,

        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };
	
	GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	
	// Load and compile shaders
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "sim.vert");
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "pixel.frag");
	GLuint computeShader = loadShader(GL_COMPUTE_SHADER,"Simulation.shader");
	
	// Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	
	// Create a program for the compute shader
	GLuint computeProgram = glCreateProgram();
	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);
	glDeleteShader(computeProgram);
	
	//Apply N Bodies to GPU memory
	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	Set_SSBO_Buffer(bodies,ssbo,0);
	
	// Render loop
	glUseProgram(shaderProgram);
	GLint bodyCountLocation = glGetUniformLocation(shaderProgram, "bodyCount");
	glUniform1i(bodyCountLocation, (int)bodies.size());
	print((int)bodies.size());
	
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
        // Draw the quad
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
		
		//Do the physics simulation
		glUseProgram(computeProgram);
		glDispatchCompute(bodies.size(),1,1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }
	
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
	return 0;
}

GLuint loadShader(GLenum type, const char* shaderPath) {
    // Retrieve the source code from filePath
    std::string shaderCode = GetShaderCode(shaderPath);
    const char* shaderCodeCStr = shaderCode.c_str();

    // Compile the shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCodeCStr, NULL);
    glCompileShader(shader);

    // Check for compile errors
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << shaderPath << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    return shader;
}