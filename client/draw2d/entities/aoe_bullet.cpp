#include "aoe_bullet.hpp"
#include "explosion.hpp"
#include "model/parameters.hpp"
#include "../z_ordering.hpp"
#include "../../next_id.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::client::draw2d::entities::aoe_bullet::aoe_bullet(
	model::parameters const &param,
	sprite::particle::system &particle_system_,
	insert_callback const &insert,
	fcppt::string const &name,
	funit const aoe
)
:
	model::object(
		param,
		name,
		z_ordering::bullet,
		model::needs_healthbar::no,
		model::decay_option::immediate
	),
	model_collection_(param.collection()),
	particle_system_(particle_system_),
	insert(insert),
	aoe(aoe)
{}
		
void
sanguis::client::draw2d::entities::aoe_bullet::decay()
{
	entities::auto_ptr explo(
		fcppt::make_auto_ptr<
			explosion
		>(
			std::tr1::ref(
				particle_system_
			),
			model_collection_,
			pos(),
			aoe
		)
	);
	
	insert(
		explo,
		client::next_id()
	);	
	
	model::object::decay();
}
