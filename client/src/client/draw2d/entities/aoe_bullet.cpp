#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::load::model::path const &_path,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::model::object(
		sanguis::client::draw2d::entities::model::parameters(
			_load_parameters,
			_path,
			sanguis::client::draw2d::entities::order_vector{
				sanguis::client::draw2d::z_ordering::bullet
			},
			sanguis::client::optional_health_pair(),
			sanguis::client::draw2d::entities::model::decay_option::immediate,
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
