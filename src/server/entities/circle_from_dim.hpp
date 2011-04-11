#ifndef SANGUIS_SERVER_ENTITIES_CIRCLE_FROM_DIM_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CIRCLE_FROM_DIM_HPP_INCLUDED

#include "body_parameters.hpp"
#include "../collision/solidity_fwd.hpp"
#include "../dim.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

entities::body_parameters const
circle_from_dim(
	server::dim const &,
	collision::solidity const &
);

}
}
}

#endif
