#include "rocket.hpp"
#include "explosion.hpp"
#include "environment.hpp"

sanguis::draw::rocket::rocket(
	draw::environment const &env,
	entity_id const id,
	sge::string const &name)
:
	bullet(
		env,
		id,
		name)
{}

void sanguis::draw::rocket::on_decay()
{
	entity_auto_ptr explo(
		new explosion(
			environment(),
			pos()));
	
	environment().insert()(
		explo);	
}
