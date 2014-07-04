#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/control/attack_dest_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/message/dispatcher_fwd.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/scene/control_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base_unique_ptr.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/state_decl.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/load/auras/context.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
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
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sanguis::client::load::context const &,
		sanguis::client::load::hud::context &,
		sanguis::client::sound_manager &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::viewport::manager &,
		sanguis::client::player_health_callback const &
	);

	~object();

	void
	process_message(
		sanguis::messages::server::base const &
	);

	void
	update(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	pause(
		bool
	);

	sanguis::client::control::environment &
	control_environment() const;
private:
	// TODO: Create a proper interface for this
	friend class sanguis::client::draw2d::scene::message_environment;

	friend class sanguis::client::draw2d::scene::control_environment;

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

	sanguis::client::draw2d::optional_translation const
	translation() const;

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

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator();

	sanguis::client::sound_manager &
	sound_manager() const;

	sanguis::client::draw2d::player_center_callback const &
	player_center_callback() const;

	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system();

	sanguis::client::draw2d::sprite::colored::system &
	colored_system();

	sanguis::client::draw2d::sprite::client::system &
	client_system();

	sanguis::client::load::model::collection const &
	load_collection() const;

	sanguis::client::load::auras::context &
	aura_resources();

	sge::renderer::screen_size const
	screen_size() const;

	sge::renderer::target::viewport const
	viewport() const;

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::client::load::context const &resources_;

	sanguis::client::load::hud::context &hud_resources_;

	sanguis::client::load::auras::context aura_resources_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::client::draw2d::sprite::state sprite_states_;

	sanguis::client::draw2d::sprite::normal::system normal_system_;

	sanguis::client::draw2d::sprite::colored::system colored_system_;

	sanguis::client::draw2d::sprite::client::system client_system_;

	std::unique_ptr<
		sanguis::client::draw2d::scene::world::object
	> const world_;

	bool paused_;

	sanguis::client::draw2d::optional_player_center player_center_;

	sanguis::client::draw2d::optional_translation translation_;

	sanguis::client::draw2d::player_center_callback const player_center_callback_;

	sanguis::client::draw2d::insert_own_callback const insert_own_callback_;

	std::unique_ptr<
		sanguis::client::draw2d::message::environment
	> const message_environment_;

	std::unique_ptr<
		sanguis::client::control::environment
	> const control_environment_;

	std::unique_ptr<
		sanguis::client::draw2d::message::dispatcher
	> const message_dispatcher_;

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
