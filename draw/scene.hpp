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

class scene : boost::noncopyable {
public:
	scene(
		sge::renderer::device_ptr,
		sge::font::font &);
	
	void process_message(
		messages::base const &);

	void process_message(
		client_messages::base const &);

	void draw(time_type);

	void pause(bool);

	void operator()(messages::add const &);
	void operator()(messages::add_enemy const &);
	void operator()(messages::add_pickup const &);
	void operator()(messages::add_decoration const &);
	void operator()(messages::add_projectile const &);
	void operator()(messages::add_weapon_pickup const &);
	void operator()(messages::change_weapon const &);
	void operator()(messages::experience const &);
	void operator()(messages::health const &);
	void operator()(messages::max_health const &);
	void operator()(messages::move const &);
	void operator()(messages::remove const &);
	void operator()(messages::resize const &);
	void operator()(messages::rotate const &);
	void operator()(messages::start_attacking const &);
	void operator()(messages::stop_attacking const &);
	void operator()(messages::start_reloading const &);
	void operator()(messages::stop_reloading const &);
	void operator()(messages::speed const &);

	void operator()(client_messages::add const &);
private:
	void configure_new_object(
		factory::entity_ptr,
		messages::add const &);
	
	entity &get_entity(entity_id);
	entity const &get_entity(entity_id) const;
	void process_default_msg(messages::base const &);
	void process_default_client_msg(client_messages::base const &);
	system &get_system();

	system                        ss;
	hud                           hud_;
	bool                          paused;

	typedef boost::ptr_map<entity_id, entity> entity_map;
	entity_map entities;

	typedef boost::function<void (messages::base const &)> dispatch_fun;
	typedef std::map<sge::type_info, dispatch_fun> event_map;
	event_map event_dispatcher;
};

}
}

#endif
