#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_CURSOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_CURSOR_HPP_INCLUDED

#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

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
	explicit cursor(
		control::cursor_position const &
	);

	control::cursor_position const
	position() const;
private:
	control::cursor_position position_;
};

}
}
}
}

#endif
