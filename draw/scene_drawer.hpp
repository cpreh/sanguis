#ifndef SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED
#define SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED

#include "entity.hpp"
#include "hud.hpp"
#include "factory/types.hpp"
#include "types.hpp"
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"
#include "../time_type.hpp"
#include "../client_messages/fwd.hpp"
#include <sge/renderer/device.hpp>
#include <sge/sprite/system.hpp>
#include <sge/font/fwd.hpp>
#include <sge/type_info.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <vector>
#include <map>

namespace sanguis
{
namespace draw
{

class player;

class scene_drawer : boost::noncopyable {
public:
	scene_drawer(
		sge::renderer::device_ptr,
		sge::font::font &);
	
	void process_message(const messages::base&);

	void process_message(const client_messages::base&);

	void draw(const time_type);

	void pause(bool);

	const player& get_player() const;

	void operator()(const messages::add&);
	void operator()(const messages::add_enemy&);
	void operator()(const messages::add_pickup&);
	void operator()(const messages::add_weapon_pickup&);
	void operator()(const messages::change_weapon&);
	void operator()(const messages::experience&);
	void operator()(const messages::health&);
	void operator()(const messages::max_health&);
	void operator()(const messages::move&);
	void operator()(const messages::remove&);
	void operator()(const messages::resize&);
	void operator()(const messages::rotate&);
	void operator()(const messages::start_attacking&);
	void operator()(const messages::stop_attacking&);
	void operator()(const messages::speed&);

	void operator()(const client_messages::add&);
private:
	void configure_new_object(
		factory::entity_ptr,
		messages::add const &);
	
	entity& get_entity(entity_id);
	const entity& get_entity(entity_id) const;
	void process_default_msg(const messages::base&);
	void process_default_client_msg(const client_messages::base&);
	system &get_system();

	system                        ss;
	hud                           hud_;
	player*                       player_;
	bool                          paused;

	typedef boost::ptr_map<entity_id, entity> entity_map;
	entity_map entities;

	typedef boost::function<void (const messages::base&)> dispatch_fun;
	typedef std::map<sge::type_info, dispatch_fun> event_map;
	event_map event_dispatcher;

	//std::vector<sge::sprite::object> sprites;
};

}
}

#endif
