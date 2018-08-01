#ifndef _SHADER_H
#define _SHADER_H

#include "SGUtil.h"
#include<glm/glm.hpp>
namespace SGEngine
{
  class Shader
  {
    public : //const char* vs_file , const char* fs_file
    Shader(const char* vs_file , const char* fs_file);
    ~Shader();

    void Use();
    void SetFloat3(const char* variable_name,glm::vec3 value);
    void SetFloat4(const char* variable_name,glm::vec4 value);

    private :
    SG_UINT shaderID;
  };

}
#endif