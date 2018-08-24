#include "Core.h"
#include "Input.h"
#include "Timer.h"

namespace SGEngine
{
    SGCore *SGCore::_instance = nullptr;
    SGCore::SGCore()
    {
    }

    SGCore &SGCore::instance()
    {
        if (_instance == nullptr)
            std::cout << "Instance not Found\n";
        return *_instance;
    }
    int SGCore::InitEngine()
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
        glfwSetKeyCallback(mainWindow, ProcessInput);
        //Set up Viewport Size
        glViewport(0, 0, bufferWidth, bufferHeight);
        return 0;
    }

    int SGCore::run()
    {
        Start();
        while (!glfwWindowShouldClose(mainWindow))
        {
            glfwPollEvents();
            SGTimer::instance().Tick();
            this->Update(SGTimer::instance().GetDeltaTime());
            this->Render();
            Input::instance().ClearLastFrameKey();
        }

        return this->EngineDispose();
    }

    void SGCore::HandleInput(GLFWwindow *wnd, int key, int action)
    {
        switch (action)
        {
        case GLFW_PRESS:
            Input::instance().SetKeyDown(key);
            break;

        case GLFW_RELEASE:
            Input::instance().SetKeyUp(key);
            break;
        }
    }

    int SGCore::EngineDispose()
    {
        this->ApplicationDispose();
        glfwTerminate();
        return 0;
    }

    SGCore::~SGCore()
    {
        std::cout << "Exit Call\n";
    }
} // namespace SGEngine

void ProcessInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    SGEngine::SGCore::instance().HandleInput(window, key, action);
}
