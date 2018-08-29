#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "ShaderManager.h"
#include "Vector.h"
#include "PrimitiveShapes.h"
#include "GameObject.h"

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
		SGMeshFilter m, s;

        simpleShader = new Shader("Simple", "./Shader/vertex.vs", "./Shader/color.frag");
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_COLOR, VT_FLOAT_VEC4), "color", 4);
		
		//Triangle GameObject
		SGShapes::instance().Triangle2D(SGVector4(1.0f, 0.0f, 0.0f, 1.0f), m);
		triangle = new SGGameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), "Triangle");
		SGComponent* triangleRender = new SGMeshRenderer(m,simpleShader);
		triangle->AddComponent(triangleRender);

		//Square GameObject
		square = new SGGameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), "Square");
		SGShapes::instance().Quad2D(SGVector4(0.0f, 1.0f, 0.0f, 1.0f), s);
		SGComponent* squareRender = new SGMeshRenderer(s,simpleShader);
		square->AddComponent(squareRender);

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
		
		//SQUARE
		square->Render();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

		//TRIANGLE
        triangle->Render();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
		glfwSwapBuffers(mainWindow);
    }

    void ApplicationDispose()
    {
        delete triangle, simpleShader,square;
    }

    ~Application()
    {
    }  

  private:
    Shader *simpleShader;
    SGGameObject *triangle, *square;

    Application()
    {
    }
};

int APIENTRY main()
{
    Application::Create();
    Application::instance().InitEngine();
    return Application::instance().run();
}
