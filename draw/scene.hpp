#ifndef SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED
#define SANGUIS_DRAW_SCENE_DRAWER_HPP_INCLUDED

#include "entity_auto_ptr.hpp"
#include "hud.hpp"
#include "system.hpp"
#include "environment.hpp"
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"
#include "../time_type.hpp"
#include "../client_messages/fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <sge/font/font_fwd.hpp>
#include <sge/type_info.hpp>
#include <sge/log/fwd.hpp>
#include <sge/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <vector>
#include <map>

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{

class entity;
class background;

class scene {
	SGE_NONCOPYABLE(scene)
public:
	scene(
		load::context const &,
		sge::renderer::device_ptr,
		sge::font::font &);
	~scene();
	
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
		entity_auto_ptr,
		messages::add const &);
	
	void render_dead();

	draw::background &
	background();

	draw::environment const &
	environment();

	void insert(
		entity_auto_ptr);

	draw::entity &
	entity(
		entity_id);
	
	draw::entity const &
	entity(
		entity_id) const;
	void process_default_msg(
		messages::base const &);
	void process_default_client_msg(
		client_messages::base const &);
	draw::system &system();
	
	static sge::log::logger &log();

	draw::system                  ss;
	hud                           hud_;
	bool                          paused;
	draw::environment             env;
	entity_id                     background_id;

	typedef boost::ptr_map<
		entity_id,
		draw::entity
	> entity_map;

	entity_map
		entities,
		dead_list;

	typedef boost::function<
		void (
			messages::base const &)
	> dispatch_fun;

	typedef std::map<
		sge::type_info,
		dispatch_fun
	> event_map;
	event_map event_dispatcher;
};

}
}

#endif
