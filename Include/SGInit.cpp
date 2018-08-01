#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>
#include "SGUtil.h"

GLFWwindow *mainWindow;
unsigned int VAO, VBO, shader, uniformModel;

void EngineDispose(void);
//Internal Shader defination
static const char *vShader = "\n\
    #version 450 core \n\
    layout (location = 0) in vec3 pos;\n\
    uniform mat4 model; \n\
    void main()\n\
    {\n\
      gl_Position = vec4(0.4*pos.x,0.4*pos.y,pos.z,1.0);\n\
    }\n\
";

static const char *fShader = "\n\
    #version 450 core \n\
    out vec4 color; \n\
    void main() \n\
    {\n\
      color = vec4(1.0,1.0,0.0,1.0);\n\
    }\n\
";

void AddShader(unsigned int* theProgram, const char *shaderCode, GLenum shaderType)
{
  std::cout << "The program : " << *theProgram<<std::endl;
  // creates an empty shader object of type shaderType , ready to accept the compiled shader
  unsigned int theShader = glCreateShader(shaderType);
  const char* s[1];
  s[0] = shaderCode;
  int codeLength[1];
  codeLength[0] = strlen(shaderCode);
  //  set shader source info and compile to the empty object - shader
  glShaderSource(theShader, 1, s, codeLength);
  glCompileShader(theShader);

  int result = 0;
  char *eLog[1024] = {0};
  //  Debug compiled shader object
  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    glGetShaderInfoLog(theShader, sizeof(eLog), NULL, (GLchar *)eLog);
    std::cout << "Error Linking Shader of type : " << shaderType << eLog;
    return;
  }
  //  Attach compiled shader to the program object
  glAttachShader(*theProgram, theShader);
    std::cout << "The program Attached : " << *theProgram<<std::endl;
  // Delete shader binary from memory
  glDeleteShader(theShader);
}

void CompileShader()
{
  std::cout << shader << std::endl;
  //  Create program object to attach shaders.
  shader = glCreateProgram();
  std::cout << shader << std::endl;

  if (!shader)
  {
    std::cout << "Error creating shader program\n";
    return;
  }

  AddShader(&shader, vShader, GL_VERTEX_SHADER);
  std::cout << shader << std::endl;
  AddShader(&shader, fShader, GL_FRAGMENT_SHADER);
  std::cout << shader << std::endl;

  int result = 0;
  char eLog[1024] = {0};
  //  Link the program object
  glLinkProgram(shader);

  //  Debug program object
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    std::cout << "Error linking program: " << eLog;
    return;
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, (GLchar *)eLog);
    std::cout << "Error validating program: " << eLog;
    return;
  }
  std::cout << shader << std::endl;
}

void CreateTriangle()
{
  float vertices[] = {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f, 1.0f, 0.0f};

  //Creating 1 array and storing its id in VAOglGenVertexArrays
  glCreateVertexArrays(1, &VAO);
  //Make the vertex array object created above as the current object
  glBindVertexArray(VAO);

  //Same process for the buffer object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

int InitExtensions()
{
  //Initialise GLFW
  if (!glfwInit())
  {
    std::cout << "GLFW Init Failed\n";
    glfwTerminate();
    return SG_UTIL_ERROR_CRITICAL;
  }

  //Setup GLFW window properties
  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SG_GLFW_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SG_GLFW_VERSION_MINOR);
  // Set profile to core = no backward compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Set forward compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  mainWindow = glfwCreateWindow(SG_UTIL_SCREEN_WIDTH, SG_UTIL_SCREEN_HEIGHT, "Test Window", NULL, NULL);
  if (!mainWindow)
  {
    std::cout << "GLFW Window Creation Failed\n";
    glfwTerminate();
    return SG_UTIL_ERROR_CRITICAL;
  }

  //Get Frame Buffer size Information
  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  //Set the window the Context will be used on
  glfwMakeContextCurrent(mainWindow);

  //Allow modern Extensions to work
  glewExperimental = GL_TRUE;
  //Init GLEW

  if (glewInit() != GLEW_OK)
  {
    std::cout << "GLEW INIT FAILED!!!" << std::endl;
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return SG_UTIL_ERROR_CRITICAL;
  }

  //Set up Viewport Size
  glViewport(0, 0, bufferWidth, bufferHeight);
  return 0;
}

int main()
{
  if (InitExtensions() == SG_UTIL_ERROR_CRITICAL)
  {
    return 1;
  }
  CreateTriangle();
  CompileShader();
  float move = 0.0f;

  float moveDir = 1.0f;
  //Game Loop
  while (!glfwWindowShouldClose(mainWindow))
  {
    //Get Input Handle
    glfwPollEvents();
    //Clear Window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);

    move += 0.0001f * moveDir;
    if (abs(move) >= 0.7f)
    {
      moveDir *= -1.0f;
    }
    glm::mat4 model;
    //glUniform1f(glGetUniformLocation(shader, "model"), move);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    //model = glm::rotate(model, 45.0f * SG_UTIL_MATH_TORAD, glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //Present the back buffer
    glfwSwapBuffers(mainWindow);
  }

  EngineDispose();
  return 0;
}

void EngineDispose()
{
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteProgram(shader);
}