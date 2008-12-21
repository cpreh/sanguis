#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_HPP_INCLUDED

#include "../types.hpp"
#undef max // TODO: find out where windows.h comes from!

namespace sanguis
{
namespace server
{
namespace entities
{

class property {
public:
	struct type {
		enum enum_type {
			health,
			attack_speed,
			movement_speed,
			size
		};
	};

	typedef space_unit value_type;

	property();
	property(
		value_type current,
		value_type base);
	property(
		value_type base);

	value_type current() const;
	void current(value_type);

	void current_to_max();

	void reset();

	value_type max() const;

	void add_to_max(value_type);
	void multiply_max(value_type);
	void max(value_type);

	void apply();

	void restrict(
		value_type);
	void unrestrict();
private:
	void clamp();
	
	value_type const base_;
	value_type
		max_linear_,
		max_constant_,
		max_,
		current_,
		restrict_;
};

}
}
}

#endif
