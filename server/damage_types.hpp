#ifndef SANGUIS_SERVER_DAMAGE_TYPES_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_TYPES_HPP_INCLUDED

#include "../damage_type.hpp"

namespace sanguis
{
namespace server
{
namespace damage
{
struct meta;

struct wrapper
{
	damage_type::type e;

	wrapper(const damage_type::type);
	meta operator=(const damage_array::value_type) const;
};

struct meta
{
	damage_type::type e;
	damage_array::value_type d;

	meta(const damage_type::type,const damage_array::value_type);
};

struct list
{
	damage_array array;

	list(meta const &);
	list(damage_array::value_type);
	list &operator()(meta const &);
	operator damage_array() const;
};

extern const wrapper normal,piercing,fire,ice,pure;

list const all(damage_array::value_type);

}
}
}

#endif
