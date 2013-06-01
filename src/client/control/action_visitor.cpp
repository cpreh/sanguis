#include <sanguis/client/control/action_visitor.hpp>
#include <sanguis/client/control/action_handler.hpp>
#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>


sanguis::client::control::action_visitor::action_visitor(
	sanguis::client::control::action_handler &_handler
)
:
	handler_(
		_handler
	)
{
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	sanguis::client::control::actions::binary const &_action
) const
{
	handler_.handle_binary_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	sanguis::client::control::actions::cursor const &_action
) const
{
	handler_.handle_cursor_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	sanguis::client::control::actions::nullary const &_action
) const
{
	handler_.handle_nullary_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	sanguis::client::control::actions::scale const &_action
) const
{
	handler_.handle_scale_action(
		_action
	);
}
