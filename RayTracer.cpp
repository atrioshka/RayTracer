#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - (radius * radius);
	auto discriminant = b * b - 4 * a * c;
	//discriminant =  0 gives one real solution, discriminant > 0 gives two real solutions
	return (discriminant >= 0);
}

//returns the color for a given scene ray 
//renders a blue to white gradient depending on ray Y coordinate

color ray_color(const ray& r) {
	//renders a spehere that colors red any pixel that intersects it
	if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
		return color(1, 0, 0);
	}

	//normalize vector r
	vec3 unit_direction = unit_vector(r.direction());

	//0.0 <= a <= 1.0, and  -1.0 < y < 1.0
	auto a = 0.5 * (unit_direction.y() + 1.0);

	//blendedValue = ((1 - a) * startValue) + (a * endValue)
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
		
}

int main() {

	//----------------------------------------- IMAGE ------------------------------------------
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	

	//Calculates the image height, and ensures that it is at least 1
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	//----------------------------------------- CAMERA ------------------------------------------
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);

	//Calculates the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	//Calculates the horizontal and vertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	//Calculates the location of the upper left pixel 
	auto viewport_upper_left = 
		  camera_center 
		- vec3(0, 0, focal_length)
		- viewport_u / 2
		- viewport_v / 2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	//----------------------------------------- RENDER ------------------------------------------
	/*
	The pixels are written out in rows
	Every row of pixels is written out left to right
	The rows are written out from top to bottom
	By convention, each of the rgb components are represented internally by real-valued variables that range from 0.0 to 1.0
	These must be scaled to integer values between 0 and 255 before printing them out
	Red goes from fully OFF (BLACK) to fully ON (RED) from left to right
	Green goes from fully OFF at the top (BLACK) to full on at the bottom (GREEN)
	ADDING RED and GREEN light together make YELLOW so the bottm right corner should be YELLOW.
	*/
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {
		std::clog << "r\Scanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {

			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;

			ray r(camera_center, ray_direction);
			color pixel_color = ray_color(r);

			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "r\Done.					\n";
}