#ifndef SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/control/action_handler_fwd.hpp>
#include <sanguis/client/control/direction_vector.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/scalar.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_fwd.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


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
		sanguis::client::send_callback const &,
		sanguis::client::control::environment &,
		sge::console::object &
	);

	~action_handler();

	void
	handle_action(
		sanguis::client::control::actions::any const &
	);

	void
	give_player_weapon(
		sanguis::weapon_type
	);

	void
	handle_binary_action(
		sanguis::client::control::actions::binary const &
	);

	void
	handle_cursor_action(
		sanguis::client::control::actions::cursor const &
	);

	void
	handle_nullary_action(
		sanguis::client::control::actions::nullary const &
	);

	void
	handle_scale_action(
		sanguis::client::control::actions::scale const &
	);
private:
	void
	update_direction(
		sanguis::client::control::scalar &,
		sanguis::client::control::key_scale
	);

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
		sanguis::weapon_type
	);

	void
	send_cheat(
		sanguis::cheat_type,
		sge::console::arg_list const &,
		sge::console::object &
	);

	sanguis::client::send_callback const send_;

	sanguis::client::control::environment &environment_;

	sanguis::optional_weapon_type current_weapon_;

	sanguis::timer rotation_timer_;

	typedef std::array<
		bool,
		static_cast<
			std::size_t
		>(
			fcppt::enum_size<
				sanguis::weapon_type
			>::value
		)
	> owned_weapons_array;

	owned_weapons_array owned_weapons_;

	sanguis::client::control::direction_vector direction_;

	fcppt::signal::scoped_connection const
		cheat_kill_conn_,
		cheat_exp_conn_;
};

}
}
}

#endif
