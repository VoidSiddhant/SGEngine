template <typename T>
void SGMaterialManager::SetVertexAttribute(const long int& material_uuid,Shader_Semantic semantic, const T *const pParam, bool bEnable, SG_UINT strideBytes, SG_UINT offsetBytes, bool normalize) const
{
  try
  {
    SPTR_ProgramBlob shared_programBlob = _map_ProgramBlob.at(material_uuid);
    MapAttributes::const_iterator it = shared_programBlob->_mapAttributes.find(semantic);
    if (it == shared_programBlob->_mapAttributes.end())
    {
      std::cout << "Attribute location not found \n";
    }
    if (!(it->second._eType == VT_FLOAT_VEC3 ||
          it->second._eType == VT_FLOAT_VEC4 ||
		  it->second._eType == VT_FLOAT_VEC2 ))
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
void SGMaterialManager::SetUniform(const long int& material_uuid,const Shader_Uniform uniform_name,const t_value_type& t_data_type)
{
	// Check if this unifrom_name exist in the current loaded shader
	try
	{
		SPTR_ProgramBlob shared_program = _map_ProgramBlob.at(material_uuid);
		MapUniforms::const_iterator it = shared_program->_mapUniform.find(uniform_name);

		if (it == shared_program->_mapUniform.end())
		{
			std::cout << "Failed to Set , Uniform not found : \n";
		}
		else
		{
			glUseProgram(shared_program->_uId);
			this->SetUniform(it->second, t_data_type);
		}
	}
	catch (...)
	{
		std::cout << "UnExpected Error Thrown from Function : " << __FUNCTION__ << std::endl;
	}
}

