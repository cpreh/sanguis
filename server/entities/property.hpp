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
	void set_current_to_max();

	value_type max() const;

	void reset_max_to_base();
	void add_to_max(value_type);
	void multiply_max_with_base(value_type);
	void max(value_type);
private:
	void adjust_current(
		value_type old_max);
	
	value_type base_,
	           max_,
	           current_;
};

}
}
}

#endif
