#include "ShaderManager.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace SGEngine
{
SGMaterialManager &SGMaterialManager::instance()
{
    static SGMaterialManager *_instance = new SGMaterialManager();
    return *_instance;
}

SGMaterialManager::AttributeVariable::AttributeVariable(Shader_SemanticDataType etype, SG_UINT uLocation, int size)
{
    this->_uLocation = uLocation;
    this->_eType = etype;
    this->_iSize = size;
}

SGMaterialManager::UniformVariable::UniformVariable(Shader_UniformDataType etype, SG_UINT uLocation)
{
    this->_uLocation = uLocation;
    this->_eType = etype;
}

SGMaterialManager::ProgramBlob::ProgramBlob()
{
    this->_uId = glCreateProgram();
    this->_aShaderIndex.empty();
}

SGMaterialManager::ShaderBlob::ShaderBlob(int shadertype, std::string filename)
{
    this->uId = glCreateShader(shadertype);
    this->strFilename = filename;
}

SG_UINT SGMaterialManager::InitializeShader(const ShaderType &shaderType, const std::string &filename)
{
#ifdef _DEBUG
	SGFileWriter logger("BuildLog.txt");
	logger << __FUNCTION__ << std::endl;
#endif // _DEBUG

    int glshader_type = 0;
    switch (shaderType)
    {
    case SHADER_VERTEX:
		std::cout << "Creating Shader_Vertex\n";
        glshader_type = GL_VERTEX_SHADER;
        break;

    case SHADER_FRAGMENT:
		std::cout << "Creating Shader_Fragment\n";
        glshader_type = GL_FRAGMENT_SHADER;
        break;
    default:
        std::cout << "INVALID SHADER TYPE PASSED\n";
        break;
    }

    VECTOR_ShaderBlob& vector_loadedShader = _avShaderBlob[shaderType];

    for (unsigned int shader = 0; shader < vector_loadedShader.size(); ++shader)
    {
        if (vector_loadedShader[shader]->strFilename == filename)
        {
			std::cout << "Shader already exist , return the index of the loaded shader\n";
            return shader;
        }
    }

    //Create new Shader Blob
    SPTR_ShaderBlob shaderBlob(new ShaderBlob(glshader_type, filename));
    if (shaderBlob->uId == 0)
    {
        std::cout << "Shader Creation Failed\n";
    }

    SGFileReader file(filename.c_str());
    std::string str = file.ReadFull();
	logger << "Compiling Shader File : " << str << std::endl;
    const char *cstr = str.c_str();
    glShaderSource(shaderBlob->uId, 1, &cstr, NULL);
    glCompileShader(shaderBlob->uId);

    //Log any errors
    char log[512];
    int compileStatus = 0;
    glGetShaderiv(shaderBlob->uId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetShaderInfoLog(shaderBlob->uId, sizeof(log), NULL, log);
        logger << "Compilation of Shader of type : " << shaderType << " Failed \n"
                  << log;
    }

    vector_loadedShader.push_back(shaderBlob);

    return (vector_loadedShader.size() - 1);
}

void SGMaterialManager::ProcessAttributes(const SG_UINT programID, std::string shaderName, Shader::Vector_ShaderAttributeInfo &vSai, MapAttributes &mAttributes)
{

#ifdef _DEBUG
	SGFileWriter logger("BuildLog.txt");
	logger << __FUNCTION__ << std::endl;
#endif // _DEBUG

    // PARSING SHADER FILE
    //bool bError = false;
    int iNumVariables = 0;
    glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTES, &iNumVariables);
    if (iNumVariables == 0 && !vSai.empty())
    {
        for (const auto attrib : vSai)
        {
            std::cout << "Attribute : " << attrib._strName << " Not Found in the shader file\n";
            // RETURN CALL BACK TO THE CALLER DO NOT PROCEED
        }
    }

    int iMaxLength = 0;
    glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &iMaxLength);
    std::unique_ptr<char[]> p_attribute_name(new char[iMaxLength]); // Unecessary : better char buffer[iMaxLength]

    for (int i = 0; i < iNumVariables; i++)
    {
        int iSize;
        GLenum eType;

        glGetActiveAttrib(programID, i, iMaxLength, NULL, &iSize, &eType, p_attribute_name.get());

        Shader_SemanticDataType eAttributeType = static_cast<Shader_SemanticDataType>(eType); // type as defined inside the shader file

        //Verify
        bool bFound = false;
        for (auto it = vSai.begin(); it != vSai.end(); ++it)
        {
            if (it->_strName == p_attribute_name.get())
            {
                bFound = true;
                
                if (it->_shaderVariable._type != eAttributeType)
                {
                    std::cout << "Type Missmatch\n";
                }
                else
                    it->_isVerified = true;
            }
        }
        if (!bFound)
        {
            //bError = true;
            std::cout << p_attribute_name.get() << " is used but not added the the shaderManager\n";
        }
    }

    //Confirm all the attributes have been verified
    for (const Shader::ShaderAttributeInfo &info : vSai)
    {
        if (!info._isVerified)
        {
            //bError = true;
            std::cout << "Not Verified\n";
        }
        else
        {
            //cache location for this attribute
            SG_UINT uLocation = glGetAttribLocation(programID, info._strName.c_str());
            mAttributes.insert(MapAttributes::value_type(info._shaderVariable._variable,
                                                         AttributeVariable(info._shaderVariable._type, uLocation, info._dataSize)));
        }
    }
}

void SGMaterialManager::ProcessUniforms(const SG_UINT programID, std::string shaderName, Shader::Vector_ShaderUniformInfo &vSui, MapUniforms &mUniforms)
{
	int a = 20;
#ifdef _DEBUG
	SGFileWriter logger("BuildLog.txt");
	logger << __FUNCTION__ << std::endl;
#endif // _DEBUG

    int iNumVariables = 0;
    //Get total number of variables present in the shader file
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &iNumVariables);
    if (iNumVariables == 0 && !vSui.empty())
    {
        std::cout << "Shader Does not contain any variables\n";
        return;
    }

    int max_length;
    //Get the max length (char) of the uniform
    glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
	char* namebuffer = new char[max_length];

    for (int i = 0; i < iNumVariables; i++)
    {
        int iSize;
        GLenum etype;
        glGetActiveUniform(programID, i, max_length, NULL, &iSize, &etype, namebuffer);

        Shader_UniformDataType e_uniform_type = static_cast<Shader_UniformDataType>(etype);
        bool bFound = false;
        for (auto it = vSui.begin(); it != vSui.end(); it++)
        {
            if (it->_strName == namebuffer)
            {
                bFound = true;
                if (it->_shaderVariable._type != e_uniform_type)
                {
                    std::cout << "Type Mismatch variable : " << namebuffer << "\n"
                              << "Expected : " << etype << " got : " << it->_shaderVariable._type;
                }
                else
                {
                    it->_isVerified = true;
                }
            }
            if (!bFound)
            {
                std::cout << "Not found shader variable : " << namebuffer;
            }
        }
		delete namebuffer;
    }

    // Confirm all the uniforms are verified and map them
    for (const Shader::ShaderUniformInfo &uinfo : vSui)
    {
        if (!uinfo._isVerified)
            std::cout << "Not Verified Skipping\n";
        else
        {
            SG_UINT uLocation = glGetUniformLocation(programID, uinfo._strName.c_str());
            mUniforms.insert(MapUniforms::value_type(uinfo._shaderVariable._variable,
                                                     UniformVariable(uinfo._shaderVariable._type, uLocation)));
        }
    }
}

void SGMaterialManager::Create(const long int& material_uuid,Shader &shader)
{
	bool _modified = false;
#ifdef _DEBUG
	SGFileWriter logger("BuildLog.txt");
	logger << "Creating Shader"<<std::endl;
#endif
    SPTR_ProgramBlob programBlob = nullptr;
    // Check if material is linked with a program object -> also contains compiled/linked shader
    try
    {
        auto it = _map_ProgramBlob.find(material_uuid); 
        if (it != _map_ProgramBlob.end())
        {
			_modified = true;
            std::cout << "Program Object Exist....Detaching shaders\n";
			//glUseProgram(0);
			glDetachShader(it->second->_uId, _avShaderBlob[SHADER_VERTEX].at(it->second->_aShaderIndex[SHADER_VERTEX])->uId);
			glDetachShader(it->second->_uId, _avShaderBlob[SHADER_FRAGMENT].at(it->second->_aShaderIndex[SHADER_FRAGMENT])->uId);
			programBlob = it->second;
        }
		else
		{
			std::cout << "Program Object does not Exist :\n";
			//Create New Program
			programBlob.reset(new ProgramBlob());
			if (programBlob->_uId == 0)
			{
				std::cout << "glCreateProgram Failed returned 0";
			}
		}
    }
    catch (...)
    {
        std::cout << "Exception Occured Shader Creation Failed\n";
    }

    programBlob->_aShaderIndex[SHADER_VERTEX] = InitializeShader(SHADER_VERTEX, shader._vertex_shader_file);
    programBlob->_aShaderIndex[SHADER_FRAGMENT] = InitializeShader(SHADER_FRAGMENT, shader._fragment_shader_file);

    //combine and link
    glAttachShader(programBlob->_uId, _avShaderBlob[SHADER_VERTEX].at(programBlob->_aShaderIndex[SHADER_VERTEX])->uId);
    glAttachShader(programBlob->_uId, _avShaderBlob[SHADER_FRAGMENT].at(programBlob->_aShaderIndex[SHADER_FRAGMENT])->uId);

    glLinkProgram(programBlob->_uId);

 
    //LOG ERROR
    char log[512];
    int success = 0;
    glGetProgramiv(programBlob->_uId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programBlob->_uId, sizeof(log), NULL, log);
        std::cout << "Error linking program: " << log << std::endl;
    }
	ProcessAttributes(programBlob->_uId, shader.shaderProgramName, shader.vector_sai, programBlob->_mapAttributes);
    ProcessUniforms(programBlob->_uId, shader.shaderProgramName, shader.vector_sui, programBlob->_mapUniform);
	
	if(!_modified)
		_map_ProgramBlob.insert(MAP_ProgramBlob::value_type(material_uuid, programBlob));
}

SGMaterialManager::~SGMaterialManager()
{
    //disable all shader programs
    activeProgram = 0;
    if (glUseProgram)
        glUseProgram(0);

    //Free in memory Program Blobs
    try
    {
        for (auto it = _map_ProgramBlob.begin(); it != _map_ProgramBlob.end(); it++)
        {
            for (SG_UINT uShaderType = 0; uShaderType < it->second->_aShaderIndex.size(); uShaderType++)
            {
                glDetachShader(it->second->_uId, _avShaderBlob[uShaderType].at(
                                                                               it->second->_aShaderIndex[uShaderType])
                                                     ->uId);
            }

            glDeleteProgram(it->second->_uId);
            delete it->second.get();
        }
    }
    catch (...)
    {
        std::cout << "Exception occured , failed to Detach Program<-/->Shader";
    }

    try
    {
        for (SG_UINT uShaderType = 0; uShaderType < _avShaderBlob.size(); uShaderType++)
        {
            //Free in Memory Shader Blobs
            for (SG_UINT i = 0; i < _avShaderBlob[uShaderType].size(); i++)
            {
                glDeleteShader(_avShaderBlob[uShaderType].at(i)->uId);
                delete _avShaderBlob[uShaderType].at(i).get();
            }
        }
    }
    catch (...)
    {
        std::cout << "Exception occurred , failed to glDelete(Shader)\n";
    }
}

void SGMaterialManager::EnableProgram(const long int& material_uuid)
{
    try
    {
        glUseProgram(_map_ProgramBlob[material_uuid]->_uId);
        activeProgram = material_uuid;
    }
    catch (...)
    {
        std::cout << "Shader Program : " << material_uuid << " not found\n";
    }
}

void SGMaterialManager::EnableAttribute(const long int& material_uuid,Shader_Semantic semantic, SG_UINT strideBytes, SG_UINT offsetBytes, bool normalize) const
{
    SetVertexAttribute(material_uuid,semantic, reinterpret_cast<const void *const>(0), true, strideBytes, offsetBytes, normalize);
}

void SGMaterialManager::DisableAttribute(const long int& material_uuid,Shader_Semantic semantic) const
{
    SetVertexAttribute(material_uuid,semantic, reinterpret_cast<const void *const>(0), false, 0, 0, false);
}

	/*	***************************************************************************
		********************** PRIVATE METHODS ************************************
		*************************************************************************** */


void SGMaterialManager::SetVertexAttribute(AttributeVariable attrib, const void *const pVoid, bool bEnable, SG_UINT strideBytes, SG_UINT offsetBytes, bool isNormalized) const
{
	try {
		if (bEnable)
		{
			glVertexAttribPointer(attrib._uLocation, attrib._iSize, GL_FLOAT, isNormalized, strideBytes, reinterpret_cast<const void *>(offsetBytes));
			glEnableVertexAttribArray(attrib._uLocation);
		}
		else
		{
			glDisableVertexAttribArray(attrib._uLocation);
		}
	}
	catch (...)
	{
		std::cout << __FUNCTION__ << std::endl<<"Error\n";
	}
    
}

void SGMaterialManager::SetUniform(const SGMaterialManager::UniformVariable uniform_var, glm::mat4 &m4Matrix) const
{
    try
    {
        if (!(uniform_var._eType == UT_FLOAT_MAT4))
        {
            std::cout << "Fail to set , uniform type mis match\n";
        }

        //set the matrix values
        glUniformMatrix4fv(uniform_var._uLocation, 1, false, &m4Matrix[0][0]);
    }
    catch (...)
    {
        std::cout << "Failed to Set Uniform , check for :\n";
        std::cout << "Did program create\n";
        std::cout << "Check Active program name\n";
    }
}

void SGMaterialManager::SetUniform(const UniformVariable uniform_var,const SGVector4& mValue) const
{
	try
	{
		if (!(uniform_var._eType == UT_FLOAT_VEC4))
		{
			std::cout << "Fail to set , uniform type mis match\n";
		}

		//set the matrix values
		glUniform4fv(uniform_var._uLocation, 1, reinterpret_cast<const float*>(&mValue.vector));
	}
	catch (...)
	{
		std::cout << "Failed to Set Uniform , check for :\n";
		std::cout << "Did program create\n";
		std::cout << "Check Active program name\n";
	}
}

void SGMaterialManager::SetUniform(const UniformVariable uniform_var,const SGVector3& mValue) const
{
	try
	{
		if (!(uniform_var._eType == UT_FLOAT_VEC4))
		{
			std::cout << "Fail to set , uniform type mis match\n";
		}

		//set the matrix values
		glUniform3fv(uniform_var._uLocation, 1, reinterpret_cast<const float*>(&mValue.vector));
	}
	catch (...)
	{
		std::cout << "Failed to Set Uniform , check for :\n";
		std::cout << "Did program create\n";
		std::cout << "Check Active program name\n";
	}
}

void SGMaterialManager::SetUniform(const UniformVariable uniform_var,const SGVector2& mValue) const
{
	try
	{
		if (!(uniform_var._eType == UT_FLOAT_VEC4))
		{
			std::cout << "Fail to set , uniform type mis match\n";
		}

		//set the matrix values
		glUniform2fv(uniform_var._uLocation, 1, reinterpret_cast<const float*>(&mValue.vector));
	}
	catch (...)
	{
		std::cout << "Failed to Set Uniform , check for :\n";
		std::cout << "Did program create?\n";
		std::cout << "Check Active program name\n";
	}
}

} // namespace SGEngine