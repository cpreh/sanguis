#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/optional_entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/control/attack_dest_fwd.hpp>
#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <sanguis/client/control/optional_attack_dest_fwd.hpp>
#include <sanguis/client/control/optional_cursor_position_fwd.hpp>
#include <sanguis/client/draw/base.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/optional_player_center_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/scene/camera_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/state/array.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/state_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/auras/context.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/messages/server/add_aoe_projectile_fwd.hpp>
#include <sanguis/messages/server/add_aura_fwd.hpp>
#include <sanguis/messages/server/add_buff_fwd.hpp>
#include <sanguis/messages/server/add_destructible_fwd.hpp>
#include <sanguis/messages/server/add_doodad_fwd.hpp>
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
#include <sanguis/messages/server/level_up_fwd.hpp>
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
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <map>
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
		fcppt::log::context &,
		sanguis::client::load::context const &,
		sanguis::client::load::hud::context &,
		sanguis::client::sound_manager &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::viewport::manager &,
		sanguis::client::player_health_callback const &,
		sanguis::client::cursor &,
		sanguis::client::draw::debug
	);

	~object()
	override;
private:
	void
	process_message(
		sanguis::messages::server::base const &
	)
	override;

	void
	update(
		sanguis::client::slowed_duration,
		sanguis::client::control::optional_cursor_position const &
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

	sanguis::client::control::optional_attack_dest
	translate_attack_dest(
		sanguis::client::control::cursor_position
	) const
	override;

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
	) const;

	sanguis::client::draw2d::optional_player_center
	player_center() const;

	void
	change_world(
		sanguis::client::world_parameters const &
	);

	sge::renderer::screen_size
	screen_size() const;

	sge::renderer::target::viewport
	viewport() const;

	sanguis::client::draw2d::entities::load_parameters
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
		sanguis::messages::server::add_doodad const &
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
		sanguis::messages::server::level_up const &
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
	void
	configure_new_object(
		sanguis::client::draw2d::entities::unique_ptr &&,
		Message const &
	);

	fcppt::log::context &log_context_;

	fcppt::log::object log_;

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::client::load::model::collection const &model_collection_;

	sanguis::client::load::hud::context &hud_resources_;

	sanguis::client::load::auras::context aura_resources_;

	sge::gui::style::base const &gui_style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::client::cursor &cursor_;

	sge::gui::renderer::base_unique_ptr const gui_renderer_;

	sanguis::client::player_health_callback const player_health_callback_;

	sanguis::client::draw2d::sprite::state sprite_states_;

	sanguis::client::draw2d::sprite::normal::system normal_system_;

	sanguis::client::draw2d::sprite::client::system client_system_;

	fcppt::unique_ptr<
		sanguis::client::draw2d::scene::world::object
	> const world_;

	bool paused_;

	sanguis::optional_entity_id player_id_;

	fcppt::unique_ptr<
		sanguis::client::draw2d::scene::camera
	> const camera_;

	sanguis::client::weapon_pair player_weapons_;

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

	fcppt::unique_ptr<
		sanguis::client::draw2d::scene::background
	> const background_;

	typedef
	fcppt::optional::object<
		sanguis::client::draw2d::scene::hover::base_unique_ptr
	>
	optional_hover_unique_ptr;

	optional_hover_unique_ptr hover_;

	sanguis::client::draw2d::scene::state::array const render_states_;
};

}
}
}
}

#endif
