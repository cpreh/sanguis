#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/own_auto_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	fcppt::string const &_name,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::model::object(
		_param,
		_name,
		fcppt::assign::make_container<
			sanguis::client::draw2d::entities::order_vector
		>(
			sanguis::client::draw2d::z_ordering::bullet
		),
		sanguis::client::draw2d::entities::model::needs_healthbar::no,
		sanguis::client::draw2d::entities::model::decay_option::immediate
	),
	diff_clock_(
		_param.diff_clock()
	),
	random_generator_(
		_param.random_generator()
	),
	model_collection_(
		_param.collection()
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
sanguis::client::draw2d::entities::aoe_bullet::on_decay()
{
	sanguis::client::draw2d::entities::own_auto_ptr explosion(
		fcppt::make_auto_ptr<
			sanguis::client::draw2d::entities::explosion
		>(
			fcppt::cref(
				diff_clock_
			),
			fcppt::ref(
				random_generator_
			),
			fcppt::cref(
				model_collection_
			),
			this->center(),
			aoe_
		)
	);

	insert_(
		explosion
	);

	sanguis::client::draw2d::entities::model::object::on_decay();
}
