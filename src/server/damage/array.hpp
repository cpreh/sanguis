#ifndef SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ARRAY_HPP_INCLUDED

#include "unit.hpp"
#include "../../damage_type.hpp"
#include <fcppt/container/array.hpp>

namespace sanguis
{
namespace server
{
namespace damage
{

typedef fcppt::container::array<
	unit,
	damage_type::size
> array;

}
}
}

#endif
