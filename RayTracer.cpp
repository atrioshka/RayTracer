#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {

	//Image
	int image_width = 256;
	int image_height = 256;

	//Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	/*
	The pixels are written out in rows
	Every row of pixels is written out left to right
	These rows are written out from top to bottom
	By convention, each of the rgb components are represented internally by real-valued variables that range from 0.0 to 1.0
	These must be scaled to integer values between 0 and 255 before printing them out
	Red goes from fully OFF (BLACK) to fully ON (RED) from left to right
	Green goes from fully OFF at the top (BLACK) to full on at the bottom (GREEN)
	ADDING RED and GREEN light together make YELLOW so the bottm right corner should be YELLOW.
	*/

	for (int i = 0; i < image_height; i++) {
		std::clog << "r\Scanlines remaining: " << (image_height - i) << ' ' << std::flush;
		for (int j = 0; j < image_width; j++) {

			auto pixel_color = color(double(j) / (image_width - 1), double(i) / (image_height - 1), 0);
			write_color(std::cout, pixel_color);
			
			/*auto r = (double)(j) / (image_width - 1);
			auto g = (double(i) / (image_height - 1));
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';*/

		}
	}
	std::clog << "r\Done.					\n";
}