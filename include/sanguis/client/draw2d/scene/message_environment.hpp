#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>


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
	public sanguis::client::draw2d::message::environment
{
	FCPPT_NONCOPYABLE(
		message_environment
	);
public:
	message_environment(
		sanguis::client::draw2d::scene::object &,
		sanguis::client::draw2d::scene::hud &,
		sanguis::client::draw2d::scene::world::object &
	);

	~message_environment();
private:
	sanguis::client::draw2d::entities::base &
	insert(
		sanguis::client::draw2d::entities::unique_ptr &&,
		sanguis::entity_id
	);

	void
	remove(
		sanguis::entity_id
	);

	sanguis::client::draw2d::entities::base &
	entity(
		sanguis::entity_id
	);

	void
	experience(
		sanguis::client::exp
	);

	void
	level(
		sanguis::client::level
	);

	void
	change_world(
		sanguis::client::world_parameters const &
	);

	sanguis::client::draw2d::entities::model::parameters const
	model_parameters() const;

	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const;

	sanguis::client::draw2d::transform_callback const &
	transform_callback() const;

	sanguis::client::draw2d::collide_callback const &
	collide_callback() const;

	sanguis::client::draw2d::scene::object &object_;

	sanguis::client::draw2d::scene::hud &hud_;

	sanguis::client::draw2d::scene::world::object &world_;
};

}
}
}
}

#endif
