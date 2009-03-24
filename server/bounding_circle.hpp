#ifndef SANGUIS_SERVER_BOUNDING_CIRCLE_HPP_INCLUDED
#define SANGUIS_SERVER_BOUNDING_CIRCLE_HPP_INCLUDED

#include "entities/entity_fwd.hpp"
#include "types.hpp"

namespace sanguis
{
namespace server
{
circle_type const
bounding_circle(
	entities::entity const &);

}
}

#endif
