#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

#include"SGUtil.h"
#include <map>
#include <memory>
#include <unordered_map>
#include "Shader.h"

namespace SGEngine
{
class SGShaderManager
{
private:
  enum ShaderType
  {
    SHADER_VERTEX = 0,
    SHADER_FRAGMENT
  };

  struct AttributeVariable
  {
    AttributeVariable(Shader_VariableType eType, SG_UINT uLocationIn);

    SG_UINT _uLocation;
    Shader_VariableType _eType;
    int _iSize;  // NOT IN USE 
  };

  struct UniformVariable
  {
    UniformVariable(Shader_UniformType, SG_UINT uLocation);

    SG_UINT _uLocation;
    Shader_UniformType _eType;
  };
  /* Usage:
  * To access the stored variables in the shader
  * User sends the Shader_Semantic ex : Shader_Semantic::Position and the program
    returns the attributes mapped to that particular semantic in the program
  * Multiple Postion semantics can be given as : POSITION0 , POSITION1.....
  * Filled after parsing the shader file and verifying the supplied ShaderInfo by
    the shader class   */
  typedef std::unordered_map<Shader_Semantic, AttributeVariable> MapAttributes;
  typedef std::unordered_map<Shader_Uniform, UniformVariable> MapUniforms;

  struct ProgramBlob
  {
    ProgramBlob();

    SG_UINT _uId;                         // Shader Program Object blob ID
    std::array<SG_UINT, 2> _aShaderIndex; //Index at which the shader blobs are loaded in the info shader array of vectors
    
    SGShaderManager::MapAttributes _mapAttributes;
    MapUniforms _mapUniform;
  };

  struct ShaderBlob
  {
    ShaderBlob(int shaderId, std::string strShaderFilename);

    SG_UINT uId; // Shader Data Blob ID
    std::string strFilename;
  };

  typedef std::shared_ptr<ProgramBlob> SPTR_ProgramBlob;
  typedef std::shared_ptr<ShaderBlob> SPTR_ShaderBlob;
  typedef std::map<std::string, SPTR_ProgramBlob> MAP_ProgramBlob;
  typedef std::vector<SPTR_ShaderBlob> VECTOR_ShaderBlob;

public:
  static SGShaderManager &instance();
  void Create(Shader &shader);
  void Enable(SG_UINT shaderProgramID);
  void EnableAttribute(ShaderAttribute attribute, unsigned strideBytes = 0, unsigned offsetBytes = 0, bool normalize = false) const;
  void DisableAttribute(ShaderAttribute attribute) const;
  void SetUniform(ShaderUniform uniform, const glm::mat4 &matrix);

private:
  SGShaderManager() {}
  ~SGShaderManager() {}
  SGShaderManager &ShaderManager(const SGShaderManager &obj);
  SGShaderManager &operator=(const SGShaderManager &c);

  //Functions
  SG_UINT InitializeShader(const ShaderType &shaderType, const std::string &filename);
  void ProcessAttributes(const uint programID,std::string shaderName,Shader::Vector_ShaderAttributeInfo& sai,MapAttributes& mAttributes) ;
  void ProcessUniforms(const uint programID,std::string shaderName , Shader::Vector_ShaderUniformInfo& sui,MapUniforms& mUniforms) ;
  //Data
  SG_UINT _enabledShaderProgram;
  
  /* Loaded Program Objects stored as map<shader.name,ProgramBlob> 
  * Contains programID
  * Index(in the vector list) of the shaders linked to this program object
  * Map of attributes <SemanticType,AttributeVariable(ShaderVariable_Type,Location)>
  * Map of uniforms   <UniformType ,UniformVariable(UniformVariable_type,Location)>
  */
  MAP_ProgramBlob _map_ProgramBlob;
  
  /* List of all loaded shader in memory
  * Branching into array of vectors -> size = 2
  * array[0] -> Vector_list -> Vertex Shaders loaded
  * array[1] -> Vector_List -> Pixel Shaders loaded */
  std::array<VECTOR_ShaderBlob, 2> _avShaderBlob;
};
} // namespace SGEngine

#endif