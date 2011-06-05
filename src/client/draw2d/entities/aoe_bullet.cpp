#include "aoe_bullet.hpp"
#include "explosion.hpp"
#include "own_auto_ptr.hpp"
#include "model/parameters.hpp"
#include "../z_ordering.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
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
		z_ordering::bullet,
		model::needs_healthbar::no,
		model::decay_option::immediate
	),
	model_collection_(_param.collection()),
	particle_system_(_particle_system),
	insert_(_insert),
	aoe_(_aoe)
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
