#ifndef SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_HANDLER_HPP_INCLUDED

#include <sanguis/cheat_type_fwd.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/client/control/action_handler_fwd.hpp>
#include <sanguis/client/control/direction_vector.hpp>
#include <sanguis/client/control/environment_cref.hpp>
#include <sanguis/client/control/key_scale.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/scalar.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/short_description.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sanguis::client::control
{

class action_handler
{
	FCPPT_NONMOVABLE(
		action_handler
	);
public:
	action_handler(
		sanguis::client::send_callback &&,
		sanguis::client::control::environment_cref,
		sge::console::object_ref
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

	[[nodiscard]]
	sanguis::client::control::optional_cursor_position const &
	cursor_position() const;
private:
	void
	update_direction(
		fcppt::reference<
			sanguis::client::control::scalar
		>,
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
		sge::console::arg_list const &
	);

	[[nodiscard]]
	fcppt::signal::auto_connection
	cheat_connection(
		sge::console::object_ref,
		sanguis::cheat_type,
		sge::console::callback::name const &,
		sge::console::callback::short_description const &
	);

	sanguis::client::send_callback const send_;

	sanguis::client::control::environment_cref const environment_;

	sanguis::timer rotation_timer_;

	sanguis::client::control::direction_vector direction_;

	sanguis::client::control::optional_cursor_position cursor_position_;

	fcppt::signal::auto_connection_container const cheat_connections_;
};

}

#endif
