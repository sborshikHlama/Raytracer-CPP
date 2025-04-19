#ifndef	HITTABLE_LIST_H
# define HITTABLE_LIST_H

#include "hittable.h"
#include "main.h"
#include <vector>

/*shared_ptr<type> is a pointer to some allocated type, with reference-counting semantics.
Every time you assign its value to another shared pointer 
(usually with a simple assignment), the reference count is incremented. 
As shared pointers go out of scope (like at the end of a block or function),
the reference count is decremented. Once the count goes to zero, the object is safely deleted.*/

class hittable_list : public hittable {
	public:
		std::vector<shared_ptr<hittable>> objects;

		void	clear() { objects.clear(); }

		void	add(shared_ptr<hittable> object) {
			objects.push_back(object);
		}

		hittable_list() {}
		hittable_list(shared_ptr<hittable> object) { add(object); }
		
		bool	hit(const	ray& r, interval ray_t, hit_record& rec) const override {
			hit_record	temp_rec;
			bool		hit_anything = false;
			auto		closest_so_far = ray_t.max;

			for (const auto& object : objects) {
				if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return (hit_anything);
		}
};

#endif