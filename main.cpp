#include "main.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

/*
Центр камеры — это точка в 3D-пространстве, из которой исходят все лучи сцены.
Её ещё называют "точкой глаза" (eye point), потому что она моделирует позицию наблюдателя.
В терминах рейтрейсинга это точка O (origin) для всех лучей P(t) = O + t * D.

Вектор от центра камеры до центра viewport (виртуального окна) ортогонален самому viewport,
то есть перпендикулярен его плоскости.
Это значит, что камера "смотрит" прямо на центр viewport, и направление взгляда 
(вектор N) составляет угол 90° с плоскостью окна.
*/

color ray_color(const ray& r, const hittable& world)
{
	hit_record	rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3	unit_direction = unit_vector(r.direction());
	auto	a = 0.5 * (unit_direction.y() + 1.0);
	return ((1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0));
}

int main(void)
{

	auto	aspect_ratio = 16.0 / 9.0;
	int		image_width = 400;

	/* Задаются переменные вроде image_width (ширина) и image_height (высота)
	— это количество пикселей по горизонтали и вертикали. */
	int		image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// World
	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 1, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera
	auto	focal_length = 1.0;
	auto	viewport_height = 2.0;
	auto	viewport_width = viewport_height * (double(image_width) / image_height);
	auto	camera_center = point3(0, 0, 0);

	auto	view_port_u = vec3(viewport_width, 0, 0);
	auto	view_port_v = vec3(0, -viewport_height, 0);

	/* Дельта-вектор — это вектор, который показывает, как перейти от одной точки к другой. 
	Он получается, когда ты вычитаешь координаты одной точки из координат другой */
	auto	pixel_delta_u = view_port_u / image_width;
	auto	pixel_delta_v = view_port_v / image_height;

	// Можно будет потом написать функцию которая находит средний вектор
	auto	viewport_upper_left = (camera_center - vec3(0, 0, focal_length)
				- view_port_u / 2 - view_port_v / 2);
	auto	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	
	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			auto	pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto	ray_direction = pixel_center - camera_center;
			ray		r(camera_center, ray_direction);

			color	pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "\rDone.                \n";
}
