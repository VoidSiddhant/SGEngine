#include "SGUtil.h"
#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Vector.h"
#include "Camera.h"
#include "PrimitiveShapes.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Material.h"
#include "External/glm/gtc/type_ptr.hpp"

// Application Side
#include "Player.h"

using namespace SGEngine;
// Forward declaration
enum class SGEngine::Shader_Semantic : SG_UINT
{
    SEMANTIC_POSTION,
    SEMANTIC_COLOR,
    SEMANTIC_TEXCOORD
};

enum class SGEngine::Shader_Uniform : SG_UINT
{
	MATRIX_MVP,
	VEC4_COLOR,
	VEC3_POS,
	SAMPLE_TEX0,
	SAMPLE_TEX1,
	USE_TEX
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
		/******************************************************************************************************
		******************	CAMERA SETUP	***********************************************************
		*****************************************************************************************************/
		camera = SG_MAKEPTRS<SGCamera>(SGVector3(0.0f, 0.0f,-10.0f) , SGVector3(0.0f,0.0f,0.0f));		

		SGMeshFilter m, s;
		/****************************************************************************************************************
		******************************	SHADER SETUP ********************************************************************
		*****************************************************************************************************************/
		//Simple Shader material
        simpleShader = SG_MAKEPTRS<Shader>("Simple", "./Shader/vertex.vs", "./Shader/color.frag");
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
        simpleShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_COLOR, VT_FLOAT_VEC4), "color", 4);
		//Uniform_Shader
		uniform_shader = SG_MAKEPTRS<Shader>("Uniform_shader", "./Shader/vertex.vs", "./Shader/color_uniform.frag");
		uniform_shader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
		uniform_shader->AddVariable(ShaderUniform(Shader_Uniform::VEC4_COLOR, UT_FLOAT_VEC4), "inColor", 0);
		//Textured Shader
		texturedShader = SG_MAKEPTRS<Shader>("Textured", "./Shader/vertex_textured.vs", "./Shader/color_texture.frag");
		texturedShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_POSTION, VT_FLOAT_VEC3), "lPos", 3);
		texturedShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_COLOR, VT_FLOAT_VEC4), "color", 4);
		texturedShader->AddVariable(ShaderAttribute(Shader_Semantic::SEMANTIC_TEXCOORD, VT_FLOAT_VEC2), "texCoord", 2);
		texturedShader->AddVariable(ShaderUniform(Shader_Uniform::MATRIX_MVP, UT_FLOAT_MAT4), "WVP", 1);
		texturedShader->AddVariable(ShaderUniform(Shader_Uniform::SAMPLE_TEX0, UT_SAMPLER2D), "sample_tex0", 1);
		texturedShader->AddVariable(ShaderUniform(Shader_Uniform::SAMPLE_TEX1, UT_SAMPLER2D), "sample_tex1" , 1);
		texturedShader->AddVariable(ShaderUniform(Shader_Uniform::USE_TEX, UT_BOOL), "useTex" , 1);
		/****************************************************************************************************************
		******************************	Material SETUP ********************************************************************
		*****************************************************************************************************************/
		SGTexture wood_text("WoodTexture","./Textures/left.jpg");
		SGTexture cont_text("ContainerTexture", "./Textures/crate.jpg");
		mat1 = SG_MAKEPTRS<SGMaterial>("Material1");
		mat1->SetShader(texturedShader);
		//mat1->SetTexture("WoodTexture", 0);
		//mat1->SetTexture("ContainerTexture", 1);
		//*************			Texture Blending			      ********
		mat1->SetUniform(Shader_Uniform::SAMPLE_TEX0, 0);       //********
		mat1->SetUniform(Shader_Uniform::SAMPLE_TEX1, 1);		//********
		mat1->SetUniform(Shader_Uniform::USE_TEX, 1);
     	//****************************************************************
		mat2 = SG_MAKEPTRS<SGMaterial>("Material2");
		mat2->SetShader(uniform_shader);
	
		/****************************************************************************************************************
		******************************	GameObject SETUP ********************************************************************
		*****************************************************************************************************************/

		//Triangle GameObject
		SGShapes::instance().Cube(SGVector4(1.0f, 1.0f, 1.0f, 1.0f), m);
		SGComponent* triangleRender = new SGMeshRenderer(m,mat1);
		player.AddComponent(triangleRender);
	}

    void Update(float dt)
    {
		camera->UpdateView();
        float greenValue = (sin(SGTimer::instance().GetTotalTime()) / 2.0f) + 0.5f;
		SGVector4 color{ 0.0f,greenValue,0.0f,1.0f };
		mat2->SetUniform(Shader_Uniform::VEC4_COLOR, color);
		
	
		if (Input::instance().GetKey(GLFW_KEY_J))
			camera->transform.Rotate(SGVector3(0.0f, 10.0f * dt, 0.0f));
		else if (Input::instance().GetKey(GLFW_KEY_L))
			camera->transform.Rotate(SGVector3(0.0f, -10.0f * dt, 0.0f));

		if (Input::instance().GetKey(GLFW_KEY_I))
			camera->transform.Translate(SGVector3(0.0f, 0.0f, 10.0f * dt));
		else if (Input::instance().GetKey(GLFW_KEY_K))
			camera->transform.Translate(SGVector3(0.0f, 0.0f, -10.0f * dt));

		mat1->SetUniform(Shader_Uniform::MATRIX_MVP, *camera * player.transform);

		player.Update(dt);

    }

    void Render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		player.Render();

		glfwSwapBuffers(mainWindow);
    }

    void ApplicationDispose()
    {
		simpleShader.reset();
    }

    ~Application()
    {
    }  

  private:
    SG_PTRS<Shader> simpleShader , uniform_shader , texturedShader;
	SG_PTRS<SGCamera> camera;
	SG_PTRS<SGMaterial> mat1;
	SG_PTRS<SGMaterial> mat2;
    Player player;
	float rotSpeed = 8.0f;
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
