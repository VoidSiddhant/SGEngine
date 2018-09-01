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

enum class SGEngine::Shader_Uniform : SG_UINT
{
	MATRIX_MVP,
	VEC4_COLOR,
	VEC3_POS
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
		//Simple Shader material
        simpleShader = SG_MAKEPTRS<Shader>("Simple", "./Shader/vertex.vs", "./Shader/color.frag");
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_COLOR, VT_FLOAT_VEC4), "color", 4);

		mat1 = SG_MAKEPTRS<SGMaterial>("Material1");

		//Uniform_Shader
		uniform_shader = SG_MAKEPTRS<Shader>("Uniform_shader", "./Shader/vertex.vs", "./Shader/color_uniform.frag");
		uniform_shader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
		uniform_shader->AddVariable(ShaderUniform(Shader_Uniform::VEC4_COLOR, UT_FLOAT_VEC4), "inColor", 4);
		
		mat2 = SG_MAKEPTRS<SGMaterial>("Material2");
		mat2->SetShader(uniform_shader);
		mat1->SetShader(uniform_shader);
		//Triangle GameObject
		SGShapes::instance().Triangle2D(SGVector4(1.0f, 0.0f, 0.0f, 1.0f), m);
		triangle = new SGGameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), "Triangle");
		SGComponent* triangleRender = new SGMeshRenderer(m,mat1);
		triangle->AddComponent(triangleRender);

		//Square GameObject
		square = new SGGameObject(SGVector3(0.0f, 0.0f, 0.0f), SGVector3(0.0f, 0.0f, 0.0f), "Square");
		SGShapes::instance().Quad2D(SGVector4(0.0f, 1.0f, 0.0f, 1.0f), s);
		SGComponent* squareRender = new SGMeshRenderer(s,mat2);
		square->AddComponent(squareRender);

	}

    void Update(float dt)
    {
        float greenValue = (sin(SGTimer::instance().GetTotalTime()) / 2.0f) + 0.5f;
		SGVector4 color{ 0.0f,greenValue,0.0f,1.0f };
		SGMaterialManager::instance().SetUniform(mat2->GetUUID(),Shader_Uniform::VEC4_COLOR, color);

		if (Input::instance().GetKeyDown(GLFW_KEY_SPACE))
		{
			mat1->SetShader(simpleShader);
			SGMeshRenderer* r = static_cast<SGMeshRenderer*>(triangle->GetComponent("Component_MeshRenderer"));
			r->UpdateMaterial();
		}
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
    SG_PTRS<Shader> simpleShader , uniform_shader;
	SG_PTRS<SGMaterial> mat1;
	SG_PTRS<SGMaterial> mat2;
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
