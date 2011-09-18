#include <sanguis/client/control/action_visitor.hpp>
#include <sanguis/client/control/action_handler.hpp>

sanguis::client::control::action_visitor::action_visitor(
	control::action_handler &_handler
)
:
	handler_(_handler)
{
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	actions::binary const &_action
) const
{
	handler_.handle_binary_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	actions::cursor const &_action
) const
{
	handler_.handle_cursor_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	actions::nullary const &_action
) const
{
	handler_.handle_nullary_action(
		_action
	);
}

sanguis::client::control::action_visitor::result_type
sanguis::client::control::action_visitor::operator()(
	actions::scale const &_action
) const
{
	handler_.handle_scale_action(
		_action
	);
}
