template<typename UniformData>
void SGMaterial::SetUniform(const Shader_Uniform& uniform_name, const UniformData& data)
{
	SGMaterialManager::instance().SetUniform(uuid, uniform_name, data);
}
