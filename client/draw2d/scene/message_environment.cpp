#include "message_environment.hpp"
#include "object.hpp"
#include "hud.hpp"

sanguis::client::draw2d::scene::message_environment::message_environment(
	object &scene_,
	hud &hud_
)
:
	scene_(scene_),
	hud_(hud_)
{}

sanguis::client::draw2d::scene::message_environment::~message_environment()
{}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::insert(
	entities::auto_ptr e_ptr,
	entity_id const id
)
{
	return 
		scene_.insert(
			e_ptr,
			id
		);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::entity(
	entity_id const id
)
{
	return
		scene_.entity(
			id
		);
}

void
sanguis::client::draw2d::scene::message_environment::experience(
	exp_type const exp
)
{
	hud_.experience(
		exp
	);
}

void
sanguis::client::draw2d::scene::message_environment::level(
	level_type const level_
)
{
	hud_.level(
		level_
	);
}
