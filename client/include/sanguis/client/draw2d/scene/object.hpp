#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/control/attack_dest_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/draw/base.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/scene/configure_entity_fwd.hpp>
#include <sanguis/client/draw2d/scene/control_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/state_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/auras/context.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/gui/renderer/base_unique_ptr.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/messages/server/add_aoe_projectile_fwd.hpp>
#include <sanguis/messages/server/add_aura_fwd.hpp>
#include <sanguis/messages/server/add_buff_fwd.hpp>
#include <sanguis/messages/server/add_destructible_fwd.hpp>
#include <sanguis/messages/server/add_enemy_fwd.hpp>
#include <sanguis/messages/server/add_friend_fwd.hpp>
#include <sanguis/messages/server/add_own_player_fwd.hpp>
#include <sanguis/messages/server/add_pickup_fwd.hpp>
#include <sanguis/messages/server/add_player_fwd.hpp>
#include <sanguis/messages/server/add_projectile_fwd.hpp>
#include <sanguis/messages/server/add_weapon_pickup_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/change_weapon_fwd.hpp>
#include <sanguis/messages/server/change_world_fwd.hpp>
#include <sanguis/messages/server/die_fwd.hpp>
#include <sanguis/messages/server/give_weapon_fwd.hpp>
#include <sanguis/messages/server/health_fwd.hpp>
#include <sanguis/messages/server/max_health_fwd.hpp>
#include <sanguis/messages/server/move_fwd.hpp>
#include <sanguis/messages/server/remove_buff_fwd.hpp>
#include <sanguis/messages/server/remove_fwd.hpp>
#include <sanguis/messages/server/remove_weapon_fwd.hpp>
#include <sanguis/messages/server/rotate_fwd.hpp>
#include <sanguis/messages/server/speed_fwd.hpp>
#include <sanguis/messages/server/weapon_status_fwd.hpp>
#include <alda/call/friend_dispatcher.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class object
:
	public sanguis::client::draw::base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sanguis::client::load::context const &,
		sanguis::client::load::hud::context &,
		sanguis::client::sound_manager &,
		sanguis::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::viewport::manager &,
		sanguis::client::player_health_callback const &,
		sanguis::client::cursor &,
		sanguis::client::draw::debug
	);

	~object()
	override;

	sanguis::client::draw2d::optional_translation const
	translation() const;
private:
	void
	process_message(
		sanguis::messages::server::base const &
	)
	override;

	void
	update(
		sanguis::client::slowed_duration
	)
	override;

	void
	draw(
		sge::renderer::context::ffp &
	)
	override;

	void
	overlay(
		sge::renderer::context::ffp &
	)
	override;

	void
	pause(
		bool
	)
	override;

	sanguis::client::control::environment &
	control_environment() const
	override;

	void
	render_systems(
		sge::renderer::context::ffp &
	);

	sanguis::client::draw2d::entities::base &
	insert(
		sanguis::client::draw2d::entities::unique_ptr &&,
		sanguis::entity_id
	);

	sanguis::client::draw2d::entities::own &
	insert_own(
		sanguis::client::draw2d::entities::own_unique_ptr &&
	);

	void
	hover_display(
		sanguis::client::draw2d::entities::base const &,
		sanguis::client::control::attack_dest
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
	player_center(
		sanguis::client::draw2d::optional_player_center
	);

	void
	update_translation();

	void
	change_world(
		sanguis::client::world_parameters const &
	);

	sge::renderer::screen_size const
	screen_size() const;

	sge::renderer::target::viewport const
	viewport() const;

	sanguis::client::draw2d::entities::load_parameters const
	load_parameters();

	sanguis::client::draw2d::insert_own_callback
	insert_own_callback();

	ALDA_CALL_FRIEND_DISPATCHER;

	typedef
	void
	result_type;

	result_type
	operator()(
		sanguis::messages::server::add_aoe_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_aura const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_buff const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_destructible const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_enemy const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_friend const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_own_player const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_player const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_weapon_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::server::change_weapon const &
	);

	result_type
	operator()(
		sanguis::messages::server::change_world const &
	);

	result_type
	operator()(
		sanguis::messages::server::die const &
	);

	result_type
	operator()(
		sanguis::messages::server::give_weapon const &
	);

	result_type
	operator()(
		sanguis::messages::server::health const &
	);

	result_type
	operator()(
		sanguis::messages::server::max_health const &
	);

	result_type
	operator()(
		sanguis::messages::server::move const &
	);

	result_type
	operator()(
		sanguis::messages::server::remove const &
	);

	result_type
	operator()(
		sanguis::messages::server::remove_buff const &
	);

	result_type
	operator()(
		sanguis::messages::server::remove_weapon const &
	);

	result_type
	operator()(
		sanguis::messages::server::rotate const &
	);

	result_type
	operator()(
		sanguis::messages::server::speed const &
	);

	result_type
	operator()(
		sanguis::messages::server::weapon_status const &
	);

	result_type
	process_default_msg(
		sanguis::messages::server::base const &
	);

	template<
		typename Message
	>
	friend class sanguis::client::draw2d::scene::configure_entity;

	template<
		typename Message
	>
	void
	configure_new_object(
		sanguis::client::draw2d::entities::unique_ptr &&,
		Message const &
	);

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::client::load::model::collection const &model_collection_;

	sanguis::client::load::hud::context &hud_resources_;

	sanguis::client::load::auras::context aura_resources_;

	sanguis::gui::style::base const &gui_style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::client::cursor &cursor_;

	sanguis::gui::renderer::base_unique_ptr const gui_renderer_;

	sanguis::client::player_health_callback const player_health_callback_;

	sanguis::client::draw2d::sprite::state sprite_states_;

	sanguis::client::draw2d::sprite::normal::system normal_system_;

	sanguis::client::draw2d::sprite::client::system client_system_;

	std::unique_ptr<
		sanguis::client::draw2d::scene::world::object
	> const world_;

	bool paused_;

	sanguis::client::draw2d::optional_player_center player_center_;

	sanguis::client::draw2d::optional_translation translation_;

	sanguis::client::weapon_pair player_weapons_;

	std::unique_ptr<
		sanguis::client::control::environment
	> const control_environment_;

	typedef
	std::map<
		sanguis::entity_id,
		sanguis::client::draw2d::entities::unique_ptr
	>
	entity_map;

	typedef
	std::list<
		sanguis::client::draw2d::entities::own_unique_ptr
	>
	own_entity_list;

	entity_map entities_;

	own_entity_list own_entities_;

	std::unique_ptr<
		sanguis::client::draw2d::scene::background
	> const background_;

	typedef
	std::vector<
		sanguis::client::draw2d::scene::hover::base_unique_ptr
	>
	hover_vector;

	hover_vector hovers_;

	fcppt::signal::scoped_connection const viewport_connection_;
};

}
}
}
}

#endif
