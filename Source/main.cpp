#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Shader.h"
#include "Vector.h"
#include "PrimitiveShapes.h"

using namespace SGEngine;

class Application : public SGCore
{
  public:
    static void Create()
    {
        if (_instance == NULL)
            _instance = new Application();
        else
            std::cout << "Instance Already Exist\n";
    }

    void Start()
    {
        // ABSTRACTION FOR THE WIN
        Mesh m, s;
        SGShapes::instance().Triangle2D(SGVector4(1.0f, 0.0f, 0.0f, 1.0f), m);
        triangle = new GameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), m);

        SGShapes::instance().Quad2D(SGVector4(0.0f, 1.0f, 0.0f, 1.0f), s);
        square = new GameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), s);

        simple = new Shader("Simple","./Shader/vertex.vs", "./Shader/color.frag");
        simple->AddVariable(ShaderAttribute(Position,AT_FLOAT_VEC3), "lPos");
        simple->AddVariable(ShaderAttribute(Color,AT_FLOAT_VEC4), "color");
        simple->Use();
    }

    void Update(float dt)
    {
        float greenValue = (sin(SGTimer::instance().GetTotalTime()) / 2.0f) + 0.5f;
        float s;
    }

    void Render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        square->render();
        //simple->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(mainWindow);
    }

    void ApplicationDispose()
    {
        delete triangle,square,simple;
    }

    ~Application()
    {
    }

  private:
    SG_UINT vbo, vao, ebo;
    Shader *simple;
    GameObject *triangle, *square;
    //Noobness
    Application()
    {
    }
};

int main()
{
    Application::Create();
    Application::instance().InitEngine();
    return Application::instance().run();
}
