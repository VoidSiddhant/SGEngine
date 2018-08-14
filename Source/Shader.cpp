#include "Shader.h"
#include "Core.h"


namespace SGEngine
{

template <>
ShaderVariable<Shader_Semantic, Shader_VariableType>::ShaderVariable(Shader_Semantic variable, Shader_VariableType type)
{
  _variable = variable;
  _type = type;
}
template <>
ShaderVariable<Shader_Uniform, Shader_UniformType>::ShaderVariable(Shader_Uniform variable, Shader_UniformType type)
{
  _variable = variable;
  _type = type;
} 

Shader::Shader(const char *shaderName, const char *vs_file, const char *fs_file)
{
  shaderProgramName = shaderName;
  _vertex_shader_file = vs_file;
  _fragment_shader_file = fs_file;
}

Shader::~Shader()
{
}

} // namespace SGEngine