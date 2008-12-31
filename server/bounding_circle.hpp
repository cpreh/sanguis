#ifndef SANGUIS_SERVER_BOUNDING_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_BOUNDING_CIRCLE_HPP_INCLUDED

#include "types.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
class entity;
}

circle_type const
bounding_circle(
	entities::entity const &);

}
}

#endif
