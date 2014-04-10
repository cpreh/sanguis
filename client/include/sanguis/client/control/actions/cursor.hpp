#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_CURSOR_HPP_INCLUDED

#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

class cursor
{
public:
	explicit
	cursor(
		sanguis::client::control::optional_cursor_position const &
	);

	sanguis::client::control::optional_cursor_position const
	position() const;
private:
	sanguis::client::control::optional_cursor_position position_;
};

}
}
}
}

#endif
