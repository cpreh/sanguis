#include "grenade.hpp"
#include "z_ordering.hpp"
#include "explosion.hpp"
#include "environment.hpp"
#include <sge/optional_impl.hpp>
#include <fcppt/make_auto_ptr.hpp>

sanguis::draw::grenade::grenade(
	draw::environment const &env,
	entity_id const id,
	fcppt::string const &name,
	funit const aoe)
:
	model(
		env,
		id,
		name,
		z_ordering::bullet,
		false,
		draw::remove_action::remove
	),
	aoe(aoe)
{}
		
void sanguis::draw::grenade::on_decay()
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
