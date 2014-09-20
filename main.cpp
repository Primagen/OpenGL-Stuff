
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>

const int ScreenWidth  = 800;
const int ScreenHeight = 600;

bool init_GLFW_and_GLEW(GLFWwindow* &window)
{
    if(!glfwInit()) {
        std::cout << "Error loading GLFW, driver may not support " << GL_VERSION << std::endl;
        return false;
    } else {
        std::cout << "GLFW initialized. OpenGL "<< GL_VERSION << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Hello OpenGL + GLFW + GLEW", NULL, NULL);
	if(window == NULL){
		std::cout << "Failed to open GLFW window. " <<
		             "If you have an Intel GPU, they may not be 3.3+ compatible. " << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW." << std::endl;
		return false;
	}

	// Ensure we can capture the escape key being pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	return true;
}

void mainLoop(GLFWwindow* window)
{
	do {
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//glFlush();
		// Swap buffers
		glfwSwapBuffers(window);

		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    std::cout << "Terminating GLFW..." << std::endl;
	glfwTerminate();
}

int main()
{
    GLFWwindow* window;
    if (!init_GLFW_and_GLEW(window))
        return 1;

    mainLoop(window);
    return 0;
}
