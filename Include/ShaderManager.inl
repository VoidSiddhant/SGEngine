template <typename T>
void SGShaderManager::SetVertexAttribute(Shader_Semantic semantic, const T *const pParam, bool bEnable, SG_UINT strideBytes, SG_UINT offsetBytes, bool normalize) const
{
  try
  {
    SPTR_ProgramBlob shared_programBlob = _map_ProgramBlob.at(activeShaderProgramName);
    MapAttributes::const_iterator it = shared_programBlob->_mapAttributes.find(semantic);
    if (it == shared_programBlob->_mapAttributes.end())
    {
      std::cout << "Attribute location not found \n";
    }
    if (!(it->second._eType == VT_FLOAT_VEC3 ||
          it->second._eType == VT_FLOAT_VEC4))
    {
      std::cout << "Invalid type , Check Shader_VariableTypes for the supported shader data types\n";
    }
    SetVertexAttribute(it->second, pParam, bEnable, strideBytes, offsetBytes, normalize);
  }
  catch (...)
  {
    std::cout << "Unexpected error occured while Accessing Shader Attributes , follow the below steps\n";
    std::cout << "Check ActiveShaderProgramName\n";
    std::cout << "Check if program is created\n";
  }
}

template<typename t_value_type>
void SGShaderManager::SetUniform(const Shader_Uniform uniform_name,const t_value_type& t_data_type) const
{
	// Check if this unifrom_name exist in the current loaded shader
	try
	{
		SPTR_ProgramBlob shared_program = _map_ProgramBlob.at(activeShaderProgramName);
		MapUniforms::const_iterator it = shared_program->_mapUniform.find(uniform_name);

		if (it == shared_program->_mapUniform.end())
		{
			std::cout << "Failed to Set , Uniform not found : \n";
		}
		else
		{
			this->SetUniform(it->second, t_data_type);
		}
	}
	catch (...)
	{
		std::cout << "UnExpected Error Thrown from Function : " << __FUNCTION__ << std::endl;
	}
}

