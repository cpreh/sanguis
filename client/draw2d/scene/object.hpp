#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "hud.hpp"
#include "../message/environment_fwd.hpp"
#include "../message/dispatcher_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/base_fwd.hpp"
#include "../sprite/client/system.hpp"
#include "../sprite/normal/system.hpp"
#include "../sprite/colored/system.hpp"
#include "../sprite/particle/system.hpp"
#include "../../client/messages/add_fwd.hpp"
#include "../../client/messages/visible_fwd.hpp"
#include "../../../load/context_fwd.hpp"
#include "../../../messages/base.hpp"
#include "../../../entity_id.hpp"
#include "../../../time_type.hpp"
#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/font/object_fwd.hpp>
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
		sge::font::object &
	);

	~object();
	
	void
	process_message(
		messages::base const &
	);

	void
	client_message(
		client_messages::add const &
	);

	void
	client_message(
		client_messages::visible const &
	);

	void
	draw(
		time_type
	);

	void
	pause(
		bool
	);
private:
	void
	render_systems();

	draw::entity &	
	insert(
		entity_auto_ptr,
		entity_id
	);

	draw::entity &
	entity(
		entity_id
	);
	
	sge::renderer::device_ptr const rend_;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	hud hud_;

	bool paused_;

	fcppt::scoped_ptr<
		message::environment
	> message_environment_;

	fcppt::scoped_ptr<
		message::dispatcher
	> message_dispatcher_;

	typedef boost::ptr_map<
		entity_id,
		draw::entity
	> entity_map;

	entity_map entities_;
};

}
}
}
}

#endif
