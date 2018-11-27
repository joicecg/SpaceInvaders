/*
"Hello Triangle". Just the basics + shaders + 2 buffers
Novelty:
Adds index buffer (Element Array Buffer)
*/

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdint>

#include <utils/gl_utils.h> // parser for shader source files

struct Buffer
{
    size_t width, height;
    uint32_t* data;
};

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void reshape_callback(GLFWwindow *window, int width, int height);
void showFPS(GLFWwindow *window);
void validateVertexShader(GLuint vs, GLint result, GLchar *infoLog);
void validateFragmentShader(GLuint fs, GLint result, GLchar *infoLog);
void validateProgram(GLuint program, GLint result, GLchar *infoLog);
void validateElement(GLuint element, GLint result, GLchar *infoLog, const GLchar *errorMessage);
GLuint compileFragmentShader(const char *shader);
GLuint compileVertexShader(const char *shader);
void attachShadersToShaderProgram(GLuint vs, GLuint fs, GLuint shaderProgram);
GLuint prepareShaderProgram(GLuint vs, GLuint fs, GLint &result, GLchar *infoLog);
GLuint compileShader(const char *shader, GLuint resultShader);
void drawVaoFromProgram(GLuint vao, GLuint shaderProgram);
uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b);
void buffer_clear(Buffer* buffer, uint32_t color);

static int width = 800, height = 600;
float x;
float y;

int main() {

    GLFWwindow *g_window;

    if (!glfwInit())
        return -1;

    #ifdef __linux__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    g_window = glfwCreateWindow(width, height, "Space Invaders", NULL, NULL);
    if (!g_window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g_window);
    glfwSetKeyCallback(g_window, key_callback);
    glfwSetFramebufferSizeCallback(g_window, reshape_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return 0;
    }

    size_t buffer_width = 800;
    size_t buffer_height = 600;

    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Buffer buffer;
    buffer.width  = buffer_width;
    buffer.height = buffer_height;
    buffer.data   = new uint32_t[buffer.width * buffer.height];
    buffer_clear(&buffer, clear_color);

    GLuint shader_id = 0;

    GLint location = glGetUniformLocation(shader_id, "dbuffer");
    glUniform1i(location, 0);


    GLfloat vertices[] = {
            -0.5f, 0.5f, 0.0f,        // Top left
            0.5f, 0.5f, 0.0f,        // Top right
            0.5f, -0.5f, 0.0f,        // Bottom right
            -0.5f, -0.5f, 0.0f        // Bottom left
    };

    GLuint indices_blue[] = {
            0, 1, 2,  // First Triangle
            0, 2, 3  // Second Triangle
    };


    GLuint vbo_blue, ibo_blue, vao_blue;

    glGenBuffers(1, &vbo_blue);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_blue);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_blue);
    glBindVertexArray(vao_blue);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    //
    glGenBuffers(1, &ibo_blue);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_blue);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_blue), indices_blue, GL_STATIC_DRAW);

    GLint result;
    GLchar infoLog[512];

    char vertex_shader[1024 * 256];
    parse_file_into_str("../shaders/vs_uniform.glsl", vertex_shader, 1024 * 256);
    GLuint vs = compileVertexShader(vertex_shader);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
    validateVertexShader(vs, result, infoLog);

    char fragment_shader[1024 * 256];
    parse_file_into_str("../shaders/fs_uniform.glsl", fragment_shader, 1024 * 256);
    GLuint fs = compileFragmentShader(fragment_shader);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
    validateFragmentShader(fs,result,infoLog);
    GLuint blueShaderProgram = prepareShaderProgram(vs, fs, result, infoLog);
    glDeleteShader(fs);

    glDeleteShader(vs);

    glClearColor(1.0, 0.0, 1.0, 1.0);
    // Rendering loop
    while (!glfwWindowShouldClose(g_window)) {
        showFPS(g_window);

        // Poll for and process events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the quad (two triangles)
        drawVaoFromProgram(vao_blue, blueShaderProgram);

        // Swap front and back buffers
        glfwSwapBuffers(g_window);
    }

    // Clean up
    glDeleteProgram(blueShaderProgram);
    glDeleteVertexArrays(1, &vao_blue);
    glDeleteBuffers(1, &vbo_blue);
    glDeleteBuffers(1, &ibo_blue);

    glfwTerminate();

    return 0;
}

void drawVaoFromProgram(GLuint vao, GLuint shaderProgram) {
    glUseProgram(shaderProgram);

    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    float redValue = 1.0 - greenValue;
    glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);

    int xLocation = glGetUniformLocation(shaderProgram, "x");
    glUniform1f(xLocation, x);

    int yLocation = glGetUniformLocation(shaderProgram, "y");
    glUniform1f(yLocation, y);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

GLuint prepareShaderProgram(GLuint vs, GLuint fs, GLint &result, GLchar *infoLog) {
    GLuint shaderProgram = glCreateProgram();
    attachShadersToShaderProgram(vs, fs, shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    validateProgram(shaderProgram,result,infoLog);
    return shaderProgram;
}

void attachShadersToShaderProgram(GLuint vs, GLuint fs, GLuint shaderProgram) {
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
}

GLuint compileFragmentShader(const char *shader) {
    GLuint resultShader = glCreateShader(GL_FRAGMENT_SHADER);
    return compileShader(shader, resultShader);
}

GLuint compileVertexShader(const char *shader) {
    GLuint resultShader = glCreateShader(GL_VERTEX_SHADER);
    return compileShader(shader, resultShader);
}

GLuint compileShader(const char *shader, GLuint resultShader) {
    const GLchar *p = shader;
    glShaderSource(resultShader, 1, &p, NULL);
    glCompileShader(resultShader);
    return resultShader;
}

void validateVertexShader(GLuint vs, GLint result, GLchar *infoLog) {
    const GLchar *vertexShaderErrorMessage = "Error! Vertex shader failed to compile. ";
    validateElement(vs, result, infoLog, vertexShaderErrorMessage);
}

void validateFragmentShader(GLuint fs, GLint result, GLchar *infoLog) {
    const GLchar *fragmentShaderErrorMessage = "Error! Fragment shader failed to compile. ";
    validateElement(fs, result, infoLog, fragmentShaderErrorMessage);
}

void validateProgram(GLuint program, GLint result, GLchar *infoLog) {
    const GLchar *programErrorMessage = "Error! Program failed to compile. ";
    validateElement(program, result, infoLog, programErrorMessage);
}

void validateElement(GLuint element, GLint result, GLchar *infoLog, const GLchar *errorMessage) {
    if (!result) {
        glGetShaderInfoLog(element, sizeof(infoLog), NULL, infoLog);
        std::cout << errorMessage << infoLog << std::endl;
    }
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    static bool gWireframe = 0;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        gWireframe = !gWireframe;
        if (gWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    switch (key){
        case GLFW_KEY_W:
            y = y + 0.1;
            printf("y = %.2f\n",y);
            break;
        case GLFW_KEY_A:
            x = x - 0.1;
            printf("x = %.2f\n",x);
            break;
        case GLFW_KEY_S:
            y = y - 0.1;
            printf("y = %.2f\n",y);
            break;
        case GLFW_KEY_D:
            x = x + 0.1;
            printf("x = %.2f\n",x);
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void reshape_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow *window) {
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

    elapsedSeconds = currentSeconds - previousSeconds;

    // Limit text updates to 4 times per second
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        double fps = (double) frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        // The C++ way of setting the window title
        std::ostringstream outs;
        outs.precision(3);    // decimal places
        outs << std::fixed
             << "Space Invaders" << "    "
             << "FPS: " << fps << "    "
             << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());

        // Reset for next average.
        frameCount = 0;
    }

    frameCount++;
}

uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
{
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

void buffer_clear(Buffer* buffer, uint32_t color)
{
    for(size_t i = 0; i < buffer->width * buffer->height; ++i)
    {
        buffer->data[i] = color;
    }
}
