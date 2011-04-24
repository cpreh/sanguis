#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_PROJECTILE_HPP_INCLUDED

#include "../entities/unique_ptr.hpp"
#include "../entities/model/parameters_fwd.hpp"
#include "../../../projectile_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::unique_ptr
projectile(
	entities::model::parameters const &,
	projectile_type::type
);

}
}
}
}

#endif
