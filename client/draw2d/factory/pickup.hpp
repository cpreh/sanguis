#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_PICKUP_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity_auto_ptr.hpp"
#include "../../entity_id.hpp"
#include "../../pickup_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entity_auto_ptr
pickup(
	environment const &,
	entity_id,
	pickup_type::type
);

}
}
}
}

#endif
