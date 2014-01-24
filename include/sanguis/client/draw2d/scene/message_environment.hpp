#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_MESSAGE_ENVIRONMENT_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/level.hpp>
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
#include <sanguis/client/draw2d/scene/hud/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>


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
		sanguis::client::draw2d::scene::hud::object &,
		sanguis::client::draw2d::scene::world::object &
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
	experience(
		sanguis::client::exp
	)
	override;

	void
	level(
		sanguis::client::level,
		sanguis::client::exp_for_next_level
	)
	override;

	void
	change_world(
		sanguis::client::world_parameters const &
	)
	override;

	void
	give_weapon(
		sanguis::weapon_description const &
	)
	override;

	void
	remove_weapon(
		sanguis::is_primary_weapon
	)
	override;

	sanguis::client::draw2d::entities::model::load_parameters const
	model_parameters() const
	override;

	sanguis::load::auras::context &
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

	sanguis::client::draw2d::scene::object &object_;

	sanguis::client::draw2d::scene::hud::object &hud_;

	sanguis::client::draw2d::scene::world::object &world_;
};

}
}
}
}

#endif
