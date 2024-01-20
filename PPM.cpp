#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>
#include <cstdio>


color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

//color test_color(const ray& r) {
//	vec3 unit_direction = unit_vector()
//}

int main() {

	//File
	std::freopen("image.ppm", "w", stdout);

	//Image

	auto aspect_ratio = 16.0 / 9.0;
		//file output image width
	int image_width = 1200;

		//Calculate the image height, and ensure it is at least 1 (will round down to nearest int)
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;	//height = (if height < 1) ? height = 1 : else height = height

	//World

	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	//Camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);

	//Calculate the vectors across the horizontal and down the vertical viewport edges
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	//Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	//Calculate the location of the upper left pixel.
	auto viewport_upper_left = camera_center
		- vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);



	//Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; ++j) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			//DEBUG: SHOWS VIEWPORT EDGES
			/*color pixel_color;
			vec3 is_viewport_edge_u = cross(point3((double)i, (double)j, 0.0), pixel_delta_u);
			vec3 is_viewport_edge_v = cross(point3((double)i, (double)j, 0.0), pixel_delta_v);

			if (is_viewport_edge_u == vec3(0,0,0)) {
				std::clog << "cross ("; write_point(std::clog, point3(i, j, 0)); std::clog << ") & ("; write_point(std::clog, pixel_delta_u); std::clog << ") == 0\n";
				pixel_color = color(1, 0, 0);
			}
			if (is_viewport_edge_v == vec3(0,0,0)) {
				std::clog << "cross ("; write_point(std::clog, point3(i, j, 0)); std::clog << ") & ("; write_point(std::clog, pixel_delta_u); std::clog << ") == 0\n";
				pixel_color = color(0, 1, 0);
			}
			else{pixel_color = ray_color(r);}*/
			color pixel_color = ray_color(r, world);
			
			write_color(std::cout, pixel_color);
		}
	}

	std::clog << "\rDone.                   \n";

	return 0;
}