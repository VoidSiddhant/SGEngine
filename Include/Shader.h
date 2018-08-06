#ifndef _SHADER_H
#define _SHADER_H

#include "SGUtil.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace SGEngine
{
enum Shader_VariableType
{
  VT_FLOAT_VEC2 = GL_FLOAT_VEC2,
  VT_FLOAT_VEC3 = GL_FLOAT_VEC3,
  VT_FLOAT_VEC4 = GL_FLOAT_VEC4
};

enum Shader_UniformType
{
  UT_FLOAT_MAT4 = GL_FLOAT_MAT4
};

enum Shader_Semantic
{
  Semantic_Position,
  Semantic_Color,
  Semantic_Texture
};

enum Shader_Uniform
{
  MVP_Matrix
};

template <typename variable, typename type>
class ShaderVariable
{
public:
  ShaderVariable(variable, type);
  SG_INLINE bool operator==(const ShaderVariable<variable,type>& inValue);
private:
  //Prevent Copying
  ShaderVariable<variable, type> &
  operator=(const ShaderVariable<variable, type> &v);

  variable _variable;
  type _type;
};

typedef ShaderVariable<Shader_Semantic, Shader_VariableType> ShaderAttribute;
typedef ShaderVariable<Shader_Uniform, Shader_UniformType> ShaderUniform;

class Shader
{
public:
  Shader(const char *shaderName, const char *vs_file, const char *fs_file);
  ~Shader();

  void Use();
  template <typename variable, typename type>
  void AddVariable(const ShaderVariable<variable, type>& _variable, std::string variableName);
  void SetFloat3(const char *variable_name, glm::vec3 value);
  void SetFloat4(const char *variable_name, glm::vec4 value);

private:
  template <typename variable, typename type>
  struct VariableInfo
  {
    ShaderVariable<variable, type> _shaderVariable;

    std::string _strName;
    bool _isVerified;

    VariableInfo(ShaderVariable<variable, type> v, std::string variableName);
  };

  //Prevent Copying of object
  Shader(const Shader &copy);
  Shader &operator=(const Shader &copy);

  std::string name;
  SG_UINT shaderID;

  typedef VariableInfo<Shader_Semantic, Shader_VariableType> ShaderAttributeInfo;
  typedef VariableInfo<Shader_Uniform, Shader_UniformType> ShaderUniformInfo;

  std::vector<ShaderAttributeInfo> vector_sai;
  std::vector<ShaderUniformInfo> vector_sui;

  std::vector<ShaderAttributeInfo>& getVector(const ShaderAttribute& attribute){
    return vector_sai;
  }

  std::vector<ShaderUniformInfo>& getVector (const ShaderUniform& uniform){
    return vector_sui;
  }
};

#include "ShaderInfo.inl"

} // namespace SGEngine
#endif