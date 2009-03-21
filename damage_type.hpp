#ifndef SANGUIS_DAMAGE_TYPE_HPP_INCLUDED
#define SANGUIS_DAMAGE_TYPE_HPP_INCLUDED

#include "messages/types.hpp"
#include <boost/tr1/array.hpp>

namespace sanguis
{

namespace damage_type
{
enum type {
	normal,
	piercing,
	fire,
	ice,
	pure,
	size
};
}

typedef std::tr1::array<
	messages::space_unit,
	damage_type::size
> damage_array;

typedef damage_array armor_array;

}

#endif
