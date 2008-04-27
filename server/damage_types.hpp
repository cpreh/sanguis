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
	operator damage_array() const;
};

damage_array operator,(damage_array,const meta &);
damage_array operator,(const meta &,const meta &);

extern const wrapper normal,piercing,fire,ice,pure;
}
}
}

#endif
