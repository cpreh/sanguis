#ifndef SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/timer.hpp>
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
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/short_description.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/connection_manager.hpp>
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
		bool,
		sanguis::is_primary_weapon
	);

	void
	handle_drop(
		sanguis::is_primary_weapon
	);

	void
	handle_reload(
		sanguis::is_primary_weapon
	);

	void
	send_cheat(
		sanguis::cheat_type,
		sge::console::arg_list const &,
		sge::console::object &
	);

	fcppt::signal::auto_connection
	cheat_connection(
		sge::console::object &,
		sanguis::cheat_type,
		sge::console::callback::name const &,
		sge::console::callback::short_description const &
	);

	sanguis::client::send_callback const send_;

	sanguis::client::control::environment &environment_;

	sanguis::timer rotation_timer_;

	sanguis::client::control::direction_vector direction_;

	fcppt::signal::connection_manager const cheat_connections_;
};

}
}
}

#endif
