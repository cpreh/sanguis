#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/enemy_kind.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/create_parameters.hpp>
#include <sanguis/client/draw2d/entities/enemy.hpp>
#include <sanguis/client/draw2d/entities/enemy_color.hpp>
#include <sanguis/client/draw2d/entities/enemy_spawn_particle.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/with_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_name.hpp>
#include <sanguis/client/draw2d/entities/hover/variant.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/model/enemy_path.hpp>
#include <sge/image/color/any/convert.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::enemy::enemy(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::load::auras::context &_aura_resources,
	sanguis::creator::enemy_type const _enemy_type,
	sanguis::enemy_kind const _enemy_kind,
	sanguis::optional_primary_weapon_type const _primary_weapon,
	sanguis::weapon_status const _weapon_status,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::draw2d::entities::name const &_name,
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
					sanguis::load::model::enemy_path(
						_enemy_type
					),
					sanguis::client::draw2d::entities::constant_order(
						sanguis::client::draw2d::z_ordering::model_generic
					),
					sanguis::client::optional_health_pair(
						_health_pair
					),
					sanguis::client::draw2d::entities::model::decay_option::delayed,
					_primary_weapon,
					_weapon_status,
					_speed,
					_center,
					_rotation,
					sge::image::color::any::convert<
						sanguis::client::draw2d::sprite::normal::color_format
					>(
						sanguis::client::draw2d::entities::enemy_color(
							_enemy_kind
						)
					)
				)
			)
		)
	),
	enemy_type_{
		_enemy_type
	},
	name_{
		fcppt::copy(
			_name.get()
		),
		sanguis::client::draw2d::entities::enemy_color(
			_enemy_kind
		)
	}
{
}

sanguis::client::draw2d::entities::enemy::~enemy()
{
}

void
sanguis::client::draw2d::entities::enemy::on_create(
	sanguis::client::draw2d::entities::create_parameters const &_create_parameters
)
{
	fcppt::optional::maybe_void(
		sanguis::client::draw2d::entities::enemy_spawn_particle(
			_create_parameters.load_parameters(),
			enemy_type_,
			this->center(),
			_create_parameters.background_tile()
		),
		[
			&_create_parameters
		](
			sanguis::client::draw2d::entities::own_unique_ptr &&_spawn_particle
		)
		{
			_create_parameters.insert_own_callback()(
				std::move(
					_spawn_particle
				)
			);
		}
	);
}

sanguis::client::draw2d::entities::hover::optional_info
sanguis::client::draw2d::entities::enemy::hover() const
{
	return
		sanguis::client::draw2d::entities::hover::optional_info(
			sanguis::client::draw2d::entities::hover::info(
				sanguis::client::draw2d::entities::hover::variant(
					sanguis::client::draw2d::entities::hover::name_and_health(
						sanguis::client::draw2d::entities::hover::optional_name(
							name_
						),
						this->health_pair()
					)
				)
			)
		);
}
