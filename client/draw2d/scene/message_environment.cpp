#include "message_environment.hpp"
#include "object.hpp"
#include "hud.hpp"
#include "../entities/model/parameters.hpp"

sanguis::client::draw2d::scene::message_environment::message_environment(
	object &object_,
	hud &hud_
)
:
	object_(object_),
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
		object_.insert(
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
		object_.entity(
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

sanguis::client::draw2d::entities::model::parameters const
sanguis::client::draw2d::scene::message_environment::model_parameters() const
{
	return entities::model::parameters(
		object_.colored_system(),
		object_.normal_system(),
		object_.load_collection()
	);
}

sanguis::client::draw2d::sprite::particle::system &
sanguis::client::draw2d::scene::message_environment::particle_system() const
{
	return object_.particle_system();
}

sanguis::client::draw2d::insert_callback const &
sanguis::client::draw2d::scene::message_environment::insert_callback() const
{
	return object_.insert_callback();
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::message_environment::transform_callback() const
{
	return object_.transform_callback();
}

sanguis::entity_id
sanguis::client::draw2d::scene::message_environment::own_player_id() const
{
	return object_.player_id();
}

sge::renderer::screen_size const
sanguis::client::draw2d::scene::message_environment::screen_size() const
{
	return object_.screen_size();
}
