#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == false)
    {
        int length = 512;
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, NULL, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader !" << std::endl;
        std::cout <<  std::hex << message << std::endl;

        // GLint infolog_length;
        // glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infolog_length);

        // GLchar infolog = new GLchar[infolog_length+1];
        // glGetShaderInfoLog(id, infolog_length, NULL, infolog.ptr);

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs); 
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    // glfwWindowHint(GLFW_VERSION_MAJOR, 1);
    // glfwWindowHint(GLFW_VERSION_MINOR, 2);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << glewInit();

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f, 
         0.5f, -0.5f 
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    std::string vertexShader = 
        "#version 120\n"
        "\n"
        "attribute vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragmentShader = 
        "#version 120\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}