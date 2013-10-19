#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/entities/enemy.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::enemy(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::load::auras::context &_aura_resources,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::enemy
			>(
				_parameters,
				_aura_resources,
				_enemy_type,
				_auras,
				_buffs
			)
		);
}
