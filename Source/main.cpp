#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "ShaderManager.h"
#include "Vector.h"
#include "PrimitiveShapes.h"

using namespace SGEngine;
// Forward declaration
enum class SGEngine::Shader_Semantic : SG_UINT
{
    SEMANTIC_POSTION ,
    SEMANTIC_COLOR,
    SEMANTIC_TEXCOORD
};

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

        //SGShapes::instance().Quad2D(SGVector4(0.0f, 1.0f, 0.0f, 1.0f), s);
        //square = new GameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), s);

        simple = new Shader("Simple", "./Shader/vertex.vs", "./Shader/color.frag");
        simple->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
        simple->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_COLOR, VT_FLOAT_VEC4), "color", 4);

        SGShaderManager::instance().Create(*simple);
		SGShaderManager::instance().EnableProgram("Simple");
        SGShaderManager::instance().BindVAO();
        SGShaderManager::instance().EnableAttribute(Shader_Semantic::SEMANTIC_POSTION, sizeof(Vertex), 0, false);
        SGShaderManager::instance().EnableAttribute(Shader_Semantic::SEMANTIC_COLOR, sizeof(Vertex), sizeof(SGVector3));
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
		SGShaderManager::instance().EnableProgram("Simple");
		SGShaderManager::instance().BindVAO();
        triangle->render();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // TODO ABSTRACTION
        glfwSwapBuffers(mainWindow);
    }

    void ApplicationDispose()
    {
        delete triangle, simple;
    }

    ~Application()
    {
    }

  private:
    SG_UINT vbo, vao, ebo;
    Shader *simple;
    GameObject *triangle, *square;

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
