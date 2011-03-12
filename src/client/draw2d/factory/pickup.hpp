#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_PICKUP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_PICKUP_HPP_INCLUDED

#include "../entities/auto_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../../../pickup_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
pickup(
	entities::model::parameters const &,
	pickup_type::type
);

}
}
}
}

#endif
