#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/other_player.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/player.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::player(
	sanguis::client::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::optional_primary_weapon_type const _primary_weapon_type,
	sanguis::weapon_status const _weapon_status,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::health_pair const _health_pair,
	sanguis::client::draw2d::entities::name const &_name
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::other_player
			>(
				_auras_load_context,
				_parameters,
				_primary_weapon_type,
				_weapon_status,
				_speed,
				_center,
				_rotation,
				_auras,
				_buffs,
				_health_pair,
				_name
			)
		);
}
