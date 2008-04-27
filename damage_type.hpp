#ifndef SANGUIS_DAMAGE_TYPE_HPP_INCLUDED
#define SANGUIS_DAMAGE_TYPE_HPP_INCLUDED

#include "messages/types.hpp"
#include <boost/array.hpp>

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

typedef boost::array<
	messages::space_unit,
	damage_type::size> damage_array;

typedef damage_array armor_array;

}
}

#endif
