#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/math/vector/object_impl.hpp>


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
		sanguis::client::draw2d::entities::order_vector{
			sanguis::client::draw2d::z_ordering::bullet
		},
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
	insert_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::entities::explosion
		>(
			diff_clock_,
			random_generator_,
			model_collection_,
			this->center(),
			aoe_
		)
	);

	sanguis::client::draw2d::entities::model::object::on_decay();
}
