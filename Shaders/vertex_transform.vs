
// Shader :
/* Input
	* Local to world pos transform 
	* Color input for all vertices
	* Texture Sample data from the program
	* 
	*/


#version core 450

layout(location = 0) in vec3 lPos;
layout(location = 1) in vec