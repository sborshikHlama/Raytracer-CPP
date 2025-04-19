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

int main(void)
{

	// World
	hittable_list	world;
	camera			cam;

	world.add(make_shared<sphere>(point3(0, 1, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	cam.image_width = 400;
	cam.aspect_ratio = 16.0 / 9.0;
	
	cam.render(world);
}
