#ifndef _SHADER_INFO_INL
#define _SHADER_INFO_INL

template <typename t_variable, typename t_type>
Shader::VariableInfo<t_variable, t_type>::VariableInfo(ShaderVariable<t_variable, t_type> variable, std::string variableName)
{
    _shaderVariable = variable;
    _strName = variableName;
    _isVerified = false;
}


#endif