
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GL_LOG_FILE "gl.log"
#include <iostream>
#include "gl_utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow *g_window = NULL;

GLuint shader_programme;

float posX = -0.1f, posY = -0.14f;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void translate_item(float transf_x);

int main() {
	restart_gl_log();
	start_gl("Space Invaders");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture0coords
		0.1f,  -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // top right
		0.1f, -0.98f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // bottom right
		-0.1f, -0.98f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // bottom left
		-0.1f,  -0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	parse_file_into_str( "test_vs.glsl", vertex_shader, 1024 * 256 );
	parse_file_into_str( "test_fs.glsl", fragment_shader, 1024 * 256 );

	GLuint vs = glCreateShader( GL_VERTEX_SHADER );
	const GLchar *p = (const GLchar *)vertex_shader;
	glShaderSource( vs, 1, &p, NULL );
	glCompileShader( vs );

	// check for compile errors
	int params = -1;
	glGetShaderiv( vs, GL_COMPILE_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", vs );
		print_shader_info_log( vs );
		return 1; // or exit or something
	}

	GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
	p = (const GLchar *)fragment_shader;
	glShaderSource( fs, 1, &p, NULL );
	glCompileShader( fs );

	// check for compile errors
	glGetShaderiv( fs, GL_COMPILE_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", fs );
		print_shader_info_log( fs );
		return 1; // or exit or something
	}
	shader_programme = glCreateProgram();
	glAttachShader( shader_programme, fs );
	glAttachShader( shader_programme, vs );
	glLinkProgram( shader_programme );

	glGetProgramiv( shader_programme, GL_LINK_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: could not link shader programme GL index %i\n",
						 shader_programme );
		print_programme_info_log( shader_programme );
		return false;
	}

	// load and create a texture
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	//stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("spaceshuttle1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glEnable( GL_CULL_FACE ); // cull face
	glCullFace( GL_BACK );		// cull back face
	glFrontFace( GL_CW );			// GL_CCW for counter clock-wise

	

	while ( !glfwWindowShouldClose( g_window ) ) {

		glfwSetKeyCallback(g_window, key_callback);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glViewport(0, 0, g_gl_width, g_gl_height);

		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram( shader_programme );

		glBindVertexArray( VAO );
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwPollEvents();

		glfwSwapBuffers(g_window);
	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_LEFT && action != GLFW_RELEASE && posX >=-0.9f) {
		posX -= 0.1f;
		translate_item(posX);
	}

	else if (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE && posX <= 0.9f) {
		posX += 0.1f;
		translate_item(posX);
	}

	else if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(g_window, 1);
	}
	
	else if (key == GLFW_KEY_SPACE && action != GLFW_PRESS) {
		
		while (posY <= 1.1f) {
			
		}
	};
};

void translate_item(float transf_x) {
	glm::mat4 transform;

	transform = glm::translate(transform, glm::vec3(transf_x, 0.0f, 0.0f));

	unsigned int transformLoc = glGetUniformLocation(shader_programme, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
};


