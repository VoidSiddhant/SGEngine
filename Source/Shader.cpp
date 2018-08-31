#include "Shader.h"
#include "Core.h"

namespace SGEngine
{

template <>
ShaderVariable<Shader_Semantic, Shader_SemanticDataType>::ShaderVariable(Shader_Semantic variable, Shader_SemanticDataType type)
{
  _variable = variable;
  _type = type;
}
template <>
ShaderVariable<Shader_Uniform, Shader_UniformDataType>::ShaderVariable(Shader_Uniform variable, Shader_UniformDataType type)
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