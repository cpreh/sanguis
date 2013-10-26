#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/message/dispatcher_fwd.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/scene/control_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/state_decl.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/load/auras/context.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <sanguis/messages/base.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_scoped_ptr.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <ctime>
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
		sanguis::load::context const &,
		sanguis::client::sound_manager &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		std::tm const &initial_time,
		sge::viewport::manager &
	);

	~object();

	void
	process_message(
		sanguis::messages::base const &
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

	void
	set_time(
		std::tm const &
	);

	sanguis::client::control::environment &
	control_environment() const;
private:
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
	name_display(
		sanguis::client::draw2d::entities::base const &
	);

	void
	remove(
		sanguis::entity_id
	);

	sanguis::client::draw2d::entities::base &
	entity(
		sanguis::entity_id
	);

	sanguis::client::draw2d::sprite::center const
	player_center() const;

	void
	transform(
		sanguis::client::draw2d::sprite::center const &
	);

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

	sanguis::client::draw2d::transform_callback const &
	transform_callback() const;

	sanguis::client::draw2d::insert_own_callback const &
	insert_own_callback() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system();

	sanguis::client::draw2d::sprite::colored::system &
	colored_system();

	sanguis::client::draw2d::sprite::client::system &
	client_system();

	sanguis::load::model::collection const &
	load_collection() const;

	sanguis::load::auras::context &
	aura_resources();

	sge::renderer::screen_size const
	screen_size() const;

	sge::renderer::target::viewport const
	viewport() const;

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::load::context const &resources_;

	sanguis::load::auras::context aura_resources_;

	sge::renderer::device::ffp &renderer_;

	sanguis::client::draw2d::sprite::state sprite_states_;

	sanguis::client::draw2d::sprite::normal::system normal_system_;

	sanguis::client::draw2d::sprite::colored::system colored_system_;

	sanguis::client::draw2d::sprite::client::system client_system_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::hud
	> const hud_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::world::object
	> const world_;

	bool paused_;

	sanguis::client::draw2d::sprite::center player_center_;

	sanguis::client::draw2d::transform_callback const transform_callback_;

	sanguis::client::draw2d::insert_own_callback const insert_own_callback_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::message::environment
	> const message_environment_;

	fcppt::scoped_ptr<
		sanguis::client::control::environment
	> const control_environment_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::message::dispatcher
	> const message_dispatcher_;

	typedef boost::ptr_map<
		sanguis::entity_id,
		sanguis::client::draw2d::entities::base
	> entity_map;

	typedef boost::ptr_list<
		sanguis::client::draw2d::entities::own
	> own_entity_list;

	entity_map entities_;

	own_entity_list own_entities_;

	std::tm current_time_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::background
	> const background_;

	sge::renderer::state::ffp::lighting::material::object_scoped_ptr const material_state_;
};

}
}
}
}

#endif
