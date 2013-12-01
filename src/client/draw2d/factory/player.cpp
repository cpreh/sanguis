#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/health_pair.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/player.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::player(
	sanguis::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::model::health_pair const _health_pair
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::player
			>(
				_auras_load_context,
				_parameters,
				_auras,
				_buffs,
				_health_pair
			)
		);
}
