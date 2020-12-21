#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_SPAWN_PARTICLE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_SPAWN_PARTICLE_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/optional_own_unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/creator/optional_background_tile_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

sanguis::client::draw2d::entities::optional_own_unique_ptr
enemy_spawn_particle(
	sanguis::client::draw2d::entities::load_parameters const &,
	sanguis::creator::enemy_type,
	sanguis::client::draw2d::sprite::center const &,
	sanguis::creator::optional_background_tile
);

}
}
}
}

#endif
