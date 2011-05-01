#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "background_fwd.hpp"
#include "hud_fwd.hpp"
#include "message_environment_fwd.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/own_auto_ptr.hpp"
#include "../entities/own_fwd.hpp"
#include "../entities/unique_ptr.hpp"
#include "../message/environment_fwd.hpp"
#include "../message/dispatcher_fwd.hpp"
#include "../sprite/client/system.hpp"
#include "../sprite/normal/system.hpp"
#include "../sprite/colored/system.hpp"
#include "../sprite/particle/system.hpp"
#include "../sprite/center.hpp"
#include "../sprite/matrix.hpp"
#include "../insert_own_callback.hpp"
#include "../transform_callback.hpp"
#include "../../control/environment_fwd.hpp"
#include "../../../load/context_fwd.hpp"
#include "../../../load/model/collection_fwd.hpp"
#include "../../../messages/base.hpp"
#include "../../../entity_id.hpp"
#include "../../../time_delta_fwd.hpp"
#include <sge/audio/listener_fwd.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/matrix/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <ctime>

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
		sge::font::metrics &,
		sge::font::text::drawer &,
		sge::audio::listener &,
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
		sanguis::time_delta const &
	);

	void
	draw();

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
	render_systems();

	void
	render_lighting();

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

	sge::renderer::viewport const
	viewport() const;

	load::context const &resources_;

	sge::renderer::device &rend_;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	fcppt::scoped_ptr<
		scene::hud
	> const hud_;

	sge::audio::listener &audio_listener_;

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
