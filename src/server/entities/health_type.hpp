#ifndef SANGUIS_SERVER_ENTITIES_HEALTH_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_HEALTH_TYPE_HPP_INCLUDED

#include "property/value.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

FCPPT_MAKE_STRONG_TYPEDEF(
	property::value,
	health_type
)

}
}
}

#endif