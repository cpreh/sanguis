#ifndef SANGUIS_MESSAGES_DIM_HPP_INCLUDED
#define SANGUIS_MESSAGES_DIM_HPP_INCLUDED

#include "bindings/static.hpp"
#include "types/dim.hpp"
#include "space_unit.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::static_<
	types::dim,
	space_unit
> dim;

}
}

#endif
