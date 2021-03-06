#pragma once

#include "ray.h"

#include<math.h>
#define _USE_MATH_DEFINES
using namespace std;

#define M_PI 3.1415926

//class camera
//{
//
//	vec3 origin;
//	vec3 u, v, w;
//	vec3 horizontal;
//	vec3 vertical;
//	vec3 low_left_corner;
//	float len_radius;
//
//public:
//	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
//	{
//		len_radius = aperture / 2;
//		float theta = vfov * M_PI / 180;
//		float half_height = tan(theta /2);
//		float half_width = aspect * half_height;
//		origin = lookfrom;
//
//		w = unit_vector(lookfrom - lookat);
//		u = unit_vector(cross(vup, w));
//		v = cross(w, u);
//
//		low_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
//		horizontal = 2 * half_width * focus_dist * u;
//		vertical = 2 * half_height * focus_dist * v;
//	}
//
//	ray get_ray(float s, float t)
//	{
//		vec3 rd = len_radius * random_in_unit_disk();
//		vec3 offset = u * rd.x() + v * rd.y();
//		return ray(origin + offset, low_left_corner + s * horizontal + t * vertical - origin - offset);
//	}
//
//	vec3 random_in_unit_disk()
//	{
//		vec3 p;
//		do 
//		{
//			p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0,1.0,1.0);
//		} while (dot(p,p)>=1.0);
//		return p;
//	}
//};

class camera
{
	vec3 origin;
	vec3 horizontal;
	vec3 vertical;
	vec3 lower_left_corner;

public:
	camera()
	{
		lower_left_corner = vec3(-2.0f, -1.0f, -1.0f);
		horizontal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = vec3(0.0, 0.0, 0.0);
	}

	ray get_ray(float u, float v)
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
};
