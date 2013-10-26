#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/enemy.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/load/auras/context_fwd.hpp>


sanguis::client::draw2d::entities::enemy::enemy(
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::load::auras::context &_aura_resources,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::name const &_name
)
:
	sanguis::client::draw2d::entities::with_buffs_auras_model(
		sanguis::client::draw2d::entities::with_buffs_auras_model_parameters(
			_load_parameters.diff_clock(),
			_load_parameters.normal_system(),
			_load_parameters.collection(),
			_buffs,
			sanguis::client::draw2d::entities::with_auras_model_parameters(
				_load_parameters.diff_clock(),
				_aura_resources,
				_load_parameters.normal_system(),
				_auras,
				sanguis::client::draw2d::entities::model::parameters(
					_load_parameters,
					sanguis::client::draw2d::entities::model::name(
						sanguis::load::enemy_name(
							_enemy_type
						)
					),
					sanguis::client::draw2d::entities::order_vector{
						sanguis::client::draw2d::z_ordering::model_generic
					},
					sanguis::client::draw2d::entities::model::needs_healthbar::yes,
					sanguis::client::draw2d::entities::model::decay_option::delayed
				)
			)
		)
	),
	name_(
		_name
	)
{
}

sanguis::client::draw2d::entities::enemy::~enemy()
{
}

sanguis::client::draw2d::entities::name
sanguis::client::draw2d::entities::enemy::name() const
{
	return
		name_;
}
