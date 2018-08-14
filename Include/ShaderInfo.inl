//#ifndef _SHADER_INFO_INL
//#define _SHADER_INFO_INL

template <typename t_variable, typename t_type>
Shader::VariableInfo<t_variable, t_type>::VariableInfo(ShaderVariable<t_variable, t_type> variable, std::string variableName)
{
    _shaderVariable = variable;
    _strName = variableName;
    _isVerified = false;
}

template <typename t_variable, typename t_type>
void Shader::AddVariable(const ShaderVariable<t_variable, t_type>& _variable, std::string variableName)
{
    //Check for duplicates
    std::vector<VariableInfo<t_variable, t_type>> &vinfo = getVector(_variable);
    
    for(const VariableInfo<t_variable, t_type>& info : vinfo)
        {
            if (info._shaderVariable == _variable)
            {
                std::cout << "Error Variable Already Exist in shader program : "<<shaderProgramName<<std::endl;
            }
        }
    //Store the variable
    vinfo.push_back(VariableInfo<t_variable, t_type>(_variable, variableName));
}

template <typename t_variable, typename t_type>
SG_INLINE bool ShaderVariable<t_variable,t_type>::operator==(const ShaderVariable<t_variable, t_type> &inValue)
{
    return (_variable == inValue._variable &&_type == inValue._type);
}

//#endif