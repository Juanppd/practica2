#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 900, HEIGHT = 700;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificación de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//0.5f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		//0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		//-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 
		//triangulo 1  
		-0.2f, 0.05f, 0.0f,    0.117f, 0.117f, 0.662f,  //A  0
		 0.2f, 0.05f, 0.0f,	   0.117f, 0.117f, 0.662f,  //D  1
		-0.0f,  0.7f, 0.0f,    0.117f, 0.117f, 0.662f,  //C  2
		//pentagono 
		-0.2f,   0.0f,  0.0f,   0.435f, 0.435f, 0.623f, //d 3
		0.2f,   0.0f, 0.0f,    0.435f, 0.435f, 0.623f, //E 4
		0.4f, -0.4f, 0.0f,    0.2f, 0.992f, 1f,     //F 5
		-0.65f, 0.0f, 0.0f,    0.2f, 0.992f, 1f,    //G  6
		-0.4f, -0.4f, 0.0f,   0.2f, 0.992f, 1f,         //H 7

		//hexagono
		-0.6f,  -0.2f, 0.0f,   0.929f, 0.192f, 0.560f,  //H   7
		-1.0f,  -0.6f, 0.0f,   0.929f, 0.192f, 0.560f,//I    8
		-0.8f,  -1.0f, 0.0f,   0.929f, 0.192f, 0.560f,//J   9
		-0.4f,  -1.0f, 0.0f,    0.929f, 0.192f, 0.560f,//k   10  
		-0.2f,  -0.6f, 0.0f,   0.929f, 0.192f, 0.560f,//L    11
        //rombo 
		0.6f, -0.2f, 0.0f,    0.929f, 0.192f, 0.243f,//M   12
		0.2f,  -0.6f, 0.0f,   0.929f, 0.192f, 0.243f,//N    13
		0.6f,  0. - 1.0f, 0.0f, 0.929f, 0.192f, 0.243f,//p  14
		1.0f, -0.6f, 0.0f,    0.929f, 0.192f, 0.243f,//0    15 
		

	};
	unsigned int indices[] = {  // note that we start from 0!
		0,1,2,3,// Trapecio
		4,5,6,  //triangulo 
		7,8,9,10,11,//hexagono
		12,13,14,15,//rombo 
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.925f, 0.854f, 0.858f,0.f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));//trapecio  //numero de indices e indice en el que va a comenzar 
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(4 * sizeof(GLfloat)));//triangulo 
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (GLvoid*)(7 * sizeof(GLfloat)));//hexagono 
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (GLvoid*)(12 * sizeof(GLfloat)));//rombo 


	
		
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}