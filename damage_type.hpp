#ifndef SANGUIS_DAMAGE_TYPE_HPP_INCLUDED
#define SANGUIS_DAMAGE_TYPE_HPP_INCLUDED

#include <boost/array.hpp>

namespace sanguis
{

// TODO: split this header
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

// TODO: we use boost::array here
// because boost::assign doesn't work with tr1::array
typedef boost::array<
	float, // TODO: make a typedef for this!
	damage_type::size
> damage_array;

typedef damage_array armor_array;

}

#endif
