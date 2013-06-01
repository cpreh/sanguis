#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
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
own_player(
	sanguis::client::draw2d::entities::model::parameters const &,
	sanguis::client::draw2d::transform_callback const &,
	sanguis::client::draw2d::collide_callback const &
);

}
}
}
}

#endif
