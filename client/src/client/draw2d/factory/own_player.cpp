#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::own_player(
	sanguis::client::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::client::draw2d::collide_callback const &_collide_callback,
	sanguis::client::player_health_callback const &_player_health_callback,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::health_pair const _health_pair
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::own_player
			>(
				_auras_load_context,
				_parameters,
				_collide_callback,
				_player_health_callback,
				_auras,
				_buffs,
				_health_pair
			)
		);
}
