#ifndef SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED

#include "action_handler_fwd.hpp"
#include "direction_vector.hpp"
#include "environment_fwd.hpp"
#include "key_scale.hpp"
#include "actions/binary_fwd.hpp"
#include "actions/cursor_fwd.hpp"
#include "actions/nullary_fwd.hpp"
#include "actions/scale_fwd.hpp"
#include "../send_callback.hpp"
#include "../../cheat_type.hpp"
#include "../../weapon_type.hpp"
#include <sge/console/object_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
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
	);
public:
	action_handler(
		client::send_callback const &,
		control::environment &,
		sge::console::object &
	);

	~action_handler();

	void
	handle_binary_action(
		control::actions::binary const &
	);

	void
	handle_cursor_action(
		control::actions::cursor const &
	);

	void
	handle_nullary_action(
		control::actions::nullary const &
	);

	void
	handle_scale_action(
		control::actions::scale const &
	);
private:
	void
	give_player_weapon(
		weapon_type::type
	);

	void
	handle_move_x(
		control::key_scale
	);

	void
	handle_move_y(
		control::key_scale
	);

	void
	update_direction();

	void 
	update_rotation();

	void
	handle_shooting(
		bool
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

	typedef fcppt::container::array<
		bool,
		weapon_type::size
	> owned_weapons_array;
	
	owned_weapons_array owned_weapons_;

	control::direction_vector direction_;

	fcppt::signal::scoped_connection const
		cheat_kill_conn_,
		cheat_impulse_conn_,
		cheat_exp_conn_;
};

}
}
}

#endif
