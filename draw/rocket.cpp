#include "rocket.hpp"
#include "explosion.hpp"
#include "environment.hpp"
#include <sge/make_auto_ptr.hpp>

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
		sge::make_auto_ptr<
			explosion
		>(
			environment(),
			pos()));
	
	environment().insert()(
		explo);	
	
	model::on_decay();
}
