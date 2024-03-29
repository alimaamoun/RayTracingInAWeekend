#pragma once
#ifndef RTWEEKEND_H
#define REWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

//usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//utility functions

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180;
}

//common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"


#endif