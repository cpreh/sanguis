#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_PROJECTILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_PROJECTILE_HPP_INCLUDED

#include <sanguis/projectile_type_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
projectile(
	sanguis::client::draw2d::entities::model::parameters const &,
	sanguis::projectile_type
);

}
}
}
}

#endif
