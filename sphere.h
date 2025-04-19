#ifndef SPHERE_H
# define SPHERE_H

# include "hittable.h"
# include "vec3.h"

class sphere : public hittable {
	
	private:
		point3	center;
		double	radius;

	public:
		sphere(const point3& center, double radius): center(center), radius(std::fmax(0, radius)) {}

		bool	hit(const ray& r, interval ray_t, hit_record& rec) const override
		{
			vec3	oc = center - r.origin();
			auto	a = dot(r.direction(), r.direction());
			auto	b = -2 * dot(r.direction(), oc);
			auto	c = dot(oc, oc) - radius * radius;
			auto	discriminant = b*b - 4*a*c;
			
			if (discriminant < 0)
				return (false);
			auto	sqrtd = std::sqrt(discriminant);
			auto	root = (-b - sqrtd) / (2 * a);
			vec3	outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			if (!ray_t.surrounds(root))
			{
				root = (-b + sqrtd) / 2;
				if (!ray_t.surrounds(root))
					return (false);
			}
			rec.t = root;
			rec.p = r.at(rec.t);
			rec.normal = (rec.p - center) / radius;
			return (true);
		}
};

#endif