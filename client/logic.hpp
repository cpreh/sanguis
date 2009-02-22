#ifndef SANGUIS_CLIENT_LOGIC_HPP_INCLUDED
#define SANGUIS_CLIENT_LOGIC_HPP_INCLUDED

#include "player_action.hpp"
#include "send_callback.hpp"
#include "../weapon_type.hpp"
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"
#include <sge/time/timer.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/signals/connection.hpp>
#include <sge/sprite/point.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/array.hpp>
#include <vector>

namespace sanguis
{
namespace client
{

class logic : boost::noncopyable {
public:
	explicit logic(
		send_callback const &,
		sge::renderer::device_ptr device,
		sge::console::gfx &);	
	void handle_player_action(
		player_action const &);
	void give_weapon(
		messages::give_weapon const &);
	void move(
		messages::move const &);
	void pause(
		bool);
	void remove(
		entity_id);
	void player_id(
		entity_id);

	sge::sprite::point const
	cursor_pos() const;
private:
	void handle_move_x(
		key_scale);
	void handle_move_y(
		key_scale);
	void update_direction();

	void handle_rotation_x(
		key_scale);
	void handle_rotation_y(
		key_scale);
	void update_rotation();

	void handle_shooting(
		key_scale);
	void handle_switch_weapon_forwards(
		key_scale);
	void handle_switch_weapon_backwards(
		key_scale);
	void handle_pause_unpause(
		key_scale);

	void change_weapon(
		weapon_type::type);

	void give_perk(
		sge::console::arg_list const &);

	send_callback const             send;
	sge::renderer::device_ptr const rend;
	sge::signals::connection const  give_perk_connection;

	typedef boost::function<
		void (key_scale)
	> action_handler;

	typedef std::vector<
		action_handler
		>                       action_handlers;
	action_handlers                 actions;
		
	entity_id                       player_id_;
	sge::math::vector::static_<
		float,
		2
	>::type                         direction;
	sge::sprite::point              cursor_pos_,
	                                player_center;
	weapon_type::type               current_weapon;
	bool                            paused;
	sge::time::timer                rotation_timer;

	typedef boost::array<
		bool,
		weapon_type::size
	>                               owned_weapons_array;
	
	owned_weapons_array             owned_weapons;
};

}
}

#endif
