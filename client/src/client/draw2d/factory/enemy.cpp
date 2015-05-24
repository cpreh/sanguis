#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/enemy_kind.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/enemy.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::enemy(
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::client::load::auras::context &_aura_resources,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::enemy_kind const _enemy_kind,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::name const &_name,
	sanguis::client::health_pair const _health_pair
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::enemy
			>(
				_parameters,
				_aura_resources,
				_enemy_type,
				_enemy_kind,
				_auras,
				_buffs,
				_name,
				_health_pair
			)
		);
}
