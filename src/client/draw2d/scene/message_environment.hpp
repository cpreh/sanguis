#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include "message_environment_fwd.hpp"
#include "object_fwd.hpp"
#include "hud_fwd.hpp"
#include "../../exp.hpp"
#include "../../level.hpp"
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
	FCPPT_NONCOPYABLE(
		message_environment
	);
public:
	explicit message_environment(
		scene::object &,
		scene::hud &
	);

	~message_environment();
private:
	entities::base &
	insert(
		entities::unique_ptr,
		entity_id
	);

	void
	remove(
		entity_id
	);

	entities::base &
	entity(
		entity_id
	);

	void
	experience(
		client::exp
	);

	void
	level(
		client::level
	);

	entities::model::parameters const
	model_parameters() const;

	sprite::particle::system &
	particle_system() const;

	draw2d::insert_own_callback const &
	insert_own_callback() const;

	draw2d::transform_callback const &
	transform_callback() const;

	scene::object &object_;

	scene::hud &hud_;
};

}
}
}
}

#endif
