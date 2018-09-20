#ifndef SG_UTIL_H
#define SG_UTIL_H

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include "External/glm/glm.hpp"
#include "External/glm/gtc/matrix_transform.hpp"
#include "External/glm/mat4x4.hpp"

//Error Codes
#define SG_UTIL_ERROR_CRITICAL 1

//Version values
#define SG_GLFW_VERSION_MAJOR 3
#define SG_GLFW_VERSION_MINOR 3

//Window Dimensions
#define SG_UTIL_SCREEN_WIDTH 800.0f
#define SG_UTIL_SCREEN_HEIGHT 640.0f

#define SG_UTIL_MATH_TORAD 3.14159265f / 180.0f

#define SG_INT64 int64_t
#define SG_UUID	long int
#define SG_UINT unsigned int
#define SG_UCHAR unsigned char
#define SG_INLINE inline
#define SG_PTRS std::shared_ptr
#define SG_PTRU std::unique_ptr
#define SG_MAKEPTRS std::make_shared
#define SG_MAKEPTRU std::make_unique

#define SG_DEBUG_START	ifdef _DEBUG
#define SG_DEBUG_END	#endif

#endif

#define S(x) x##y 