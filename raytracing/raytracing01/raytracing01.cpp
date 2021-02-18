// raytracing01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<string>

#include "hitable.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <float.h>

using namespace std;

#define random(a,b) (rand()%(b-a+1)+a)
#define random1 (float((rand()%(100))) / 100.0f)

vec3 random_in_unit_sphere()
{
	vec3 p;
	do 
	{
		p = 2.0 * vec3(random1, random1, random1) - vec3(1,1,1);
	} while (dot(p,p)>=1.0);
	return p;
}


vec3 color(const ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0, std::numeric_limits<float>::max(), rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(ray(rec.p, target - rec.p), world);
		//return 0.5 * vec3(rec.normal.x() + 1.0, rec.normal.y() + 1.0, rec.normal.z() + 1.0);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5,0.7,1.0);
	}
}


int main()
{
	const char* filePath = "./Test.ppm";
	int nx = 800;
	int ny = 400;

	//采样数量
	int ns = 100;

	hitable* list[2];
	material* m1 = new material();
	material* m2 = new material();
	list[0] = new sphere(vec3(0,0,-1), 0.5, m1);
	list[1] = new sphere(vec3(0,-100.5,-1),100.0, m2);

	hitable* world = new hitable_list(list, 2);

	camera cam;

	ofstream ofs(filePath);
	if (ofs.is_open())
	{
		ofs << "P3\n" << nx << " " << ny << "\n255\n";
		for (int j = ny - 1; j >= 0; --j)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0,0,0);

				for (int s = 0; s < ns; s++)
				{
					float u = (float(i) + float(random(0,100))/100.0f) / (float)nx;
					float v = (float(j) + float(random(0, 100)) / 100.0f) / (float)ny;

					ray r = cam.get_ray(u, v);
					vec3 p = r.point_at_paramer(2.0);
					col += color(r, world);
				}
				col /= float(ns);

				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);
				ofs << to_string(ir) << " " << to_string(ig) << " " << to_string(ib) << "\n";
			}
		}
	}
	ofs.close();
	cout << "hellow world" << endl;
	system("pause");
	return -1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


/* 初体验，输出颜色信息到文本
ofstream ofs(filePath, ios::out | ios::trunc);
if (ofs.is_open())
{
	ofs << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; --j)
	{
		for (int i = 0; i < nx; ++i)
		{
			float r = float(i) / (float)nx;
			float g = float(j) / (float)ny;
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			ofs << ir << " " << ig << " " << ib << "\n";
		}
	}
}
ofs.close();
system("pause");
cout << "hellow world" << endl;
*/