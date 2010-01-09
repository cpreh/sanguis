#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "message_environment_fwd.hpp"
#include "object_fwd.hpp"
#include "hud_fwd.hpp"
#include "../message/environment.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class message_environment
:
	public draw2d::message::environment
{
	FCPPT_NONCOPYABLE(message_environment)
public:
	explicit message_environment(
		object &,
		hud &
	);

	~message_environment();
private:
	entities::base &
	insert(
		entities::auto_ptr,
		entity_id
	);

	entities::base &
	entity(
		entity_id
	);

	void
	experience(
		exp_type
	);

	void
	level(
		level_type
	);

	entities::model::parameters const
	model_parameters() const;

	sprite::particle::system &
	particle_system() const;

	draw2d::insert_callback const &
	insert_callback() const;

	draw2d::transform_callback const &
	transform_callback() const;

	entity_id
	own_player_id() const;

	sge::renderer::screen_size const
	screen_size() const;

	object &object_;

	hud &hud_;
};

}
}
}
}

#endif
