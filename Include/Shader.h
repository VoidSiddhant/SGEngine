#ifndef _SHADER_H
#define _SHADER_H

#include "SGUtil.h"
#include "Property.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace SGEngine
{
  enum AttributeType
  {
    AT_FLOAT_VEC3 = GL_FLOAT_VEC3,
    AT_FLOAT_VEC4 = GL_FLOAT_VEC4
  };

  enum UniformType
  {
    UT_FLOAT_MAT4 = GL_FLOAT_MAT4
  };

template <typename variable, typename type>
class ShaderVariable final
{
public:
  ShaderVariable(variable, type);

      private :
      //Prevent Copying
      ShaderVariable<variable, type> &
      operator=(const ShaderVariable<variable, type> &v);

  variable _variable;
  type _type;
};

typedef ShaderVariable<P_Attributes,AttributeType> ShaderAttribute;
typedef ShaderVariable<P_Uniform,UniformType> ShaderUniform;

class Shader
{
public: //const char* vs_file , const char* fs_file
  Shader(char *shaderName, const char *vs_file, const char *fs_file);
  ~Shader();

  void Use();
  template <typename variable, typename type>
  void AddVariable(ShaderVariable<variable, type> _variable, std::string variableName);
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
  
  typedef VariableInfo<P_Attributes,AttributeType> AttributeInfo;
  typedef VariableInfo<P_Uniform,UniformType> UniformInfo;
};

#include "ShaderInfo.inl"

} // namespace SGEngine
#endif