#ifndef VEC3_H
# define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
	public:
		double e[3];

		// Constructors
		vec3(): e{0, 0, 0} {}
		vec3(double e0, double e1, double e2): e{e0, e1, e2} {}

		// const - метод не может менять e
		// эти три метода что-то вроде геттеров
		double x() const {return e[0]; }
		double y() const {return e[1]; }
		double z() const {return e[2]; }

		// Operator overload
		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		// Сложение двух векторов — это покомпонентное сложение их координат.
		vec3& operator+=(const vec3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		vec3& operator*=(double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3& operator/=(double t)
		{
			return *this *= 1/t;
		}

		double length() const {
			return std::sqrt(length_squared());
		}

		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}
};

// Type alias
using point3 = vec3;

// Vector Utility Functions

// Не понимаю зачем здесь передавать референс на вектор, а не просто копию
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Умножение вектора на число изменяет его длину, но не направление.
// Зачем нужно: Например, для изменения длины луча или масштабирования направления.
inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
	return (1/t) * v;
}

// Скалярное произведение даёт число, показывающее, насколько два вектора "смотрят" в одном направлении.
inline double dot(const vec3& u, const vec3& v)
{
	return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

// Векторное произведение даёт новый вектор, перпендикулярный двум исходным.
inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3((u.e[1] * v.e[2] - u.e[2] * v.e[1]),
				(u.e[2] * v.e[0] - u.e[0] * v.e[2]),
				(u.e[0] * v.e[1] - u.e[1] * v.e[0]));
}

inline vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}

#endif