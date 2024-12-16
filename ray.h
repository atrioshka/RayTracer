#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {

	//P(t) = A + (t * b) where, 
	//P is a 3D position along a line in 3D
	//A is the origin of the ray
	//b is the direction of the ray
	//t is a ray parameter in the set of Real numbers

public:
	ray(){}

	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction){}

	//returns origin of the ray (A)
	//returns an immutable reference to orig
	const point3& origin() const { return orig; }

	//returns direction of the ray (b)
	//returns an immutable reference to dir
	const vec3& direction() const { return dir; }
	
	//returns the 3D position of a ray at t (P(t))
	point3 at(double t) const {
		return orig + t * dir;
	}

private:
	//A
	point3 orig;
	//b
	vec3 dir;
};
#endif // !RAY_H
