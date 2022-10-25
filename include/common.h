#ifndef COMMON_H
#define COMMON_H

#define EPSILON 0.000001
#define EPSILONf 0.000001f

#define MY_PI 3.141592653589793
#define MY_2PI 6.283185307179586
#define MY_PI_HALF 1.5707963267948966

#define MY_PIf 3.141592653589793f
#define MY_2PIf 6.283185307179586f
#define MY_PI_HALFf 1.5707963267948966f

#include <glm.hpp>

// --- Types ---

using vec3 = glm::vec3;
using mat3 = glm::mat3;

// --- Functions ---

using glm::clamp;
using glm::max;
using glm::min;
using glm::normalize;
using glm::reflect;
using glm::transpose;

#endif // COMMON_H