#ifndef SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED

#include "value_type.hpp"
#include "../../damage_type.hpp"
#include <boost/array.hpp>

namespace sanguis
{
namespace server
{
namespace damage
{

// TODO: we use boost::array here
// because boost::assign doesn't work with tr1::array
typedef boost::array<
	value_type,
	damage_type::size
> array;

}
}
}

#endif
