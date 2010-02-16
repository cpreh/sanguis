#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "hud.hpp"
#include "message_environment_fwd.hpp"
#include "../message/environment_fwd.hpp"
#include "../message/dispatcher_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/base_fwd.hpp"
#include "../sprite/client/system.hpp"
#include "../sprite/normal/system.hpp"
#include "../sprite/colored/system.hpp"
#include "../sprite/particle/system.hpp"
#include "../sprite/point.hpp"
#include "../transform_callback.hpp"
#include "../insert_callback.hpp"
#include "../../control/environment_fwd.hpp"
#include "../../cursor/object_ptr.hpp"
#include "../../messages/add_fwd.hpp"
#include "../../messages/visible_fwd.hpp"
#include "../../../load/context_fwd.hpp"
#include "../../../load/model/collection_fwd.hpp"
#include "../../../messages/base.hpp"
#include "../../../entity_id.hpp"
#include "../../../time_type.hpp"
#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/font/object_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_map.hpp>

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
	FCPPT_NONCOPYABLE(object)
public:
	object(
		load::context const &,
		sge::renderer::device_ptr,
		sge::font::object &,
		client::cursor::object_ptr
	);

	~object();
	
	void
	process_message(
		sanguis::messages::base const &
	);

	entity_id
	client_message(
		sanguis::client::messages::add const &
	);

	void
	client_message(
		sanguis::client::messages::visible const &
	);

	void
	draw(
		time_type
	);

	void
	pause(
		bool
	);

	void
	player_id(
		entity_id
	);

	client::control::environment &
	control_environment() const;
private:
	friend class message_environment;

	friend class control_environment;

	void
	render_systems();

	entities::base &	
	insert(
		entities::auto_ptr,
		entity_id
	);

	entities::base &
	entity(
		entity_id
	);

	entities::base &
	own_player();

	void
	transform(
		sprite::point const &
	);

	draw2d::transform_callback const &
	transform_callback() const;

	draw2d::insert_callback const &
	insert_callback() const;

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
	
	load::context const &resources_;

	sge::renderer::device_ptr const rend_;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	hud hud_;

	bool paused_;

	entity_id
		player_id_,
		background_id_;

	sprite::point player_center_;

	draw2d::transform_callback const transform_callback_;

	draw2d::insert_callback const insert_callback_;

	fcppt::scoped_ptr<
		message::environment
	> message_environment_;

	fcppt::scoped_ptr<
		control::environment
	> control_environment_;

	fcppt::scoped_ptr<
		message::dispatcher
	> message_dispatcher_;

	typedef boost::ptr_map<
		entity_id,
		entities::base
	> entity_map;

	entity_map entities_;
};

}
}
}
}

#endif
