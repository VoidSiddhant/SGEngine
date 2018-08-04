#include "Shader.h"
#include "Core.h"
#include <sstream>

namespace SGEngine
{
template<>
ShaderVariable<Shader_Semantic, Shader_VariableType>::ShaderVariable(Shader_Semantic variable, Shader_VariableType type)
{
  _variable = variable;
  _type = type;
}
template<>
ShaderVariable<Shader_Uniform, Shader_UniformType>::ShaderVariable(Shader_Uniform variable, Shader_UniformType type)
{
  _variable = variable;
  _type = type;
}
template <typename variable, typename type>
void Shader::AddVariable(ShaderVariable<variable,type> _variable,std::string variableName)
{
  //std::vector<variable,type>
}

Shader::Shader(char *shaderName, const char *vs_file, const char *fs_file)
{
  name = shaderName;
  //***************VERTEX SHADER**************************//
  //Open File
  std::ifstream file_vs(vs_file, std::ios_base::in);
  std::ifstream file_fs(fs_file, std::ios_base::in);

  if (!file_fs || !file_vs)
  {
    std::cout << "Failed to Read file\n";
  }

  std::stringstream vertex_file_stream, fragment_file_stream;
  vertex_file_stream << file_vs.rdbuf();
  fragment_file_stream << file_fs.rdbuf();
  file_fs.close();
  file_vs.close();
  int size = strlen(vertex_file_stream.str().c_str());
  std::string str = vertex_file_stream.str();
  std::string str2 = fragment_file_stream.str();
  const char *vertex_code = str.c_str();
  const char *fragment_code = str2.c_str();

  SG_UINT vs_object = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs_object, 1, &vertex_code, &size);
  //Log Any Vertex Shader Error
  glCompileShader(vs_object);
  char log[512];
  int success = 0;
  glGetShaderiv(vs_object, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vs_object, sizeof(log), NULL, log);
    std::cout << "Vertex Shader Compilation Faield : " << log << std::endl;
  }

  SG_UINT fs_object = glCreateShader(GL_FRAGMENT_SHADER);
  size = strlen(fragment_file_stream.str().c_str());

  glShaderSource(fs_object, 1, &fragment_code, &size);
  //Log Any Fragment Shader Error
  glCompileShader(fs_object);
  success = 0;
  glGetShaderiv(fs_object, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fs_object, sizeof(log), NULL, log);
    std::cout << "Fragment Shader Compilation Failed : " << log << std::endl;
  }

  success = 0;
  //Link to the Program Object
  shaderID = 0;
  shaderID = glCreateProgram();
  glAttachShader(shaderID, vs_object);
  glAttachShader(shaderID, fs_object);
  glLinkProgram(shaderID);

  glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
    std::cout << "Error linking program: " << log << std::endl;
  }
  //Delete the shader object
  glDeleteShader(vs_object);
  glDeleteShader(fs_object);
}

void Shader::SetFloat3(const char *variable_name, glm::vec3 value)
{
  glUniform3f(glGetUniformLocation(shaderID, variable_name), value.x, value.y, value.z);
}

void Shader::SetFloat4(const char *variable_name, glm::vec4 value)
{
  glUniform4f(glGetUniformLocation(shaderID, variable_name), value.x, value.y, value.z, value.w);
}

void Shader::Use()
{
  glUseProgram(shaderID);
}

Shader::~Shader()
{
}

} // namespace SGEngine