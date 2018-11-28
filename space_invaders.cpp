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

struct Sprite
{
    size_t width, height;
    uint8_t* data;
};

struct Alien
{
    size_t x, y;
    uint8_t type;
};

struct Player
{
    size_t x, y;
    size_t life;
};

struct Game
{
    size_t width, height;
    size_t num_aliens;
    Alien* aliens;
    Player player;
};

struct SpriteAnimation
{
    bool loop;
    size_t num_frames;
    size_t frame_duration;
    size_t time;
    Sprite** frames;
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
void buffer_sprite_draw(
        Buffer* buffer, const Sprite& sprite,
        size_t x, size_t y, uint32_t color
);
void buffer_draw_number(
        Buffer* buffer,
        const Sprite& number_spritesheet, size_t number,
        size_t x, size_t y,
        uint32_t color);
void buffer_draw_text(
        Buffer* buffer,
        const Sprite& text_spritesheet,
        const char* text,
        size_t x, size_t y,
        uint32_t color);

void movePlayerLeft();

void movePlayerRight();

static int width = 800, height = 600;
float x;
float y;

Game game;

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

    size_t buffer_width = 500;
    size_t buffer_height = 300;

    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Buffer buffer;
    buffer.width  = buffer_width;
    buffer.height = buffer_height;
    buffer.data   = new uint32_t[buffer.width * buffer.height];
    buffer_clear(&buffer, clear_color);

    GLuint vao, buffer_texture;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenTextures(1, &buffer_texture);
    glBindTexture(GL_TEXTURE_2D, buffer_texture);
    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGB8,
            buffer.width, buffer.height, 0,
            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer.data
    );

    Sprite alien_sprite0;
    alien_sprite0.width = 11;
    alien_sprite0.height = 8;
    alien_sprite0.data = new uint8_t[11 * 8]
            {
                    0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
                    0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
                    0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
                    0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
                    1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
                    1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
                    1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
                    0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
            };

    Sprite alien_sprite1;
    alien_sprite1.width = 11;
    alien_sprite1.height = 8;
    alien_sprite1.data = new uint8_t[88]
            {
                    0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
                    1,0,0,1,0,0,0,1,0,0,1, // @..@...@..@
                    1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
                    1,1,1,0,1,1,1,0,1,1,1, // @@@.@@@.@@@
                    1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
                    0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
                    0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
                    0,1,0,0,0,0,0,0,0,1,0  // .@.......@.
            };

    Sprite player_sprite;
    player_sprite.width = 11;
    player_sprite.height = 7;
    player_sprite.data = new uint8_t[77]
            {
                    0,0,0,0,0,1,0,0,0,0,0, // .....@.....
                    0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
                    0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
                    0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
                    1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
                    1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
                    1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
            };

    game.width = 200;
    game.height = buffer_height;
    game.num_aliens = 55;
    game.aliens = new Alien[game.num_aliens];

    game.player.x = 112 - 5;
    game.player.y = 32;

    game.player.life = 3;

    SpriteAnimation* alien_animation = new SpriteAnimation;

    alien_animation->loop = true;
    alien_animation->num_frames = 2;
    alien_animation->frame_duration = 10;
    alien_animation->time = 0;

    alien_animation->frames = new Sprite*[2];
    alien_animation->frames[0] = &alien_sprite0;
    alien_animation->frames[1] = &alien_sprite1;

    size_t score = 0;

  //  score += 10 * (4 - game.aliens[ai].type);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLint result;
    GLchar infoLog[512];

    char vertex_shader[800 * 600];
    parse_file_into_str("../shaders/vs.glsl", vertex_shader, 1024 * 256);
    GLuint vs = compileVertexShader(vertex_shader);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
    validateVertexShader(vs, result, infoLog);

    char fragment_shader[800 * 600];
    parse_file_into_str("../shaders/fs.glsl", fragment_shader, 1024 * 256);
    GLuint fs = compileFragmentShader(fragment_shader);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
    validateFragmentShader(fs,result,infoLog);

    GLuint shader_id = prepareShaderProgram(vs, fs, result, infoLog);

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

    GLuint vbo, ibo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_blue), indices_blue, GL_STATIC_DRAW);


    GLuint blueShaderProgram = prepareShaderProgram(vs, fs, result, infoLog);
    glDeleteShader(fs);

    glDeleteShader(vs);

    glfwSwapInterval(1);
    glClearColor(1.0, 0.0, 1.0, 1.0);
    // Rendering loop
    while (!glfwWindowShouldClose(g_window)) {
        showFPS(g_window);

        // Poll for and process events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        for(size_t yi = 0; yi < 5; ++yi)
        {
            for(size_t xi = 0; xi < 11; ++xi)
            {
                game.aliens[yi * 11 + xi].x = 16 * xi + 20;
                game.aliens[yi * 11 + xi].y = 17 * yi + 128;
            }
        }

        for(size_t ai = 0; ai < game.num_aliens; ++ai)
        {
            const Alien& alien = game.aliens[ai];
            size_t current_frame = alien_animation->time / alien_animation->frame_duration;
            const Sprite& sprite = *alien_animation->frames[current_frame];
            buffer_sprite_draw(&buffer, sprite, alien.x, alien.y, rgb_to_uint32(128, 0, 0));
        }

        buffer_sprite_draw(&buffer, player_sprite, game.player.x, game.player.y, rgb_to_uint32(128, 0, 0));

        glTexSubImage2D(
                GL_TEXTURE_2D, 0, 0, 0,
                buffer.width, buffer.height,
                GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
                buffer.data
        );

        // Render the quad (two triangles)
        drawVaoFromProgram(vao, blueShaderProgram);

        // Swap front and back buffers
        glfwSwapBuffers(g_window);

        ++alien_animation->time;
        if(alien_animation->time == alien_animation->num_frames * alien_animation->frame_duration)
        {
            if(alien_animation->loop) alien_animation->time = 0;
            else
            {
                delete alien_animation;
                alien_animation = nullptr;
            }
        }

//        buffer_clear(&buffer, clear_color);
//
//        buffer_draw_text(
//                &buffer,
//                text_spritesheet, "SCORE",
//                4, game.height - text_spritesheet.height - 7,
//                rgb_to_uint32(128, 0, 0)
//        );
//
//        buffer_draw_number(
//                &buffer,
//                number_spritesheet, score,
//                4 + 2 * number_spritesheet.width, game.height - 2 * number_spritesheet.height - 12,
//                rgb_to_uint32(128, 0, 0)
//        );
//
//        buffer_draw_text(
//                &buffer,
//                text_spritesheet, "CREDIT 00",
//                164, 7,
//                rgb_to_uint32(128, 0, 0)
//        );
//
//        for(size_t i = 0; i < game.width; ++i)
//        {
//            buffer.data[game.width * 16 + i] = rgb_to_uint32(128, 0, 0);
//        }
    }

    // Clean up
    glDeleteProgram(blueShaderProgram);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

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
            movePlayerLeft();
            printf("x = %.2f\n",x);
            break;
        case GLFW_KEY_S:
            y = y - 0.1;
            printf("y = %.2f\n",y);
            break;
        case GLFW_KEY_D:
            x = x + 0.1;
            movePlayerRight();
            printf("x = %.2f\n",x);
            break;
        default:
            break;
    }
}

void movePlayerRight() {
    if(game.player.x + 11 <= game.width - 1) {
        game.player.x += 1;
    }
}

void movePlayerLeft() {
    if((int)game.player.x >= 0) {
        game.player.x -= 1;
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

void buffer_sprite_draw(
        Buffer* buffer, const Sprite& sprite,
        size_t x, size_t y, uint32_t color
){
    for(size_t xi = 0; xi < sprite.width; ++xi)
    {
        for(size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if(sprite.data[yi * sprite.width + xi] &&
               sy < buffer->height && sx < buffer->width)
            {
                buffer->data[sy * buffer->width + sx] = color;
            }
        }
    }
}

void buffer_draw_text(
        Buffer* buffer,
        const Sprite& text_spritesheet,
        const char* text,
        size_t x, size_t y,
        uint32_t color)
{
    size_t xp = x;
    size_t stride = text_spritesheet.width * text_spritesheet.height;
    Sprite sprite = text_spritesheet;
    for(const char* charp = text; *charp != '\0'; ++charp)
    {
        char character = *charp - 32;
        if(character < 0 || character >= 65) continue;

        sprite.data = text_spritesheet.data + character * stride;
        buffer_sprite_draw(buffer, sprite, xp, y, color);
        xp += sprite.width + 1;
    }
}

void buffer_draw_number(
        Buffer* buffer,
        const Sprite& number_spritesheet, size_t number,
        size_t x, size_t y,
        uint32_t color)
{
    uint8_t digits[64];
    size_t num_digits = 0;

    size_t current_number = number;
    do
    {
        digits[num_digits++] = current_number % 10;
        current_number = current_number / 10;
    }
    while(current_number > 0);

    size_t xp = x;
    size_t stride = number_spritesheet.width * number_spritesheet.height;
    Sprite sprite = number_spritesheet;
    for(size_t i = 0; i < num_digits; ++i)
    {
        uint8_t digit = digits[num_digits - i - 1];
        sprite.data = number_spritesheet.data + digit * stride;
        buffer_sprite_draw(buffer, sprite, xp, y, color);
        xp += sprite.width + 1;
    }
}