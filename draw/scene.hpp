#ifndef SANGUIS_DRAW_SCENE_HPP_INCLUDED
#define SANGUIS_DRAW_SCENE_HPP_INCLUDED

#include "scene_fwd.hpp"
#include "entity_auto_ptr.hpp"
#include "hud.hpp"
#include "environment.hpp"
#include "entity_fwd.hpp"
#include "background_fwd.hpp"
#include "sprite/client/system.hpp"
#include "sprite/normal/system.hpp"
#include "sprite/colored/system.hpp"
#include "sprite/particle/system.hpp"
#include "../load/context_fwd.hpp"
#include "../client_messages/add_fwd.hpp"
#include "../client_messages/visible_fwd.hpp"
#include "../messages/base.hpp"
#include "../messages/add_aoe_projectile.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_friend.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_player.hpp"
#include "../messages/add_projectile.hpp"
#include "../messages/add_weapon_pickup.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/experience.hpp"
#include "../messages/health.hpp"
#include "../messages/level_up.hpp"
#include "../messages/max_health.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/resize.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"
#include "../messages/start_reloading.hpp"
#include "../messages/stop_reloading.hpp"
#include "../messages/speed.hpp"
#include "../entity_id.hpp"
#include "../time_type.hpp"
#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace draw
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
	
	void process_message(
		messages::base const &);

	void client_message(
		client_messages::add const &);
	void client_message(
		client_messages::visible const &);

	void draw(time_type);

	sge::renderer::texture_ptr const
	capture_screen();

	void pause(bool);

	typedef void result_type;

	void operator()(messages::add_aoe_projectile const &);
	void operator()(messages::add_enemy const &);
	void operator()(messages::add_friend const &);
	void operator()(messages::add_pickup const &);
	void operator()(messages::add_player const &);
	void operator()(messages::add_projectile const &);
	void operator()(messages::add_weapon_pickup const &);
	void operator()(messages::change_weapon const &);
	void operator()(messages::experience const &);
	void operator()(messages::health const &);
	void operator()(messages::level_up const &);
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
private:
	template<
		typename Msg
	>
	void configure_new_object(
		entity_auto_ptr,
		Msg const &
	);
	
	void render_dead();

	draw::background &
	background();

	draw::environment const &
	environment();

	draw::entity &	
	insert(
		entity_auto_ptr
	);

	draw::entity &
	entity(
		entity_id
	);
	
	draw::entity const &
	entity(
		entity_id
	) const;
	
	void
	process_default_msg(
		messages::base const &
	);

	static fcppt::log::object &
	log();

	sge::renderer::device_ptr const rend;

	sprite::normal::system normal_system_;

	sprite::colored::system colored_system_;

	sprite::client::system client_system_;

	sprite::particle::system particle_system_;

	hud                           hud_;
	bool                          paused;
	draw::environment             env;
	entity_id                     background_id;
	bool                          paint_background;

	typedef boost::ptr_map<
		entity_id,
		draw::entity
	> entity_map;

	entity_map
		entities,
		dead_list;
};

}
}

#endif
