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
      std::cout << "Invalid type passed , Check Shader_VariableTypes for the supported shader data types\n";
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