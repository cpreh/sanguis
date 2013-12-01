#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::client::draw2d::entities::model::name const &_name,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::model::object(
		sanguis::client::draw2d::entities::model::parameters(
			_parameters,
			_name,
			sanguis::client::draw2d::entities::order_vector{
				sanguis::client::draw2d::z_ordering::bullet
			},
			sanguis::client::draw2d::entities::model::optional_health_pair(),
			sanguis::client::draw2d::entities::model::decay_option::immediate
		)
	),
	diff_clock_(
		_parameters.diff_clock()
	),
	random_generator_(
		_parameters.random_generator()
	),
	model_collection_(
		_parameters.collection()
	),
	normal_system_(
		_parameters.normal_system()
	),
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
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::entities::explosion
		>(
			diff_clock_,
			random_generator_,
			normal_system_,
			model_collection_,
			this->center(),
			aoe_
		)
	);

	sanguis::client::draw2d::entities::model::object::on_die();
}
