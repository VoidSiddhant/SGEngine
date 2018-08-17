#include "ShaderManager.h"
#include "FileReader.h"

namespace SGEngine
{
SGShaderManager &SGShaderManager::instance()
{
    static SGShaderManager *_instance = new SGShaderManager();
    return *_instance;
}

SGShaderManager::AttributeVariable::AttributeVariable(Shader_VariableType etype, SG_UINT uLocation)
{
    this->_uLocation = uLocation;
    this->_eType = etype;
}

SGShaderManager::UniformVariable::UniformVariable(Shader_UniformType etype, SG_UINT uLocation)
{
    this->_uLocation = uLocation;
    this->_eType = etype;
}

SGShaderManager::ProgramBlob::ProgramBlob()
{
    this->_uId = glCreateProgram();
    this->_aShaderIndex.empty();
}

SGShaderManager::ShaderBlob::ShaderBlob(int shadertype, std::string filename)
{
    this->uId = glCreateShader(shadertype);
    this->strFilename = filename;
}

SG_UINT SGShaderManager::InitializeShader(const ShaderType &shaderType, const std::string &filename)
{
    int glshader_type = 0;
    switch (shaderType)
    {
    case SHADER_VERTEX:
        glshader_type = GL_VERTEX_SHADER;
        break;

    case SHADER_FRAGMENT:
        glshader_type = GL_FRAGMENT_SHADER;
        break;
    default:
        std::cout << "INVALID SHADER TYPE PASSED\n";
        break;
    }

    VECTOR_ShaderBlob &vector_loadedShader = _avShaderBlob[shaderType];

    for (unsigned int shader = 0; shader < vector_loadedShader.size(); ++shader)
    {
        if (vector_loadedShader[shader]->strFilename == filename)
        {
            //Shader already exist , return the index of the loaded shader
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
        std::cout << "Compilation of Shader of type : " << shaderType << " Failed \n"
                  << log;
    }

    vector_loadedShader.push_back(shaderBlob);

    return (vector_loadedShader.size() - 1);
}

void SGShaderManager::ProcessAttributes(const uint programID, std::string shaderName, Shader::Vector_ShaderAttributeInfo &vSai, MapAttributes &mAttributes)
{
    // PARSING SHADER FILE
    bool bError = false;
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

        Shader_VariableType eAttributeType = static_cast<Shader_VariableType>(eType);

        //Verify
        bool bFound = false;
        for (auto it = vSai.begin(); it != vSai.end(); ++i)
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
            bError = true;
            std::cout << p_attribute_name.get() << " is used but not added the the shaderManager\n";
        }
    }

    //Confirm all the attributes have been verified
    for (const Shader::ShaderAttributeInfo &info : vSai)
    {
        if (!info._isVerified)
        {
            bError = true;
            std::cout << "Not Verified\n";
        }
        else
        {
            //cache location for this attribute
            SG_UINT uLocation = glGetAttribLocation(programID, info._strName.c_str());
            mAttributes.insert(MapAttributes::value_type(info._shaderVariable._variable,
                                                         AttributeVariable(info._shaderVariable._type, uLocation)));
        }
    }
}

void SGShaderManager::ProcessUniforms(const uint programID, std::string shaderName, Shader::Vector_ShaderUniformInfo &vSui, MapUniforms &mUniforms)
{
    // Parse....................................................

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
    char namebuffer[max_length];

    for (int i = 0; i < iNumVariables; i++)
    {
        int iSize;
        GLenum etype;
        glGetActiveUniform(programID, i, max_length, NULL, &iSize, &etype, namebuffer);

        Shader_UniformType e_uniform_type = static_cast<Shader_UniformType>(etype);
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
// namespace SGEngine   } }

void SGShaderManager::Create(Shader &shader)
{
    SPTR_ProgramBlob programBlob = nullptr;
    // Check if Shader already has been created
    try
    {
        programBlob = _map_ProgramBlob.at(shader.shaderProgramName);
        if (programBlob)
        {
            std::cout << "Shader Already Created\n";
            throw;
        }
    }
    catch (...)
    {
        std::cout << "Exception Occured Shader Creation Failed\n";
    }
    //Create New Program
    programBlob.reset(new ProgramBlob());
    if (programBlob->_uId == 0)
    {
        std::cout << "glCreateProgram Failed returned 0";
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

    _map_ProgramBlob.insert(MAP_ProgramBlob::value_type(shader.shaderProgramName, programBlob));
}

SGShaderManager::~SGShaderManager()
{
    //disable all shader programs
    activeShaderProgramName = "";
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

void SGShaderManager::EnableProgram(std::string shaderProgramName)
{
    try
    {
        glUseProgram(_map_ProgramBlob[shaderProgramName]->_uId);
        activeShaderProgramName = shaderProgramName;
    }
    catch (...)
    {
        std::cout << "Shader Program : " << shaderProgramName << " not found\n";
    }
}

void SGShaderManager::EnableAttribute(Shader_Semantic semantic, SG_UINT strideBytes, SG_UINT offsetBytes, bool normalize) const
{
    SetVertexAttribute(semantic, reinterpret_cast<const void *const>(0), true, strideBytes, offsetBytes, normalize);
}

void SGShaderManager::DisableAttribute(Shader_Semantic semantic) const
{
    SetVertexAttribute(semantic, reinterpret_cast<const void *const>(0), false, 0, 0, false);
}

void SGShaderManager::SetVertexAttribute(AttributeVariable attrib, const void *const pVoid, bool bEnable, SG_UINT strideBytes, SG_UINT offsetBytes, bool isNormalized) const
{
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

void SGShaderManager::SetUniform(Shader_Uniform eType,const glm::mat4& m4Matrix) const
{
    try
    {
        SPTR_ProgramBlob shared_program = _map_ProgramBlob.at(activeShaderProgramName);
        
        MapUniforms::const_iterator it = shared_program->_mapUniform.find(eType);
        if(it == shared_program->_mapUniform.end())
        {
            std::cout<<"Fail to set , Uniform not found\n";
        }
        else if(!(it->second._eType == UT_FLOAT_MAT4))
        {
            std::cout<<"Fail to set , uniform type mis match\n";
        }

        //set the matrix values
        glUniformMatrix4fv(it->second._uLocation,1,false,&m4Matrix[0][0]);
    }
    catch(...)
    {
        std::cout<<"Failed to Set Uniform , check for :\n";
        std::cout<<"Did program create\n";
        std::cout<<"Check Active program name\n";
    }
}
} // namespace SGEngine