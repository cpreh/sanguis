#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/load/friend_name.hpp>


sanguis::client::draw2d::entities::friend_::friend_(
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::client::load::auras::context &_aura_resources,
	sanguis::friend_type const _friend_type,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::order_vector const &_orders,
	sanguis::client::health_pair const _health_pair
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
						sanguis::load::friend_name(
							_friend_type
						)
					),
					_orders,
					sanguis::client::optional_health_pair(
						_health_pair
					),
					sanguis::client::draw2d::entities::model::decay_option::delayed
				)
			)
		)
	)
{
}

sanguis::client::draw2d::entities::friend_::~friend_()
{
}
