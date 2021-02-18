#pragma once
#include "vec3.h"
#include<random>
using namespace std;
class ray
{
public:
	ray(vec3 a, vec3 b) { A = a; B = b; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_paramer(float t) const{ return A + t * B; }
	vec3 A;
	vec3 B;

	static double randomN()
	{
		default_random_engine e;
		uniform_real_distribution<double> u(0.0, 1.0);
		return u(e);
	}
};

double drand48()
{
	default_random_engine e;
	uniform_real_distribution<double> u(0.0, 1.0);
	return u(e);
}

