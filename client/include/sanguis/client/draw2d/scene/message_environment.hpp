#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/message/environment.hpp>
#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>


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
		sanguis::client::draw2d::scene::world::object &,
		sanguis::client::player_health_callback const &
	);

	~message_environment();
private:
	sanguis::client::draw2d::entities::base &
	insert(
		sanguis::client::draw2d::entities::unique_ptr &&,
		sanguis::entity_id
	)
	override;

	void
	remove(
		sanguis::entity_id
	)
	override;

	sanguis::client::draw2d::entities::base &
	entity(
		sanguis::entity_id
	)
	override;

	void
	change_world(
		sanguis::client::world_parameters const &
	)
	override;

	sanguis::client::draw2d::entities::model::load_parameters const
	model_parameters() const
	override;

	sanguis::client::load::auras::context &
	aura_resources() const
	override;

	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const
	override;

	sanguis::client::draw2d::player_center_callback const &
	player_center_callback() const
	override;

	sanguis::client::draw2d::collide_callback const &
	collide_callback() const
	override;

	sanguis::client::player_health_callback const &
	player_health_callback() const
	override;

	sanguis::client::draw2d::scene::object &object_;

	sanguis::client::draw2d::scene::world::object &world_;

	sanguis::client::player_health_callback const player_health_callback_;
};

}
}
}
}

#endif
