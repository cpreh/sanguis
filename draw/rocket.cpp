#include "rocket.hpp"
#include "explosion.hpp"
#include "environment.hpp"
#include <sge/optional_impl.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::draw::rocket::rocket(
	draw::environment const &env,
	entity_id const id,
	fcppt::string const &name,
	funit const aoe)
:
	bullet(
		env,
		id,
		name
	),
	aoe(aoe)
{}

void sanguis::draw::rocket::on_decay()
{
	entity_auto_ptr explo(
		sge::make_auto_ptr<
			explosion
		>(
			environment(),
			pos(),
			aoe
		)
	);
	
	environment().insert()(
		explo
	);	
	
	model::on_decay();
}
