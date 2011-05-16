#ifndef SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED
#define SANGUIS_MESSAGES_VECTOR2_HPP_INCLUDED

#include "bindings/static.hpp"
#include "types/vector2.hpp"
#include "space_unit.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::static_<
	messages::types::vector2,
	messages::space_unit
> vector2;

}
}

#endif
