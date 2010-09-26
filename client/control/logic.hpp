#ifndef SANGUIS_CLIENT_CONTROL_LOGIC_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_LOGIC_HPP_INCLUDED

#include "logic_fwd.hpp"
#include "player_action_fwd.hpp"
#include "environment_fwd.hpp"
#include "key_scale.hpp"
#include "../send_callback.hpp"
#include "../../cheat_type.hpp"
#include "../../weapon_type.hpp"
#include <sge/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>

namespace sanguis
{
namespace client
{
namespace control
{

class logic
{
	FCPPT_NONCOPYABLE(logic)
public:
	logic(
		send_callback const &,
		environment &,
		sge::console::object &
	);

	~logic();

	void
	handle_player_action(
		player_action const &
	);

	void
	give_player_weapon(
		weapon_type::type
	);
private:
	void
	handle_move_x(
		key_scale
	);

	void
	handle_move_y(
		key_scale
	);

	void
	update_direction();

	void
	handle_rotation_x(
		key_scale
	);

	void
	handle_rotation_y(
		key_scale
	);

	void 
	update_rotation();

	void
	handle_shooting(
		key_scale
	);

	void
	handle_switch_weapon_forwards(
		key_scale
	);

	void
	handle_switch_weapon_backwards(
		key_scale
	);

	void
	handle_escape(
		key_scale
	);

	void
	change_weapon(
		weapon_type::type
	);
	
	void
	send_cheat(
		cheat_type::type,
		sge::console::arg_list const &,
		sge::console::object &
	);

	send_callback const send_;

	control::environment &environment_;

	typedef fcppt::function::object<
		void (key_scale)
	> action_handler;

	typedef std::vector<
		action_handler
	> action_handlers;

	action_handlers const actions_;
		
	weapon_type::type current_weapon_;

	sge::time::timer rotation_timer_;

	typedef std::tr1::array<
		bool,
		weapon_type::size
	> owned_weapons_array;
	
	owned_weapons_array owned_weapons_;

	fcppt::signal::scoped_connection 
		cheat_kill_conn_,
		cheat_impulse_conn_,
		cheat_exp_conn_;
};

}
}
}

#endif
