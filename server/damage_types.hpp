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

struct all_meta;
struct all_wrapper
{
	all_meta operator=(const damage_array::value_type) const;
};

struct all_meta 
{
	damage_array::value_type d;

	all_meta(const damage_array::value_type);
	operator damage_array() const;
};

extern const wrapper normal,piercing,fire,ice,pure;
extern const all_wrapper all;
}
}
}

sanguis::damage_array operator,(sanguis::damage_array,const sanguis::server::damage::meta &);
sanguis::damage_array operator,(const sanguis::server::damage::meta &,const sanguis::server::damage::meta &);
sanguis::damage_array operator,(const sanguis::server::damage::all_meta &,const sanguis::server::damage::meta &);

#endif
