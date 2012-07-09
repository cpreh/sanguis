#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/background_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/draw2d/scene/message_environment_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_auto_ptr.hpp>
#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/client/draw2d/message/dispatcher_fwd.hpp>
#include <sanguis/client/draw2d/sprite/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system.hpp>
#include <sanguis/client/draw2d/sprite/normal/system.hpp>
#include <sanguis/client/draw2d/sprite/colored/system.hpp>
#include <sanguis/client/draw2d/sprite/particle/system.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/matrix.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/random_generator.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/object_decl.hpp>
#include <fcppt/math/matrix/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
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
		load::context const &,
		sge::renderer::device &,
		sge::charconv::system &,
		sge::font::metrics &,
		sge::font::text::drawer &,
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
		sge::renderer::context::object &
	);

	void
	pause(
		bool
	);

	void
	set_time(
		std::tm const &
	);

	client::control::environment &
	control_environment() const;
private:
	friend class message_environment;

	friend class control_environment;

	void
	render_systems(
		sge::renderer::context::object &
	);

	void
	render_lighting(
		sge::renderer::context::object &
	);

	entities::base &
	insert(
		entities::unique_ptr,
		sanguis::entity_id
	);

	entities::own &
	insert_own(
		entities::own_auto_ptr
	);

	void
	remove(
		sanguis::entity_id
	);

	entities::base &
	entity(
		sanguis::entity_id
	);

	sprite::center const
	player_center() const;

	void
	transform(
		sprite::center const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator();

	draw2d::transform_callback const &
	transform_callback() const;

	draw2d::insert_own_callback const &
	insert_own_callback() const;

	sprite::normal::system &
	normal_system();

	sprite::colored::system &
	colored_system();

	sprite::client::system &
	client_system();

	sprite::particle::system &
	particle_system();

	load::model::collection const &
	load_collection() const;

	sge::renderer::screen_size const
	screen_size() const;

	sge::renderer::target::viewport const
	viewport() const;

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator random_generator_;

	load::context const &resources_;

	sge::renderer::device &rend_;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	fcppt::scoped_ptr<
		scene::hud
	> const hud_;

	fcppt::scoped_ptr<
		scene::world::object
	> const world_;

	bool paused_;

	sprite::center player_center_;

	draw2d::transform_callback const transform_callback_;

	draw2d::insert_own_callback const insert_own_callback_;

	fcppt::scoped_ptr<
		message::environment
	> const message_environment_;

	fcppt::scoped_ptr<
		control::environment
	> const control_environment_;

	fcppt::scoped_ptr<
		message::dispatcher
	> const message_dispatcher_;

	typedef boost::ptr_map<
		sanguis::entity_id,
		entities::base
	> entity_map;

	typedef boost::ptr_list<
		entities::own
	> own_entity_list;

	entity_map entities_;

	own_entity_list own_entities_;

	std::tm current_time_;

	sprite::matrix const default_transform_;

	fcppt::scoped_ptr<
		scene::background
	> const background_;
};

}
}
}
}

#endif
