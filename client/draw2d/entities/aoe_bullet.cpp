#include "aoe_bullet.hpp"
#include "explosion.hpp"
#include "../z_ordering.hpp"
#include "../../next_id.hpp"
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
		false
	),
	particle_system_(particle_system_),
	insert(insert),
	aoe(aoe)
{}
		
void
sanguis::client::draw2d::entities::aoe_bullet::on_decay()
{
	entity_auto_ptr explo(
		fcppt::make_auto_ptr<
			explosion
		>(
			particle_system_,
			pos(),
			aoe
		)
	);
	
	insert(
		explo,
		client::next_id()
	);	
	
	model::object::on_decay();
}
