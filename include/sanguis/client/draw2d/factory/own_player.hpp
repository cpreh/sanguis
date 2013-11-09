#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>


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
	sanguis::load::auras::context &,
	sanguis::client::draw2d::entities::model::load_parameters const &,
	sanguis::client::draw2d::player_center_callback const &,
	sanguis::client::draw2d::collide_callback const &,
	sanguis::aura_type_vector const &,
	sanguis::buff_type_vector const &
);

}
}
}
}

#endif
