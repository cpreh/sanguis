#include <sanguis/client/draw2d/scene/message_environment.hpp>
#include <sanguis/client/draw2d/scene/hud.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/scene/world/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>

sanguis::client::draw2d::scene::message_environment::message_environment(
	scene::object &_object,
	scene::hud &_hud,
	scene::world::object &_world
)
:
	object_(_object),
	hud_(_hud),
	world_(_world)
{
}

sanguis::client::draw2d::scene::message_environment::~message_environment()
{
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::insert(
	entities::unique_ptr _entity,
	sanguis::entity_id const _id
)
{
	return
		object_.insert(
			move(
				_entity
			),
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::remove(
	sanguis::entity_id const _id
)
{
	object_.remove(
		_id
	);
}

sanguis::client::draw2d::entities::base &
sanguis::client::draw2d::scene::message_environment::entity(
	sanguis::entity_id const _id
)
{
	return
		object_.entity(
			_id
		);
}

void
sanguis::client::draw2d::scene::message_environment::experience(
	client::exp const _exp
)
{
	hud_.experience(
		_exp
	);
}

void
sanguis::client::draw2d::scene::message_environment::level(
	client::level const _level
)
{
	hud_.level(
		_level
	);
}

void
sanguis::client::draw2d::scene::message_environment::change_world(
	client::world_parameters const &_param
)
{
	world_.change(
		_param
	);
}

sanguis::client::draw2d::entities::model::parameters const
sanguis::client::draw2d::scene::message_environment::model_parameters() const
{
	return
		entities::model::parameters(
			object_.diff_clock(),
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

sanguis::client::draw2d::insert_own_callback const &
sanguis::client::draw2d::scene::message_environment::insert_own_callback() const
{
	return object_.insert_own_callback();
}

sanguis::client::draw2d::transform_callback const &
sanguis::client::draw2d::scene::message_environment::transform_callback() const
{
	return object_.transform_callback();
}
