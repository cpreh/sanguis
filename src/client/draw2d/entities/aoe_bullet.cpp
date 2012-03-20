#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/own_auto_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	model::parameters const &_param,
	sprite::particle::system &_particle_system,
	draw2d::insert_own_callback const &_insert,
	fcppt::string const &_name,
	draw2d::aoe const _aoe
)
:
	model::object(
		_param,
		_name,
		fcppt::assign::make_container<
			entities::order_vector
		>(
			z_ordering::bullet
		),
		model::needs_healthbar::no,
		model::decay_option::immediate
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
	particle_system_(
		_particle_system
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
	entities::own_auto_ptr explo(
		fcppt::make_auto_ptr<
			entities::explosion
		>(
			fcppt::cref(
				diff_clock_
			),
			fcppt::ref(
				random_generator_
			),
			fcppt::ref(
				particle_system_
			),
			fcppt::cref(
				model_collection_
			),
			this->center(),
			aoe_
		)
	);

	insert_(
		explo
	);

	model::object::on_decay();
}
