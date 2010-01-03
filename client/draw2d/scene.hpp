#ifndef SANGUIS_DRAW_SCENE_HPP_INCLUDED
#define SANGUIS_DRAW_SCENE_HPP_INCLUDED

#include "scene_fwd.hpp"
#include "entity_auto_ptr.hpp"
#include "hud.hpp"
#include "environment.hpp"
#include "entity_fwd.hpp"
#include "sprite/client/system.hpp"
#include "sprite/normal/system.hpp"
#include "sprite/colored/system.hpp"
#include "sprite/particle/system.hpp"
#include "../load/context_fwd.hpp"
#include "../client_messages/add_fwd.hpp"
#include "../client_messages/visible_fwd.hpp"
#include "../messages/base.hpp"
#include "../entity_id.hpp"
#include "../time_type.hpp"
#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/font/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

class scene {
	FCPPT_NONCOPYABLE(scene)
public:
	scene(
		load::context const &,
		sge::renderer::device_ptr,
		sge::font::object &
	);

	~scene();
	
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

	typedef void result_type;

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
	
	draw::entity const &
	entity(
		entity_id
	) const;
	
	static fcppt::log::object &
	log();

	sge::renderer::device_ptr const rend;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	hud hud_;

	bool paused;

	draw::environment env;

	fcppt::scoped_ptr<
		message_dispatcher
	> message_dispatcher_;

	typedef boost::ptr_map<
		entity_id,
		draw::entity
	> entity_map;

	entity_map entities;
};

}
}
}

#endif
