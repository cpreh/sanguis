#ifndef SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED
#define SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED

#include <vector>
#include <map>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/sprite/system.hpp>
#include <sge/type_info.hpp>
#include <sge/timer.hpp>
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"
#include "../tick_event.hpp"
#include "../client_messages/fwd.hpp"
#include "entity.hpp"

namespace sanguis
{

namespace draw
{

class player;

class scene_drawer {
public:
	scene_drawer(sge::renderer_ptr);
	
	void process_message(const messages::base&);

	void process_message(const client_messages::base&);

	void draw(const tick_data &);

	const player& get_player() const;

	void operator()(const messages::add&);
	void operator()(const messages::health&);
	void operator()(const messages::max_health&);
	void operator()(const messages::move&);
	void operator()(const messages::player_state&);
	void operator()(const messages::remove&);
	void operator()(const messages::rotate&);
	void operator()(const messages::speed&);

	void operator()(const client_messages::add&);
private:
	entity& get_entity(entity_id);
	const entity& get_entity(entity_id) const;
	void process_default_msg(const messages::base&);
	void process_default_client_msg(const client_messages::base&);

	sge::sprite::system ss;
	player*             player_;

	typedef boost::ptr_map<entity_id, entity> entity_map;
	entity_map entities;

	typedef boost::function<void (const messages::base&)> dispatch_fun;
	typedef std::map<sge::type_info, dispatch_fun> event_map;
	event_map event_dispatcher;

	std::vector<sge::sprite::object> sprites;
};

}
}

#endif
