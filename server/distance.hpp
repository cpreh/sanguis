#ifndef SANGUIS_SERVER_DISTANCE_HPP_INCLUDED
#define SANGUIS_SERVER_DISTANCE_HPP_INCLUDED

#include "entities/entity_fwd.hpp"
#include "types.hpp"

namespace sanguis
{
namespace server
{
space_unit
distance(
	entities::entity const &,
	entities::entity const &);

space_unit
distance(
	entities::entity const &,
	pos_type const &);

}
}

#endif
