#ifndef SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED

#include "action_handler_fwd.hpp"
#include "player_action_fwd.hpp"
#include "environment_fwd.hpp"
#include "key_scale.hpp"
#include "../send_callback.hpp"
#include "../../cheat_type.hpp"
#include "../../weapon_type.hpp"
#include <sge/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace control
{

class action_handler
{
	FCPPT_NONCOPYABLE(
		action_handler
	)
public:
	action_handler(
		client::send_callback const &,
		control::environment &,
		sge::console::object &
	);

	~action_handler();

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
	handle_switch_weapon(
		bool forward
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

	client::send_callback const send_;

	control::environment &environment_;

	weapon_type::type current_weapon_;

	sge::time::timer rotation_timer_;

	typedef std::tr1::array<
		bool,
		weapon_type::size
	> owned_weapons_array;
	
	owned_weapons_array owned_weapons_;

	fcppt::signal::scoped_connection const
		cheat_kill_conn_,
		cheat_impulse_conn_,
		cheat_exp_conn_;
};

}
}
}

#endif
