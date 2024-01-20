#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {

	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	world.add(make_shared<sphere>(point3(-1, -.2, -1.01), 0.5));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1920;

	cam.initialize();
	cam.render(world);

	return 0;
}