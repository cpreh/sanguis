#ifndef SANGUIS_CLIENT_LOGIC_HPP_INCLUDED
#define SANGUIS_CLIENT_LOGIC_HPP_INCLUDED

#include "player_action.hpp"
#include "send_callback.hpp"
#include "../cheat_type.hpp"
#include "cursor/object_ptr.hpp"
#include "../weapon_type.hpp"
#include "../entity_id.hpp"
#include "../messages/give_weapon.hpp"
#include "../messages/move.hpp"
#include <sge/console/object_fwd.hpp>
#include <sge/time/timer.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/sprite/point.hpp>
#include <sge/noncopyable.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <boost/tr1/array.hpp>
#include <boost/function.hpp>
#include <vector>

namespace sanguis
{
namespace client
{

class logic {
	SGE_NONCOPYABLE(logic)
public:
	logic(
		send_callback const &,
		sge::renderer::device_ptr,
		cursor::object_ptr,
		sge::console::object &);
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
	entity_id player_id() const;
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
	
	void send_cheat(
		cheat_type::type);

	send_callback const send;
	sge::renderer::device_ptr const rend;
	cursor::object_ptr const cursor_;

	typedef boost::function<
		void (key_scale)
	> action_handler;

	typedef std::vector<
		action_handler
	> action_handlers;

	action_handlers const actions;
		
	entity_id player_id_;

	typedef sge::math::vector::static_<
		float,
		2
	>::type direction_vector;

	direction_vector direction;
	sge::sprite::point player_center;
	weapon_type::type current_weapon;
	bool paused;
	sge::time::timer rotation_timer;

	typedef std::tr1::array<
		bool,
		weapon_type::size
	>                               owned_weapons_array;
	
	owned_weapons_array             owned_weapons;
	sge::signal::scoped_connection 
		cheat_kill_conn_,
		cheat_impulse_conn_;
};

}
}

#endif
