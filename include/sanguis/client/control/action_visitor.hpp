#ifndef SANGUIS_CLIENT_CONTROL_ACTION_VISITOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTION_VISITOR_HPP_INCLUDED

#include <sanguis/client/control/action_handler_fwd.hpp>
#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

class action_visitor
{
	FCPPT_NONASSIGNABLE(
		action_visitor
	);
public:
	explicit
	action_visitor(
		sanguis::client::control::action_handler &
	);

	typedef void result_type;

	result_type
	operator()(
		sanguis::client::control::actions::binary const &
	) const;

	result_type
	operator()(
		sanguis::client::control::actions::cursor const &
	) const;

	result_type
	operator()(
		sanguis::client::control::actions::nullary const &
	) const;

	result_type
	operator()(
		sanguis::client::control::actions::scale const &
	) const;
private:
	sanguis::client::control::action_handler &handler_;
};

}
}
}

#endif
