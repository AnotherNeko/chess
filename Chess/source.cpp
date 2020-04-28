#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DebugTools/Log.h";

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    enum class ShaderType : signed char
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            { //set mode to vertex
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            { //set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << std::endl;
        }
        
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); //returns null terminated c-string of source code for shader
    glShaderSource(id, 1, &src, nullptr /*null means string is null-terminated*/);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        LogError("failed to compile " + (std::string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader!");
        LogError(message);

        glDeleteShader(id);
        return (unsigned int)NAN;
    }
    
    //add error handling

    return(id);
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //cleanup intermediates
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    void LogInfo(const std::string & message);

    std::cout << glGetString(GL_VERSION) << std::endl;

    unsigned const static int count = 12;
    float positions[count] = {
            0.0f,  0.5f,
           -0.5f, -0.5f,
            0.5f, -0.5f,
            1.0f,  0.0f,
            0.9f,  0.0f,
            0.95f, -0.1f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0/*index*/, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderProgramSource sauce = ParseShader("Resources/shaders/Basic.shader");
    //LogInfo("Fragment Shader:");
    //LogInfo(sauce.FragmentSource);
    //LogInfo("Vertex Shader:");
    //LogInfo(sauce.VertexSource);


    unsigned int shader = CreateShader(sauce.VertexSource, sauce.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
    
}