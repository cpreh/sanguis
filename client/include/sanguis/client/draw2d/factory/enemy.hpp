#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_ENEMY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_ENEMY_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::unique_ptr
enemy(
	sanguis::client::draw2d::entities::load_parameters const &,
	sanguis::client::load::auras::context &,
	sanguis::creator::enemy_type,
	sanguis::enemy_kind,
	sanguis::optional_primary_weapon_type,
	sanguis::weapon_status,
	sanguis::client::draw2d::speed,
	sanguis::client::draw2d::sprite::center,
	sanguis::client::draw2d::sprite::rotation,
	sanguis::aura_type_vector const &,
	sanguis::buff_type_vector const &,
	sanguis::client::draw2d::entities::name const &,
	sanguis::client::health_pair
);

}
}
}
}

#endif
