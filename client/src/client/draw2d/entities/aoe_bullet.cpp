#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/level_vector.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::load::model::path &&_path,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::model::object(
		sanguis::client::draw2d::entities::model::parameters(
			_load_parameters,
			std::move(
				_path
			),
			sanguis::client::draw2d::entities::constant_order(
				sanguis::client::draw2d::z_ordering::bullet
			),
			sanguis::client::optional_health_pair(),
			sanguis::client::draw2d::entities::model::decay_option::immediate,
			sanguis::optional_primary_weapon_type(),
			sanguis::weapon_status::nothing,
			_speed,
			_center,
			_rotation,
			sanguis::client::draw2d::sprite::normal::white()
		)
	),
	load_parameters_{
		_load_parameters
	},
	insert_(
		_insert
	),
	aoe_(
		_aoe
	)
{
}

sanguis::client::draw2d::entities::aoe_bullet::~aoe_bullet()
{
}

void
sanguis::client::draw2d::entities::aoe_bullet::on_die()
{
	insert_(
		fcppt::unique_ptr_to_base<
			sanguis::client::draw2d::entities::own
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::client::draw2d::entities::explosion
			>(
				load_parameters_,
				this->center(),
				aoe_
			)
		)
	);

	sanguis::client::draw2d::entities::model::object::on_die();
}
