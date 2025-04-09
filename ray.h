/*
В контексте рейтрейсинга луч — это полупрямая в 3D-пространстве, которая 
начинается в определённой точке (источнике) и идёт в заданном направлении. 
Он используется для моделирования пути света от камеры через пиксель на экране 
в сцену.

Луч задаётся двумя основными элементами:

Точка начала (Origin, обозначается как O) — вектор (x₀, y₀, z₀).
Направление (Direction, обозначается как D) — вектор (dx, dy, dz),
обычно нормализованный (длина = 1).

Математически луч описывается параметрическим уравнением:

P(t) = O + t * D, где:
P(t) — точка на луче;
t — параметр (расстояние вдоль луча, t ≥ 0, так как луч идёт только вперёд);
O — точка начала;
D — направление.
*/

#ifndef RAY_H
# define RAY_H

#include "vec3.h"

class ray {
	private:
		point3 orig;
		vec3 dir;
	public:
		ray() {}

		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

		const point3& origin() const { return orig; }
		const vec3& direction() const { return dir; }

		point3 at(double t) const {
			return orig + t*dir;
		}
};

#endif