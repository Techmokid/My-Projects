#ifndef COMPILER_FUNCTIONS_LIST    // To make sure you don't declare the function more than once by including the header multiple times.
#define COMPILER_FUNCTIONS_LIST

#include <iostream>		// Required for User I/O operations
#include <string.h>
#include <cstring>
#include <chrono>			// Required for time keeping and timeout periods
#include <stdlib.h>		// Required to clear the console
#include <vector>			// Required for dynamic sized arrays (Effectively lists)
#include <math.h>			// Required for math floor function
#include <stdexcept>	// Required for error handling
#include <thread>			// Required to allow for CPU multithreading
#include <fstream>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#ifdef _WIN32
#include <winsock2.h>	// Required for server socket connections
#include <windows.h>	// Required for console text colour editing
#else
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

// Multiple variants of saying "Stop program" so I don't have to think which I used
//#define quit() 			waitForUserInput();return 0;
//#define end() 			waitForUserInput();return 0;
//#define stop() 			waitForUserInput();return 0;
//#define quitProgram() 	waitForUserInput();return 0;
//#define endProgram() 	waitForUserInput();return 0;
//#define stopProgram() 	waitForUserInput();return 0;





GLuint loadShader(GLenum type, const char* shaderPath);





// Helper_Functions.cpp
void ClearConsole();
void print();
void print(int x);
void print(float x);
void print(double x);
void print(long unsigned int x);
void print(std::string x);
void printFormatted(std::string module, std::string status, std::string msg);
void printSuccess(std::string module, std::string msg);
void printError(std::string module, std::string msg);
void printLog(std::string module, std::string msg);
void printInfo(std::string module, std::string msg);
void printDebug(std::string module, std::string msg);
void SetConsoleColor(int colour);
std::string TimeFormatter(double x);
std::string DataSizeFormatter(unsigned long long int x);
void waitForUserInput();
std::string stringToLower(std::string in);
std::string stringToLowerCapitalized(std::string in);
std::string stringToUpper(std::string in);
std::vector<std::string> SplitString(std::string inputVal, char delimiter);
std::string ASCII_To_Numeric(std::string x);
std::string RemoveSpecificCharacter(std::string x, char delim);
std::string expandEnvironmentVariables(const std::string& inputPath);
void quit();
void delay(unsigned int t);
void SetWallpaper(std::string path);

void _checkSeeded();
float getRandomFloat();
float getRandomFloat(float HI);
float getRandomFloat(float HI, float LO);





//OpenGL_Interface.cpp
GLFWwindow* GetCurrentActiveWindow();
std::string GetShaderCode(std::string shaderPath);
static void error_callback(int error, const char* description);
void WriteChangesToScreen();
void StartWindow(bool hideWindow);
void StartWindow(int w, int h);
void StartWindow(bool hideWindow, int w, int h);
GLuint CompileShader(std::string computeShaderCode);
GLuint CompileShader(const char* computeShaderSource);
GLuint StartShaderProgram(GLuint computeShader);
GLuint StartShaderProgram(GLuint computeShader, std::vector<GLuint*> ssbo);
GLuint InitializeShader(std::string shaderPath);
void checkShaderCompileStatus(GLuint shader);
void ShutDownOpenGL();





template<typename T>
void Set_SSBO_Buffer(std::vector<T> &obj, GLuint ssbo, int buffer_index) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, obj.size() * sizeof(T), obj.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, buffer_index, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Set_SSBO_Buffer(T &obj, GLuint ssbo, int buffer_index) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T), &obj, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, buffer_index, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Set_SSBO_Buffer(T obj, GLuint ssbo, int buffer_index) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T), &obj, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, buffer_index, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Get_SSBO_Buffer(std::vector<T> &obj, GLuint ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, obj.size() * sizeof(T), obj.data());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Get_SSBO_Buffer(T &obj, GLuint ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(T), obj.data());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Edit_SSBO_Buffer(std::vector<T> &obj, GLuint ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, obj.size() * sizeof(T), obj.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Edit_SSBO_Buffer(T &obj, GLuint ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, obj.size() * sizeof(T), obj.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

template<typename T>
void Edit_SSBO_Buffer(T obj, GLuint ssbo) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(T), &obj);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

#endif