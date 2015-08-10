#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_name.hpp>
#include <sanguis/client/draw2d/entities/hover/variant.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/load/model/friend_path.hpp>


sanguis::client::draw2d::entities::friend_::friend_(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::load::auras::context &_aura_resources,
	sanguis::friend_type const _friend_type,
	sanguis::optional_primary_weapon_type const _primary_weapon,
	sanguis::weapon_status const _weapon_status,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::order_function const &_orders,
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
					sanguis::load::model::friend_path(
						_friend_type
					),
					_orders,
					sanguis::client::optional_health_pair(
						_health_pair
					),
					sanguis::client::draw2d::entities::model::decay_option::delayed,
					_primary_weapon,
					_weapon_status,
					_speed,
					_center,
					_rotation,
					sanguis::client::draw2d::sprite::normal::white()
				)
			)
		)
	)
{
}

sanguis::client::draw2d::entities::friend_::~friend_()
{
}

sanguis::client::draw2d::entities::hover::optional_info
sanguis::client::draw2d::entities::friend_::hover() const
{
	return
		sanguis::client::draw2d::entities::hover::optional_info(
			sanguis::client::draw2d::entities::hover::info(
				sanguis::client::draw2d::entities::hover::variant(
					sanguis::client::draw2d::entities::hover::name_and_health(
						sanguis::client::draw2d::entities::hover::optional_name(),
						this->health_pair()
					)
				)
			)
		);
}
